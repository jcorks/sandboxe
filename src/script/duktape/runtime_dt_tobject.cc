#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <sandboxe/script/duktape/runtime_dt_object.h>
#include <sandboxe/script/duktape/runtime_dt_context.h>
#include <cassert>
#include <duktape.h> 

using namespace Sandboxe::Script::Runtime;

const char * hidden_key_object   = "\xFFSBO";
const char * hidden_key_function = "\xFFSBF";




TObject::TObject(duk_context * ctx) : source(ctx) {
    assert(duk_get_top(source));
}

// Gets the given property as a string value as interpreted by the ES engine
std::string TObject::Get(const std::string & str) const {
    int stackSz = (duk_get_top(source));

    duk_get_prop_string(source, -1, str.c_str());      
    const char * prop = duk_safe_to_string(source, -1); 
    std::string out(prop ? prop : "");
    duk_pop(source);

    assert(stackSz == duk_get_top(source));
    return out;
}

Primitive TObject::GetAsPrimitive(const std::string & str) const {
    int stackSz = (duk_get_top(source));

    duk_get_prop_string(source, -1, str.c_str());      
    TObject top(source);
    Primitive out = top.ThisAsPrimitive();
    duk_pop(source);

    assert(stackSz == duk_get_top(source));
    return out;
}


Primitive TObject::CallMethod(const std::string & name, const std::vector<Primitive> & args) {
    int stackSz = (duk_get_top(source));

    if (name.size()) { // method / member call!
        duk_get_prop_string(source, -1, name.c_str());
        Primitive out = CallMethod("", args);
        duk_pop(source);
        assert(stackSz == duk_get_top(source));

        return out;
    } else {     // Self call!
        
        if (!duk_is_callable(source, -1)) {
            //DTContext::Get()->ThrowErrorObject(std::string() + "\"" + name + "\" is not a callable object.");
            assert(stackSz == duk_get_top(source));
            return Primitive();
        }
        // pcall consumes the object itself even in error.
        duk_dup(source, -1);
        for(uint32_t i = 0; i < args.size(); ++i) {
            PushPrimitive(args[i]);
        }
        if (duk_pcall(source, args.size()) != DUK_EXEC_SUCCESS) {
            DTContext::Get()->ProcessErrorObject();
            assert(stackSz == duk_get_top(source));
            return Primitive();
        } else if (stackSz != duk_get_top(source)) { // return value
            Primitive out = ThisAsPrimitive(); // the return value is at the top of the stack, so we can return it!
            duk_pop(source); // retval
            assert(stackSz == duk_get_top(source));
            return out;
        } else { // no return value!
            return Primitive();
        }
        
    }
    return Primitive();
}

// Sets/replaces a property with the given value.
void TObject::Set(const std::string & str, const Primitive & data) {
    int stackSz = (duk_get_top(source));
    PushPrimitive(data);
    duk_put_prop_string(source, -2, str.c_str());
    assert(stackSz == duk_get_top(source)); 
}



// Sets a native function object with the given name on the top object
void TObject::SetFunction(const std::string & str, Sandboxe::Script::Runtime::Function funcSrc) {
    int stackSz = (duk_get_top(source));
    duk_push_c_function(source, method_call, DUK_VARARGS);
    {
        // associate the function pointer with the data itself
        TObject func(source);
        func.MapFunction(funcSrc);

    }
    duk_put_prop_string(source, -2, str.c_str());
    assert(stackSz == duk_get_top(source)); 
}


bool TObject::IsThisArray() const {
    return duk_is_array(source, -1);
}

std::vector<Primitive> TObject::ThisAsPrimitiveArray() const {
    int stackSz = (duk_get_top(source));
    std::vector<Primitive> out;
    uint32_t length = duk_get_length(source, -1);
    for(uint32_t i = 0; i < length; ++i) {
        duk_get_prop_index(source, -1, i);
        out.push_back(ThisAsPrimitive());
        duk_pop(source);        
    }
    assert(stackSz == duk_get_top(source)); 
    return out;
}

// Adds a managed property. Managed properties have intercepted set/get functions 
// using the ES6 proxy feature
void TObject::SetManagedProperty(const std::string & str, Sandboxe::Script::Runtime::Function get, Sandboxe::Script::Runtime::Function set) {
    int stackSz = (duk_get_top(source));
    auto src = ThisAsPrimitive();
    assert(
        src.hint == Sandboxe::Script::Runtime::Primitive::TypeHint::ObjectReferenceT ||
        src.hint == Sandboxe::Script::Runtime::Primitive::TypeHint::ObjectReferenceNonNativeT
    );
    Object * obj = src;


    // uses ES5 define property mechanism
    duk_push_string(source, str.c_str());
    
    duk_push_c_function(source, native_get, 0);
    {
        TObject func(source);
        func.MapObject  (obj);
        func.MapFunction(get);
    }

    duk_push_c_function(source, native_set, 1);
    {
        TObject func(source);
        func.MapObject  (obj);
        func.MapFunction(set);
    }



    
    // default: configurable: false, enumerable: false
    duk_def_prop(
        source, 
        -4,
        DUK_DEFPROP_HAVE_GETTER |
        DUK_DEFPROP_HAVE_SETTER
    );
    
    assert(stackSz == duk_get_top(source));

}


// sets a hidden property pointer that is accessible via pointer
void TObject::MapFunction(Function value) {
    int stackSz = (duk_get_top(source));

    duk_push_pointer(source, (void*)value);
    duk_put_prop_string(source, -2, hidden_key_function);
    

    assert(stackSz == duk_get_top(source));                
}

void TObject::MapObject(Object * value) {
    int stackSz = (duk_get_top(source));

    duk_push_pointer(source, (void*)value);
    duk_put_prop_string(source, -2, hidden_key_object);
    

    assert(stackSz == duk_get_top(source));                
}


// gets a hidden mapped pointer for the object
Function TObject::GetMappedFunction() const {
    int stackSz = (duk_get_top(source));

    duk_get_prop_string(source, -1, hidden_key_function);      
    Function prop = (Function)duk_to_pointer(source, -1); 
    duk_pop(source);
    

    assert(stackSz == duk_get_top(source));
    return prop;
}

Object * TObject::GetMappedObject() const {
    int stackSz = (duk_get_top(source));

    duk_get_prop_string(source, -1, hidden_key_object);      
    Object * prop = (Object*)duk_to_pointer(source, -1); 
    duk_pop(source);
    

    assert(stackSz == duk_get_top(source));
    return prop;
}




Sandboxe::Script::Runtime::Primitive TObject::ThisAsPrimitive() const {
    switch(duk_get_type(source, -1)) {
        case DUK_TYPE_NONE:      return Primitive();
        case DUK_TYPE_UNDEFINED: return Primitive();
        case DUK_TYPE_NULL:      return Primitive();
        case DUK_TYPE_BOOLEAN:   return Primitive(duk_get_boolean(source, -1));
        case DUK_TYPE_NUMBER:    return Primitive(duk_get_number(source, -1));
        case DUK_TYPE_STRING:    return Primitive(std::string(duk_get_string(source, -1)));
        case DUK_TYPE_OBJECT: {
            Object * ref = GetMappedObject();
            if (ref) // native ref 
                return Primitive(ref);

            // non-native ref. Needs a temporary native object
            return Primitive(Object_Internal::CreateTemporaryObjectFromStackTop());
        }
        case DUK_TYPE_BUFFER:    return Primitive(); // no generic implementation
        case DUK_TYPE_POINTER:   return Primitive(); // hidden property
        case DUK_TYPE_LIGHTFUNC: return Primitive(std::string(duk_get_string(source, -1))); // function?

    }


    return Primitive();
}




// A normal native call. Is the entry point for all 
// function defined by the user.
duk_ret_t TObject::method_call(duk_context * source) {
    int args = duk_get_top(source);
    Sandboxe::Script::Runtime::Context context;
    std::vector<Primitive> argsConverted;
    for(uint32_t i = 0; i < args; ++i) {
        duk_dup(source, i);
        {
            TObject arg(source);
            argsConverted.push_back(arg.ThisAsPrimitive());

            if (arg.IsThisArray()) {
                context.SetArrayArgument(i, arg.ThisAsPrimitiveArray());
            }

        }
        duk_pop(source);

        //Dynacoe::Console::Info() << "ARG" << i << ":" << argsConverted[i].Data() << "\n";
    }

    // get the source if possible
    Object * ref = nullptr;
    duk_push_this(source);
    if (!duk_is_undefined(source, -1)) {
        TObject obj(source);
        ref = obj.GetMappedObject();
    }
    duk_pop(source);

    duk_push_current_function(source);
    Function f;
    {
        TObject thisFunction(source);
        f = thisFunction.GetMappedFunction();
    }
    f(ref, argsConverted, context);


    // TODO: need to handle arrays
    TObject pushr(source);
    if (context.ReturnsArray()) {
        pushr.PushPrimitiveArray(context.GetReturnArray());
    } else {
        pushr.PushPrimitive(context.GetReturnValue());
    }
    Object_Internal::SweepTemporaryObjects();
    return 1;
}

// the standard get interceptor
// Through ES5 define property gets, no arguments are given
duk_ret_t TObject::native_get(duk_context * source) {
    // first get the source object
    duk_push_current_function(source);
    Object * ref;
    Function f;
    {
        TObject obj(source);
        ref = (Object*)          obj.GetMappedObject  ();
        f   = (Function)         obj.GetMappedFunction();
    }
    assert(ref);    
    TObject pushr(source);

    duk_pop(source);
    Sandboxe::Script::Runtime::Context context;
    f(ref, {}, context);

        
    // since this is a get interceptor, the return value is 
    // essential
    if (context.ReturnsArray()) {
        pushr.PushPrimitiveArray(context.GetReturnArray());
    } else {
        pushr.PushPrimitive(context.GetReturnValue());
    }
    return 1;
}


// the standard set interception function. Through ES define property
// one argument is given
duk_ret_t TObject::native_set(duk_context * source) {
    // now that the object function is at the top of the stack, 
    // lets extract that mapped pointer!
    duk_push_current_function(source);
    Object * ref;
    Function f;
    {
        TObject obj(source);
        ref = (Object*)          obj.GetMappedObject  ();
        f   = (Function)         obj.GetMappedFunction();
    }
    duk_pop(source);
    assert(ref);        

    Sandboxe::Script::Runtime::Context context;
    std::vector<Primitive> argsConverted;
    // last argument should be the value, so get it immediately
    {
        TObject arg(source);
        argsConverted.push_back(arg.ThisAsPrimitive());

        if (arg.IsThisArray()) {
            context.SetArrayArgument(0, arg.ThisAsPrimitiveArray());
        }
    }
    duk_pop(source);



    f(ref, argsConverted, context);
    
    return 0;
}



void TObject::PushPrimitive(const Primitive & data) {
    int stackSz = (duk_get_top(source));
    switch(data.hint) {
      case Primitive::TypeHint::BooleanT: duk_push_boolean(source, (bool)data); break;
      case Primitive::TypeHint::IntegerT: 
      case Primitive::TypeHint::FloatT:   
      case Primitive::TypeHint::DoubleT:
      case Primitive::TypeHint::UInt32T: 
      case Primitive::TypeHint::UInt64T: duk_push_number(source, data); break;
      case Primitive::TypeHint::StringT: duk_push_string(source, data.Data().c_str()); break;
      case Primitive::TypeHint::ObjectReferenceT:      
      case Primitive::TypeHint::ObjectReferenceNonNativeT: {
        Object * obj = data;
        duk_push_heapptr(source, obj->GetNative()->GetHeapStorePointer());
        //DTContext::Get()->PushHeapEntryToDTTop(obj->GetNative()->GetHeapStoreIndex());
        break;
      }
      default: duk_push_string(source, "");
    }

}


void TObject::PushPrimitiveArray(const std::vector<Primitive> & array) {
    int index = duk_push_array(source);
    uint32_t len = array.size();
    for(uint32_t i = 0; i < len; ++i) {
        PushPrimitive(array[i]);
        duk_put_prop_index(source, index, i);
    }
}

