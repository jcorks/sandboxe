#include <sandboxe/script/runtime.h>
#include <sandboxe/entity/terminal.h>
#include <sandboxe/script/shell.h>
#include <Dynacoe/Library.h>
#include <Dynacoe/RawData.h>
#include <sandboxe/trunk.h>
#include <cassert>
#include <v8.h>
#include <sandboxe/bindings/all.hpp>
#include <map>

using Sandboxe::Script::Runtime::Function;
using Sandboxe::Script::Runtime::Object;
using Sandboxe::Script::Runtime::Primitive;
using Sandboxe::Script::Runtime::Context;
using Sandboxe::Script::Runtime::Object_Internal;



struct SandboxeContextModel {
    v8::Persistent<v8::Context> context;
    v8::TryCatch exceptionHandler;
    Object * contextObject;
    Dynacoe::Entity::ID terminal;
    std::map<std::string, Function> functions;
};


// stored type information for objects
struct Type {
    // unique identifier of the type
    int typeID;

    // Handle to the v8-mirrored object template
    v8::Persistent<v8::ObjectTemplate> self;

    // List of native functions, mapped by name
    std::map<std::string, Function> functions;
    
    // List of nativeProperty handliers, mapped by name
    std::map<std::string, std::pair<Function, Function>> natives;
};


// Native reference to a Runtime::Object
struct Object_Internal {
    // v8 handle representing this object.
    v8::Persistent<v8::Object> reference;
    
    // Pointer to the type of this object
    Type * typeData;
    
    // Object reference that owns this Object_Internal
    Object * parent;
    
    
    // returns whether this instance is from a native instance
    int isNative; 
    
    // nonNative objects set with SetNonNativeReference
    std::vector<Object *> nonNatives;

    
    void ForceNative();
};




// Define to specific where scopes start and end
#define SANDBOXE_SCOPE v8::HandleScope v8_handleScope


static SandboxeContextModel * global = nullptr;

// Table of all objects. Since v8 doesnt seem to send events for object cleanup,
// this has to be cleaned out every now and then
std::vector<Object_Internal*> objects;
std::vector<Object*> temporary;

// Table of all types. 
std::vector<Type *> types;



//////////////////////////////////////
/// Native helpers
/////////////////////////////////
// reports exceptions 
static void script_exception_handler(v8::TryCatch * tcatch) {
    v8::HandleScope scopeMonitor;
    if (tcatch->Exception().IsEmpty()) return;

    v8::String::Utf8Value exception(tcatch->Exception());



    Sandboxe::Script::Terminal * term = global->terminal.IdentifyAs<Sandboxe::Script::Terminal>();
    if (!term) return;


    const char * rawString = *exception;
    
    v8::Handle<v8::Message> detail = tcatch->Message();

    // no other info but the bassic message string
    if(detail.IsEmpty()) {
        term->ReportError(rawString);
        return;
    }
    

    Dynacoe::Chain message;

    
    // location first
    v8::String::Utf8Value filename(detail->GetScriptResourceName());
    int linenum = detail->GetLineNumber();
    
    
    // erroneous code
    message 
        << "  "
        << (const char*)*filename << ", line " << linenum << ": " << rawString << "\n  "
        << (const char*)*v8::String::Utf8Value(detail->GetSourceLine()) << "\n  "
    ;
    for(int i = 0; i < detail->GetStartColumn(); ++i)
        message << " ";
        
    for(int i = detail->GetStartColumn(); i < detail->GetEndColumn(); ++i) 
        message << "^";
    
    
    
    
    
    // erroneous code
    v8::String::Utf8Value st(tcatch->StackTrace());
    if (*st) {
        message << "\n  Call Stack info:\n  " << (const char*)*st << "\n";
    }   
    


    // try to run the default handler. If unsuccessful, return 0
    // The default handler is passed the system-dependent error string.

    v8::Handle<v8::String> sourceHandle = v8::String::New("try{sandboxe.script.onError();}catch(e){false;return;}true;");
    v8::Handle<v8::String> nameHandle = v8::String::New("<internal>");
    v8::Handle<v8::Script> script = v8::Script::Compile(sourceHandle, nameHandle);
    
    // compilation error
    assert(!script.IsEmpty());
    
    // runtime error
    v8::Handle<v8::Value> result = script->Run();
    if (!(!result.IsEmpty() && result->IsTrue())) {
        auto win = Dynacoe::ViewManager::Get(Dynacoe::ViewManager::GetCurrent());
        if (!win) {
            Dynacoe::Console::Info() << "**Note**: A display was automatically created and shown to display the scripting error.\n";
            Dynacoe::ViewManager::NewMain("sandboxe");
        }

        term->ReportError(message.ToString().c_str());
        Dynacoe::Console::Show(true);
        
    }
}


static v8::Handle<v8::Value> sandboxe_primitive_to_v8_value(const Primitive & p) {
    if (!p.IsDefined()) return v8::Undefined();
    switch(p.hint) {
      case Primitive::TypeHint::BooleanT: return v8::Boolean::New(p);
      case Primitive::TypeHint::IntegerT: return v8::Integer::New(p);
      case Primitive::TypeHint::FloatT:   
      case Primitive::TypeHint::DoubleT:  return v8::Number::New(p);
      case Primitive::TypeHint::UInt32T:  return v8::Uint32::New(p);
      case Primitive::TypeHint::UInt64T:  return v8::Number::New(p);
      case Primitive::TypeHint::ObjectReferenceT:  return ((Object*)p)->GetNative()->reference;
      case Primitive::TypeHint::ObjectReferenceNonNativeT:  return ((Object*)p)->GetNative()->reference;
      default:;
    }
    return v8::String::New(std::string(p).c_str());
}

static Object * sandboxe_object_reference_temporary_from_v8_value(const v8::Handle<v8::Value> & val) {
    Object_Internal * ref = new Object_Internal;
    ref->isNative = false;
    ref->typeData = nullptr;
    ref->parent = nullptr;
    ref->reference = v8::Persistent<v8::Object>::New(val->ToObject());
    ref->reference.MarkIndependent();
    
    Object * temp = new Object(*ref);

    // gets cleaned up next cycle
    temporary.push_back(temp);
    return temp;
}

static std::vector<Primitive> v8_array_to_sandboxe_primitive_array(v8::Handle<v8::Object> array) {
    std::vector<Primitive> arguments;
    uint32_t len = v8::Array::Cast(*array)->Length();
    for(uint32_t i = 0; i < len; ++i) {
        auto item = array->Get(i);
        // collect native objects 
        if (item->IsObject()) {
            v8::Handle<v8::Object> object = item->ToObject();
            if (object->InternalFieldCount()) { //< - Native object
                arguments.push_back(
                    (
                        (Object_Internal*)object->GetPointerFromInternalField(0)
                    )->parent
                );            
            } else if (item->IsFunction()) { //<- non-native object

                arguments.push_back(sandboxe_object_reference_temporary_from_v8_value(item));
                
            } else {
                arguments.push_back(*v8::String::Utf8Value(item) ? Primitive(std::string(*v8::String::Utf8Value(item))) : Primitive());
            }
        } else {
            arguments.push_back(*v8::String::Utf8Value(item) ? Primitive(std::string(*v8::String::Utf8Value(item))) : Primitive());
        }
    }
    return arguments;
}

static Primitive v8_object_to_primitive(const v8::Persistent<v8::Value> * source, Sandboxe::Script::Runtime::Context & context, uint32_t argIndex) {
    // collect native objects 
    if ((*source)->IsObject()) {
        v8::Handle<v8::Object> object = (*source)->ToObject()->Clone();
        if (object->InternalFieldCount()) { //< - Native object
            return
                (
                    (Object_Internal*)object->GetPointerFromInternalField(0)
                )->parent;
            
        } else if (object->IsFunction()) { //<- non-native object

            return sandboxe_object_reference_temporary_from_v8_value(object);
            
        } else if (object->IsArray()) {
            // blank for the slot in the normal argument input.
            // user functions need to know to check the array argument if they want an array.
            context.SetArrayArgument(argIndex, v8_array_to_sandboxe_primitive_array(object));
            return Primitive();
        } else {    
            return *v8::String::Utf8Value(object) ? Primitive(std::string(*v8::String::Utf8Value(object))) : Primitive();
        }
    } else {
        return *v8::String::Utf8Value(*source) ? Primitive(std::string(*v8::String::Utf8Value(*source))) : Primitive();
    }
}

static std::vector<Primitive> v8_arguments_to_sandboxe_primitive_array(const v8::Arguments & args, Sandboxe::Script::Runtime::Context & context) {
    std::vector<Primitive> arguments;
    for(uint32_t i = 0; i < args.Length(); ++i) {
        v8::Persistent<v8::Value> per = v8::Persistent<v8::Value>::New(args[i]);
        arguments.push_back(v8_object_to_primitive(&per, context, i));
        per.Dispose();
    }
    return arguments;
}


static v8::Handle<v8::Value> sandboxe_context_get_return_value(const Context & context) {
    // if the native call wants to return a new scripting object, do so
    if (context.ReturnsArray()) {
        auto outputArray = context.GetReturnArray();
        /// ARRAY PLS
        v8::Handle<v8::Array> array = v8::Array::New(outputArray.size());
        for(uint32_t i = 0; i < outputArray.size(); ++i) {
            array->Set(i, sandboxe_primitive_to_v8_value(outputArray[i]));
        }
        return array;
    } else if (context.GetReturnValue().hint == Primitive::TypeHint::ObjectReferenceT) {
        return ((Object*)context.GetReturnValue())->GetNative()->reference;
    }
    return sandboxe_primitive_to_v8_value(context.GetReturnValue());
    
}

////////////////////////////////////////////////////////
/// native functions
///////////////////////////////////////////////////////
uint32_t ITERP = 0;


static v8::Handle<v8::Value> sandboxe_v8_native__accessor_get(v8::Local<v8::String> name, const v8::AccessorInfo & info) {
    //SANDBOXE_SCOPE;
    Object_Internal * ref = (Object_Internal*) info.This()->GetPointerFromInternalField(0);
    Context context;
    std::string into = *v8::String::Utf8Value(name);
    printf("E_AG (%u) %p %s\n", ITERP, ref->typeData->natives[*v8::String::Utf8Value(name)].first, into.c_str());
    ref->typeData->natives[into].first(
        ref->parent,
        {},
        context
    );
    printf("L_AG (%u) %p %s\n", ITERP++, ref->typeData->natives[*v8::String::Utf8Value(name)].first, into.c_str());
    fflush(stdout);
    return sandboxe_context_get_return_value(context);
}

static void sandboxe_v8_native__accessor_set(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo & info) {
    //SANDBOXE_SCOPE;
    Object_Internal * ref = (Object_Internal*) info.This()->GetPointerFromInternalField(0);
    std::vector<Primitive> arguments;
    Context context;
    v8::Persistent<v8::Value> per = v8::Persistent<v8::Value>::New(value);
    
    arguments.push_back(v8_object_to_primitive(&per, context, 0));
    std::string into = *v8::String::Utf8Value(name);
    printf("E_AS (%u) %p %s\n", ITERP, ref->typeData->natives[into].second, into.c_str());
    ref->typeData->natives[into].second(
        ref->parent,
        arguments,
        context
    );
    printf("L_AS (%u) %p %s\n", ITERP++, ref->typeData->natives[into].second, into.c_str());
    fflush(stdout);
    
    per.Dispose();
}

static v8::Handle<v8::Value> sandboxe_v8_native__invocation(const v8::Arguments & args) {
    // arguments should have reference to original object;
    //SANDBOXE_SCOPE;
    Object_Internal * ref = (Object_Internal*) args.Holder()->GetPointerFromInternalField(0);
    Context context;
    std::vector<Primitive> arguments = v8_arguments_to_sandboxe_primitive_array(args, context);

        
    std::string into = *v8::String::Utf8Value(args.Callee()->GetName());
    printf("E_NI (%u) %p %s\n", ITERP, ref->typeData->functions[into], into.c_str());
    ref->typeData->functions[into](
        ref->parent,
        arguments,
        context
    );
    printf("L_NI (%u)%p %s\n", ITERP++, ref->typeData->functions[into], into.c_str());
    fflush(stdout);


    return sandboxe_context_get_return_value(context);

}

// globals functions defined at initialization
static v8::Handle<v8::Value> sandboxe_v8_native__global_incovation(const v8::Arguments & args) {
    SANDBOXE_SCOPE;
    Function f = (Function)(Dynacoe::Chain() << *v8::String::Utf8Value(args.Data())).AsUInt64();

    Sandboxe::Script::Runtime::Context context;
    std::vector<Primitive> arguments = v8_arguments_to_sandboxe_primitive_array(args, context);
    
    // gather native objects if applicable
    printf("E_GI (%u) %p\n", ITERP, f);
    f(nullptr, arguments, context);
    printf("L_GI (%u) %p\n", ITERP, f);
    return sandboxe_context_get_return_value(context);



}














// loads a new script file
static std::set<std::string> includedScripts; 

static v8::Handle<v8::Value> debug_is_native(const v8::Arguments & args) {
    //v8::HandleScope scopeMonitor;
    if (args.Length() < 1) {
        return v8::Undefined();
    }
    if (args[0]->IsObject() && args[0]->ToObject()->InternalFieldCount()) return v8::True();
    return v8::False();
}

static v8::Handle<v8::Value> debug_is_function(const v8::Arguments & args) {
    //v8::HandleScope scopeMonitor;
    if (args.Length() < 1) {
        return v8::Undefined();
    }
    if (args[0]->IsFunction()) return v8::True();
    return v8::False();
}

static v8::Handle<v8::Value> debug_get_properties(const v8::Arguments & args) {
    //v8::HandleScope scopeMonitor;
    if (args.Length() < 1) {
        return v8::Undefined();
    }
    if (args[0]->IsObject()) {
        return args[0]->ToObject()->GetPropertyNames();
    }
    return v8::Undefined();
}

static v8::Handle<v8::Value> script_include(const v8::Arguments & args) {
    //v8::HandleScope scopeMonitor;
    if (args.Length() < 1) {
        return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "Exactly one arg, dummy\n").ToString().c_str()));
    }
    
    // having a second argument is a flag for only including rather than running.
    bool pragmaOnce = false;
    if (args.Length() == 2) {
        pragmaOnce = true;
    }
    
    
    v8::String::Utf8Value path(args[0]);

    // if include_once, ignore additional include requests
    if (pragmaOnce && includedScripts.find(*path) != includedScripts.end()) {
        return v8::Undefined();
    }
    
    Dynacoe::AssetID id;
    if (Sandboxe::Trunk::ItemExists(*path)) {
        Dynacoe::Console::Info() << "Loading " << *path << " from trunk\n";
        id = Dynacoe::Assets::LoadFromBuffer(
            "", 
            *path, 
            Sandboxe::Trunk::ItemGet(*path)
        );    
    } else {
        id = Dynacoe::Assets::Load("", *path, false);
    }
    if (!id.Valid()) {
        return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "File " << *path << " could not be accessed.\n").ToString().c_str()));
    }
    
    // retrieve full string
    Dynacoe::RawData & data = Dynacoe::Assets::Get<Dynacoe::RawData>(id);
    char * rawStr = new char[data.GetSize()+1];
    rawStr[data.GetSize()] = 0;
    memcpy(rawStr, data.GetPtr(), data.GetSize());
    
    includedScripts.insert(*path);
    
    // execute the script
    Sandboxe::Script::Runtime::Execute(rawStr, *path);
        //delete[] rawStr;
        //return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "File " << *path << " could not be accessed.\n").ToString().c_str()));
    
    Sandboxe::Script::Runtime::CheckAndHandleErrors();
    
    delete[] rawStr;
    
    
    return v8::Undefined();
}








void Sandboxe::Script::Runtime::Initialize() {
    v8::HandleScope top;
    global = new SandboxeContextModel;
    global->terminal = Dynacoe::Entity::Create<Sandboxe::Script::Terminal>();
    
    v8::Handle<v8::ObjectTemplate> base = v8::ObjectTemplate::New();
    // set base functions
    base->Set(v8::String::New("__script_include"), v8::FunctionTemplate::New(script_include)); 

    base->Set(v8::String::New("__debug_get_properties"), v8::FunctionTemplate::New(debug_get_properties)); 
    base->Set(v8::String::New("__debug_isFunction"), v8::FunctionTemplate::New(debug_is_function)); 
    base->Set(v8::String::New("__debug_isNative"), v8::FunctionTemplate::New(debug_is_native)); 

    const std::vector<std::pair<std::string, Function>> & fns = Sandboxe::Script::GatherNativeBindings();
    if (fns.size()) {
        
        std::string str;
        for(uint32_t i = 0; i < fns.size(); ++i) {            
            str = Dynacoe::Chain() << (uint64_t)fns[i].second;
            base->Set(
                v8::String::New(fns[i].first.c_str()),
                v8::FunctionTemplate::New(            
                    sandboxe_v8_native__global_incovation,
                    v8::String::New(str.c_str())
                )
            );
        }
    }

    // include base bindings 
    //Sandboxe::Script::BindAll(global->sandboxeJS);

    global->context = v8::Context::New(NULL, base);
    
    //assert(!global->context.IsEmpty());
    global->context->Enter();

    Dynacoe::Console::Info() << "v8 version " << v8::V8::GetVersion() << "\n";
    

    // innitialize dynacoe shell extension
    Sandboxe::Script::Shell::Initialize();
    

    Sandboxe::Script::ApplyPostBindings();
    
    
}


std::string initialization_source = 
#include "../../sandboxe_initialization.js"
;
#include <sandboxe/script/garbageCollector.h>
void Sandboxe::Script::Runtime::Start() {
    SANDBOXE_SCOPE;
    v8::Context::Scope scope(global->context);
    Dynacoe::Engine::AttachManager(Dynacoe::Entity::Create<Sandboxe::GarbageCollector>());

    // finally, load in base logic for sandboxe bindings
    {
        std::vector<uint8_t> initData(
            (uint8_t*)&initialization_source[0],
            ((uint8_t*)&initialization_source[0]) + initialization_source.size()
        );
        Sandboxe::Trunk::AddItem("sandboxe_initialization", initData);
    }
    
    Sandboxe::Script::Runtime::Load("sandboxe_initialization");
    Dynacoe::Console::OverlayMessageMode(Dynacoe::Console::MessageMode::Disabled);
    Dynacoe::Console::Info() 
        << "                         ____                  \n"
        << "   _________ _____  ____/ / /_  ____  _  _____ \n"
        << "  / ___/ __ `/ __ \\/ __  / __ \\/ __ \\| |/_/ _ \\\n"
        << " (__  ) /_/ / / / / /_/ / /_/ / /_/ />  </  __/\n"
        << "/____/\\__,_/_/ /_/\\__,_/_.___/\\____/_/|_|\\___/ \n"
        << "Johnathan Corkery, 2018 (coebeef.net/sandboxe)\n\n"
        << "Backend status:\n\n";

    Dynacoe::Console::OverlayMessageMode(Dynacoe::Console::MessageMode::Standard);



    
    
    
    Sandboxe::Script::Runtime::Load("main.js");
    
    Dynacoe::Engine::Run();
}

std::string Sandboxe::Script::Runtime::Execute(const std::string & source, const std::string & name) {
    //v8::HandleScope scopeMonitor;
    v8::Handle<v8::String> sourceHandle = v8::String::New(source.c_str());
    v8::Handle<v8::String> nameHandle = v8::String::New(name.c_str());

    v8::Handle<v8::Script> script = v8::Script::Compile(sourceHandle, nameHandle);
    
    // compilation error
    if (script.IsEmpty()) {
        return "";
    }
    
    // runtime error
    v8::Handle<v8::Value> result = script->Run();
    if (result.IsEmpty()) {
        return "";
    }
    
    v8::String::Utf8Value resultStr(result);

    return std::string(*resultStr ? *resultStr : "<undefined>");
}

void Sandboxe::Script::Runtime::Load(const std::string & path) {
    //TODO: sanitize?
    Execute(Dynacoe::Chain() << "__script_include(\"" << path << "\");\n");
}














void Sandboxe::Script::Runtime::AddType(int typeID,
    const std::vector<std::pair<std::string, Function>> & functions,
    const std::vector<std::pair<std::string, Primitive>> & properties,
    const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties
) {
    if (typeID >= 0 && typeID < types.size() && types[typeID]) {
        v8::ThrowException(v8::String::New("sandboxe script object: Type already exists..."));
        return;
    }
    while(types.size() <= typeID) {
        types.push_back(nullptr);
    }
    
    SANDBOXE_SCOPE;

    Type * data = new Type;
    data->self = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
    data->self->SetInternalFieldCount(1);
    data->typeID = typeID;
    
    
    // normal functions
    for(uint32_t i = 0; i < functions.size(); ++i) {
        data->self->Set(
            v8::String::New(functions[i].first.c_str()),
            v8::FunctionTemplate::New(sandboxe_v8_native__invocation)
        );
        data->functions[functions[i].first] = functions[i].second;
    }
    
    
    // normal properties (starting values)
    for(uint32_t i = 0; i < properties.size(); ++i) {
        data->self->Set(
            v8::String::New(properties[i].first.c_str()),
            v8::String::New(std::string(properties[i].second).c_str())
        );        
    }
    
    
    // for native properties
    for(uint32_t i = 0; i < nativeProperties.size(); ++i) {
        data->self->SetAccessor(
            v8::String::New(nativeProperties[i].first.c_str()),
            sandboxe_v8_native__accessor_get,
            sandboxe_v8_native__accessor_set
        );
        data->natives[nativeProperties[i].first] = nativeProperties[i].second;
    }
    types[typeID] = data;
    
}




static void sandboxe_v8_object_garbage_collect(v8::Persistent<v8::Value> src, void * data) {
    Object_Internal * object = (Object_Internal*)src->ToObject()->GetPointerFromInternalField(0);
    object->parent->OnGarbageCollection();
    Dynacoe::Console::Info() << "Removing" << (uint64_t)data << "\n";
    delete object->parent;
    
}



Object::Object(int typeID) {
    data = new Object_Internal;
    data->isNative = true;
    data->typeData = types[typeID];
    if (data->typeData == nullptr) {
        v8::ThrowException(v8::String::New("sandboxe script object: Type does not exist"));
        //objects.push_back(data);
        return;
    }
    data->parent = this;
    v8::Handle<v8::Object> obj = data->typeData->self->NewInstance();
    // set a ref to the type info
    obj->SetPointerInInternalField(0, data);

    //objects.push_back(data);
    data->reference = v8::Persistent<v8::Object>::New(obj);
    //data->reference.MakeWeak(data, sandboxe_v8_object_garbage_collect);
}


// non-native object
Object::Object(Object_Internal & inData) {
    data = &inData;
    // set a ref to the type info
    data->reference->SetPointerInInternalField(0, data);
    data->typeData = nullptr;
}


Object::~Object() {
    for(uint32_t i = 0; i < data->nonNatives.size(); ++i) {
        temporary.push_back(data->nonNatives[i]);
    }
    delete data;
}

Primitive Object::Get(const std::string & name) {
    if (data->reference.IsEmpty()) {
        v8::ThrowException(v8::String::New("sandboxe script object: Get() failed; reference is dead"));
        return Primitive();
    }
    v8::Handle<v8::Value> obj = data->reference->Get(v8::String::New(name.c_str()));
    if (obj->IsObject() && (obj->IsFunction() || obj->IsArray())) {
        return sandboxe_object_reference_temporary_from_v8_value(obj);
    }
    v8::String::Utf8Value value(obj);
    return (*value ? Primitive(std::string(*value)) : Primitive());
}

void Object::Set(const std::string & name, const Primitive & d) {
    if (data->reference.IsEmpty()) {
         v8::ThrowException(v8::String::New("sandboxe script object: Set() failed; reference is dead"));
    }
    data->reference->Set(
        v8::String::New(name.c_str()),
        sandboxe_primitive_to_v8_value(d)
            
    );

}


void Object_Internal::ForceNative() {
    assert(!isNative);
    if (!isNative) {

        v8::Handle<v8::Object> obj = reference; // non-native data

        // transform into native reference
        isNative = true;
        typeData = nullptr;


        //objects.push_back(data);
        reference = v8::Persistent<v8::Object>::New(obj);
        // set a ref to the type info
        reference->SetPointerInInternalField(0, this);
        //reference.MakeWeak(this, sandboxe_v8_object_garbage_collect);
        reference.MarkIndependent();
        std::cout << this << "is now native" << std::endl;
    }
}


uint32_t Object::AddNonNativeReference(Object * d) {
    uint32_t out = data->nonNatives.size();

    d->data->ForceNative();

    data->nonNatives.push_back(d);
    // defers destruction of temporary
    // they will be reposted to destruction on this objects destructor
    for(uint32_t i = 0; i < temporary.size(); ++i) {
        if (temporary[i] == d) {
            temporary.erase(temporary.begin() + i);
            return out;
        }
    }    
    return out;
}
void Object::UpdateNonNativeReference(Object * d, uint32_t index) {
    //if (d->IsNative()) return;
    d->data->ForceNative();
    while(data->nonNatives.size() <= index) data->nonNatives.push_back(nullptr);
    data->nonNatives[index] = d;

    // defers destruction of temporary
    // they will be reposted to destruction on this objects destructor
    for(uint32_t i = 0; i < temporary.size(); ++i) {
        if (temporary[i] == d) {
            temporary.erase(temporary.begin() + i);
            return;
        }
    }
}

Object * Object::GetNonNativeReference(uint32_t index) const {
    while(data->nonNatives.size() <= index) data->nonNatives.push_back(nullptr);
    return data->nonNatives[index];    
}





Primitive Object::CallMethod(const std::string & str, const std::vector<Primitive> & args) {
    v8::HandleScope scope;
    v8::Persistent<v8::Object> fn;
    
 

    if (str.size()) {
        v8::Handle<v8::Value> pre = data->reference->Get(v8::String::New(str.c_str()));
        if (!(!pre.IsEmpty() && pre->IsObject())) {
            // throw error?
            return Primitive();
        }
        fn = v8::Persistent<v8::Object>::New(pre->ToObject());

    } else {
        fn = v8::Persistent<v8::Object>::New(data->reference->ToObject());
    }
    
    if (!fn->IsCallable() || fn.IsEmpty()) {
        return Primitive();
    }
    if (fn->IsUndefined()) return Primitive();


    v8::String::Utf8Value fnName(fn->ToString());
    printf("FUNCTION CALLMETHOD %s \n", *fnName);
    fflush(stdout);

    v8::Handle<v8::Value> result;
    if (args.size()) {
        v8::Handle<v8::Value> args_conv[args.size()];
        for(uint32_t i = 0; i < args.size(); ++i) {
            args_conv[i] = sandboxe_primitive_to_v8_value(args[i]);
        }
        
        result = fn->CallAsFunction(
            data->reference,
            args.size(),
            &args_conv[0]
        );
    } else {
        result = fn->CallAsFunction(
            data->reference,
            0,
            nullptr
        );

    }
    
    if (!(!result.IsEmpty() && !result->IsUndefined())) return Primitive();
    std::string out = *v8::String::Utf8Value(result) ? std::string(*v8::String::Utf8Value(result)) : "";
    if (out.size()) {
        return Primitive(std::string(out));
    }
    return Primitive();
}

bool Object::IsNative() const {
    return data->isNative;
}

int Object::GetTypeID() const {
    return data->typeData->typeID;
}




void Sandboxe::Script::Runtime::ScriptError(const std::string & str) {
    v8::ThrowException(v8::String::New(str.c_str()));
}


void Sandboxe::Script::Runtime::PerformGarbageCollection() {
    for(uint32_t i = 0; i < temporary.size(); ++i) {
        if (!temporary[i]) continue;
        
        // making weak 
        //temporary[i]->GetNative()->reference.MakeWeak(temporary[i]->GetNative(), sandboxe_v8_object_garbage_collect);
        temporary[i] = nullptr;
    }
    temporary.clear();

    
    // TODO:
    // cleanup schemes
    // reorganizations

}


void Sandboxe::Script::Runtime::CheckAndHandleErrors() {
    if (global->exceptionHandler.HasCaught()) {
        script_exception_handler(&global->exceptionHandler);
        global->exceptionHandler.Reset();
    }
}



