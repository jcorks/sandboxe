#include <sandboxe/script/runtime.h>
#include <sandboxe/entity/terminal.h>
#include <sandboxe/script/shell.h>
#include <Dynacoe/Library.h>
#include <Dynacoe/RawData.h>

#include <v8.h>

#include <map>

using Sandboxe::Script::Runtime::Function;
using Sandboxe::Script::Runtime::Object;
using Sandboxe::Script::Runtime::Primitive;
using Sandboxe::Script::Runtime::Context;
using Sandboxe::Script::Runtime::NativeRef;



struct SandboxeContextModel {
    v8::Persistent<v8::Context> context;
    v8::Handle<v8::Object> sandboxeJS;
    Object * contextObject;
    Dynacoe::Entity::ID terminal;
    std::map<std::string, Function> functions;
};


// stored type information for objects
struct Type {
    // name of the type
    std::string name;

    // Handle to the v8-mirrored object template
    v8::Persistent<v8::ObjectTemplate> self;

    // List of native functions, mapped by name
    std::map<std::string, Function> functions;
    
    // List of nativeProperty handliers, mapped by name
    std::map<std::string, std::pair<Function, Function>> natives;
};


// Native reference to a Runtime::Object
struct NativeRef {
    // v8 handle representing this object.
    v8::Persistent<v8::Object> reference;
    
    // Pointer to the type of this object
    Type * typeData;
    
    // Object reference that owns this NativeRef
    Object * parent;
    
    // Indexed arbitrary native data.
    std::vector<void*> userData;
};




// Define to specific where scopes start and end
#define SANDBOXE_SCOPE v8::HandleScope v8_handleScope


static SandboxeContextModel * global = nullptr;

// Table of all objects. Since v8 doesnt seem to send events for object cleanup,
// this has to be cleaned out every now and then
Dynacoe::Table<NativeRef*> objects;

// Table of all types. 
std::map<std::string, Type *> types;



//////////////////////////////////////
/// Native helpers
/////////////////////////////////

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
    }
    return v8::String::New(std::string(p).c_str());
}


static std::vector<Primitive> v8_arguments_to_sandboxe_primitive_array(const v8::Arguments & args) {
    std::vector<Primitive> arguments;
    for(uint32_t i = 0; i < args.Length(); ++i) {

        // collect native objects 
        if (args[i]->IsObject()) {
            v8::Handle<v8::Object> object = args[i]->ToObject();
            if (object->InternalFieldCount())
                arguments.push_back(
                    (
                        (NativeRef*)object->GetPointerFromInternalField(0)
                    )->parent
                );            
            else {
                /// SOMETHING
                arguments.push_back(*v8::String::Utf8Value(args[i]) ? Primitive(std::string(*v8::String::Utf8Value(args[i]))) : Primitive());
            }
        } else {
            arguments.push_back(*v8::String::Utf8Value(args[i]) ? Primitive(std::string(*v8::String::Utf8Value(args[i]))) : Primitive());
        }
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



static v8::Handle<v8::Value> sandboxe_v8_native__accessor_get(v8::Local<v8::String> name, const v8::AccessorInfo & info) {
    SANDBOXE_SCOPE;
    NativeRef * ref = (NativeRef*) info.This()->GetPointerFromInternalField(0);
    Context context;
    ref->typeData->natives[*v8::String::Utf8Value(name)].first(
        ref->parent,
        {},
        context
    );
    return sandboxe_context_get_return_value(context);
}

static void sandboxe_v8_native__accessor_set(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo & info) {
    SANDBOXE_SCOPE;
    NativeRef * ref = (NativeRef*) info.This()->GetPointerFromInternalField(0);
    std::vector<Primitive> arguments;
    Context context;
    arguments.push_back(*v8::String::Utf8Value(value) ? Primitive(std::string(*v8::String::Utf8Value(value))) : Primitive());
    std::string into = *v8::String::Utf8Value(name);
    ref->typeData->natives[into].second(
        ref->parent,
        arguments,
        context
    );
}

static v8::Handle<v8::Value> sandboxe_v8_native__invocation(const v8::Arguments & args) {
    // arguments should have reference to original object;
    SANDBOXE_SCOPE;
    NativeRef * ref = (NativeRef*) args.Holder()->GetPointerFromInternalField(0);
    Context context;
    std::vector<Primitive> arguments = v8_arguments_to_sandboxe_primitive_array(args);

        
    std::string into = *v8::String::Utf8Value(args.Callee()->GetName());
    ref->typeData->functions[into](
        ref->parent,
        arguments,
        context
    );
    
    return sandboxe_context_get_return_value(context);

}

// globals functions defined at initialization
static v8::Handle<v8::Value> sandboxe_v8_native__global_incovation(const v8::Arguments & args) {
    SANDBOXE_SCOPE;
    Function f = (Function)(Dynacoe::Chain() << *v8::String::Utf8Value(args.Data())).AsUInt64();

    v8::TryCatch try_catch;
    Sandboxe::Script::Runtime::Context context;
    std::vector<Primitive> arguments = v8_arguments_to_sandboxe_primitive_array(args);
    
    // gather native objects if applicable
    f(nullptr, arguments, context);


    return sandboxe_context_get_return_value(context);



}














// loads a new script file
static v8::Handle<v8::Value> script_include(const v8::Arguments & args) {
    v8::HandleScope scopeMonitor;
    if (args.Length() != 1) {
        return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "Exactly one arg, dummy\n").ToString().c_str()));
    }
    
    
    v8::String::Utf8Value path(args[0]);
    Dynacoe::AssetID id = Dynacoe::Assets::Load("", *path);
    if (!id.Valid()) {
        return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "File " << *path << " could not be accessed.\n").ToString().c_str()));
    }
    
    // retrieve full string
    Dynacoe::RawData & data = Dynacoe::Assets::Get<Dynacoe::RawData>(id);
    char * rawStr = new char[data.GetSize()+1];
    rawStr[data.GetSize()] = 0;
    memcpy(rawStr, data.GetPtr(), data.GetSize());
    
    
    // execute the script
    Sandboxe::Script::Runtime::Execute(rawStr);
        //delete[] rawStr;
        //return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "File " << *path << " could not be accessed.\n").ToString().c_str()));
    
    delete[] rawStr;
    
    
    return v8::Undefined();
}



// reports exceptions 
static void script_exception_handler(v8::TryCatch * tcatch) {
    v8::HandleScope scopeMonitor;
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
        << (const char*)*filename << ", line " << linenum << ": " << rawString << "\n"
        << (const char*)*v8::String::Utf8Value(detail->GetSourceLine()) << "\n"
    ;
    
    for(int i = 0; i < detail->GetStartColumn(); ++i)
        message << " ";
        
    for(int i = detail->GetStartColumn(); i < detail->GetEndColumn(); ++i) 
        message << "^";
    
    
    
    
    
    // erroneous code
    v8::String::Utf8Value st(tcatch->StackTrace());
    if (*st) {
        message << "\nCall Stack info:\n" << (const char*)*st << "\n";
    }   
    term->ReportError(message.ToString().c_str());

}





void Sandboxe::Script::Runtime::Initialize(const std::vector<std::pair<std::string, Function>> & fns) {
    v8::HandleScope top;
    global = new SandboxeContextModel;
    global->terminal = Dynacoe::Entity::Create<Sandboxe::Script::Terminal>();
    
    v8::Handle<v8::ObjectTemplate> base = v8::ObjectTemplate::New();
    // set base functions
    base->Set(v8::String::New("__script_include"), v8::FunctionTemplate::New(script_include)); 


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


    

    // innitialize dynacoe shell extension
    Sandboxe::Script::Shell::Initialize();
    
    

    
    
}


std::string Sandboxe::Script::Runtime::Execute(const std::string & source, const std::string & name) {
    v8::HandleScope scopeMonitor;
    v8::TryCatch tcatch;
    v8::Handle<v8::String> sourceHandle = v8::String::New(source.c_str());
    v8::Handle<v8::String> nameHandle = v8::String::New(name.c_str());

    v8::Handle<v8::Script> script = v8::Script::Compile(sourceHandle, nameHandle);
    
    // compilation error
    if (script.IsEmpty()) {
        script_exception_handler(&tcatch);
        return "";
    }
    
    // runtime error
    v8::Handle<v8::Value> result = script->Run();
    if (result.IsEmpty()) {
        script_exception_handler(&tcatch);
        return "";
    }
    
    v8::String::Utf8Value resultStr(result);

    return std::string(*resultStr ? *resultStr : "<undefined>");
}

void Sandboxe::Script::Runtime::Load(const std::string & path) {
    //TODO: sanitize?
    Execute(Dynacoe::Chain() << "__script_include(\"" << path << "\");\n");
}












static std::map<std::string, Type *> typemap;


void Sandboxe::Script::Runtime::AddType(const std::string & name,
    const std::vector<std::pair<std::string, Function>> & functions,
    const std::vector<std::pair<std::string, Primitive>> & properties,
    const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties
) {
    if (types.find(name) != types.end()) {
        v8::ThrowException(v8::String::New("sandboxe script object: Type already exists..."));
        return;
    }
    SANDBOXE_SCOPE;

    Type * data = new Type;
    data->self = v8::Persistent<v8::ObjectTemplate>::New(v8::ObjectTemplate::New());
    data->self->SetInternalFieldCount(1);
    data->name = name;
    
    
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
    types[name] = data;
    
}






Object::Object(const std::string & t) {
    SANDBOXE_SCOPE;
    data = new NativeRef;
    data->typeData = types[t];
    if (data->typeData == nullptr) {
        v8::ThrowException(v8::String::New("sandboxe script object: Type does not exist"));
        objects.Insert(data);
        return;
    }
    data->parent = this;
    v8::Handle<v8::Object> obj = data->typeData->self->NewInstance();
    // set a ref to the type info
    obj->SetPointerInInternalField(0, data);

    objects.Insert(data);
    data->reference = v8::Persistent<v8::Object>::New(obj);
    data->reference.MakeWeak(nullptr, nullptr);
}

Object::~Object() {
    delete data;
}

Primitive Object::Get(const std::string & name) {
    SANDBOXE_SCOPE;
    if (data->reference.IsEmpty()) {
        v8::ThrowException(v8::String::New("sandboxe script object: Get() failed; reference is dead"));
        return Primitive();
    }
    v8::String::Utf8Value value(data->reference->Get(v8::String::New(name.c_str())));
    return (*value ? Primitive(std::string(*value)) : Primitive());
}

void Object::Set(const std::string & name, const Primitive & d) {
    SANDBOXE_SCOPE;
    if (data->reference.IsEmpty()) {
         v8::ThrowException(v8::String::New("sandboxe script object: Set() failed; reference is dead"));
    }
    data->reference->Set(
        v8::String::New(name.c_str()),
        sandboxe_primitive_to_v8_value(d)
    );

}


const std::string & Object::GetType() const {
    return data->typeData->name;
}


void Object::SetNativeAddress(void * d, uint32_t index) {
    while(data->userData.size() <= index) data->userData.push_back(nullptr);
    data->userData[index] = d;
}

void * Object::GetNativeAddress(uint32_t index) {
    while(data->userData.size() <= index) data->userData.push_back(nullptr);
    return data->userData[index];
}

Primitive Object::CallMethod(const std::string & str, const std::vector<Primitive> & args) {
    SANDBOXE_SCOPE;
    v8::Handle<v8::Value> pre = data->reference->Get(v8::String::New(str.c_str()));
    if (!(!pre.IsEmpty() && pre->IsObject())) {
        // throw error?
        return Primitive();
    }
    v8::Handle<v8::Object> fn = pre->ToObject();
    if (!fn->IsCallable()) {
        return Primitive();
    }

    v8::Handle<v8::Value> args_conv[args.size()];
    for(uint32_t i = 0; i < args.size(); ++i) {
        args_conv[i] = v8::String::New(std::string(args[i]).c_str());
    }
    v8::Handle<v8::Value> result = fn->CallAsFunction(
        data->reference,
        args.size(),
        &args_conv[0]
    );
    if (!(!result.IsEmpty() && !result->IsUndefined())) return Primitive();
    const char * out = *v8::String::Utf8Value(result);
    if (out) {
        return Primitive(std::string(out));
    }
    return Primitive();
}

void Context::ScriptError(const std::string & str) {
    v8::ThrowException(v8::String::New(str.c_str()));
}






