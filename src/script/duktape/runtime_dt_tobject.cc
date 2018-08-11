#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <sandboxe/script/duktape/runtime_dt_object.h>
#include <sandboxe/script/duktape/runtime_dt_context.h>
#include <cassert>
#include <duktape.h> 

using namespace Sandboxe::Script::Runtime;



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
        duk_push_string(source, name.c_str());
        for(uint32_t i = 0; i < args.size(); ++i) {
            PushPrimitive(args[i]);
        }
        if (duk_pcall_prop(source, (-1*(int)args.size()) - 2, args.size()) != DUK_EXEC_SUCCESS) {
            duk_pop(source); // failure ignore;
            assert(stackSz == duk_get_top(source));
            return Primitive();
        } else {
            Primitive out = ThisAsPrimitive(); // the return value is at the top of the stack, so we can return it!
            duk_pop(source); // retval
            assert(stackSz == duk_get_top(source));
            return out;
        }
    } else {     // Self call!
        if (!duk_is_callable(source, -1)) {
            duk_pop(source); // failure ignore;
            //DTContext::Get()->ThrowErrorObject(std::string() + "\"" + name + "\" is not a callable object.");
            return Primitive();
        }
        for(uint32_t i = 0; i < args.size(); ++i) {
            PushPrimitive(args[i]);
        }
        if (duk_pcall(source, args.size()) != DUK_EXEC_SUCCESS) {
            assert(stackSz == duk_get_top(source));
            return Primitive();
        } else {
            Primitive out = ThisAsPrimitive(); // the return value is at the top of the stack, so we can return it!
            duk_pop(source); // retval
            assert(stackSz == duk_get_top(source));
            return out;
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
        func.MapPointer((void*)0x1, (void*)funcSrc);

    }
    duk_put_prop_string(source, -2, str.c_str());
    assert(stackSz == duk_get_top(source)); 
}


// Adds a managed property. Managed properties have intercepted set/get functions 
// using the ES6 proxy feature
void TObject::SetManagedProperty(const std::string & str, Sandboxe::Script::Runtime::Function set, Sandboxe::Script::Runtime::Function get) {
    int stackSz = (duk_get_top(source));

    // uses proxy functionality 
    duk_dup_top(source); // copy the object at the top (since making the proxy will consume it)
    duk_push_object(source); // handler (not used)

    // set proxy target attributes (target should just capture it)
    duk_push_c_function(source, native_set, 4);
    duk_put_prop_string(source, -2, "set");
    
    duk_push_c_function(source, native_get, 3);
    duk_put_prop_string(source, -2, "get");
    
    duk_push_proxy(source, 0);
    duk_pop(source); // we dont need the ref really
    assert(stackSz == duk_get_top(source));

}


// sets a hidden property pointer that is accessible via pointer
void TObject::MapPointer(void * key, void * value) {
    int stackSz = (duk_get_top(source));

    duk_push_pointer(source, value);
    duk_put_prop_string(source, -2, PointerToHiddenKey(key));
    

    assert(stackSz == duk_get_top(source));                
}

// gets a hidden mapped pointer for the object
void * TObject::GetMappedPointer(void * key) const {
    int stackSz = (duk_get_top(source));

    duk_get_prop_string(source, -1, PointerToHiddenKey(key));      
    void * prop = duk_to_pointer(source, -1); 
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
            Object * ref = (Object*)GetMappedPointer((void*)(0x1));
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


const char * TObject::PointerToHiddenKey(void * p) const {
    static char holder[34];
    snprintf(holder, 34, "\xFF%p", p);
    return holder;
}




// A normal native call. Is the entry point for all 
// function defined by the user.
duk_ret_t TObject::method_call(duk_context * source) {
    int args = duk_get_top(source);
    std::vector<Primitive> argsConverted;
    for(uint32_t i = 0; i < args; ++i) {
        duk_dup(source, i);
        {
            TObject arg(source);
            argsConverted.push_back(arg.ThisAsPrimitive());
        }
        duk_pop(source);

        Dynacoe::Console::Info() << "ARG" << i << ":" << argsConverted[i].Data() << "\n";
    }


    duk_push_current_function(source);
    Function f;
    {
        TObject thisFunction(source);
        f = (Function)thisFunction.GetMappedPointer((void*)0x1);
    }
    Sandboxe::Script::Runtime::Context context;
    f(nullptr, argsConverted, context);


    // TODO: need to handle arrays
    duk_push_string(source, context.GetReturnValue().Data().c_str());
    Object_Internal::SweepTemporaryObjects();

    return 1;
}

// the standard get interceptor
// targ: underlying plain object (= target, above)
// key: key (can be any value, not just a string)
// recv: object being read from (= the proxy object)
duk_ret_t TObject::native_get(duk_context * source) {
    // first get the source object
    Object * ref;
    {
        TObject obj(source);
        ref = (Object*)obj.GetMappedPointer((void*)0x1);
    }
    assert(ref);    
    duk_pop(source);
    

    // get the function to run from the ES function object
    duk_push_current_function(source);
    Function f;
    {
        TObject thisFunction(source);
        f = (Function)thisFunction.GetMappedPointer((void*)0x1);
    }
    Sandboxe::Script::Runtime::Context context;
    f(ref, {}, context);
    
    // since this is a get interceptor, the return value is 
    // essential
    TObject pushr(source);
    pushr.PushPrimitive(context.GetReturnValue());
    return 1;
}


// the standard set interception function.
// targ: underlying plain object (= target, above)
// key: key (can be any value, not just a string)
// val: value
// recv: object being read from (= the proxy object)
duk_ret_t TObject::native_set(duk_context * source) {
    // now that the object callee is at the top of the stack, 
    // lets extract that mapped pointer!
    Object * ref;
    {
        TObject obj(source);
        ref = (Object*)obj.GetMappedPointer((void*)0x1);
    }
    assert(ref);        
    duk_pop(source); // skip the recv argument

    std::vector<Primitive> argsConverted;
    // last argument should be the value, so get it immediately
    {
        TObject arg(source);
        argsConverted.push_back(arg.ThisAsPrimitive());
    }
    duk_pop(source);

    // the top object at this point is the property name, which we dont 
    // really use!
    duk_pop(source); // key



    // get the function to run from the ES function object
    duk_push_current_function(source);
    Function f;
    {
        TObject thisFunction(source);
        f = (Function)thisFunction.GetMappedPointer((void*)0x1);
    }
    Sandboxe::Script::Runtime::Context context;
    f(ref, argsConverted, context);
    
    // since this is a set interceptor, we dont need the return value..
    // but the proxy set function expects a "was this write accepted"
    // value, which we always return as true (for now);
    duk_push_boolean(source, true);
    return 1;
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
        DTContext::Get()->PushHeapEntryToDTTop(obj->GetNative()->GetHeapStoreIndex());
        break;
      }
      default: duk_push_string(source, "");
    }

}

