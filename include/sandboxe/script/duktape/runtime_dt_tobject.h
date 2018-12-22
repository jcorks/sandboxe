#ifndef H_SANDBOXE_DT_TOBJECT_INCLUDED
#define H_SANDBOXE_DT_TOBJECT_INCLUDED

#include <sandboxe/script/runtime.h>
#include <duktape.h> 


namespace Sandboxe {
namespace Script {
namespace Runtime {




// symbolic wrapper for the (T)opmost (Object) on the duktape stack.
// For clarity, it is helpful to place this object at the top of 
// the program stack in its own scope. THis makes it very clear 
// that it is only valid for the lifetime specified and guarantees it works 
// with the same reference.
class TObject {
  public:
    // requires teh context to work with
    TObject(duk_context * ctx);
    
    // Gets the given property as a string value as interpreted by the ES engine
    std::string Get(const std::string & str) const;

    // Gets the given property as a string value as interpreted by the ES engine
    Primitive GetAsPrimitive(const std::string & str) const;

    
    // Gets the object as a primitive
    Sandboxe::Script::Runtime::Primitive ThisAsPrimitive() const;

    
    // Sets/replaces a property with the given value.
    void Set(const std::string & str, const Primitive & data);    
    
    // Calls a function fo te given name if it exists.
    Primitive CallMethod(const std::string & str, const std::vector<Primitive> & args);
    
    
    // Sets a native function object with the given name on the top object
    void SetFunction(const std::string & str, Sandboxe::Script::Runtime::Function funcSrc);
    
    
    // Adds a managed property. Managed properties have intercepted set/get functions 
    // using the ES6 proxy feature
    void SetManagedProperty(const std::string & str, Sandboxe::Script::Runtime::Function get, Sandboxe::Script::Runtime::Function set);

    // sets a hidden property pointer that is accessible via pointer
    void MapObject(Object * value);
    void MapFunction(Function value);

    // gets a hidden mapped pointer for the object
    Object * GetMappedObject() const;
    Function GetMappedFunction() const;


    // Gets whether this object is an array. Arrays are not language-agnostic constructs,
    // so they are blanketed as ObjectReferenceNonNative unless detected and extracted using 
    // ThisAsPrimitiveArray(), which will only produce meaningful results if IsThisArray() 
    // is true.
    bool IsThisArray() const;
    
    // Returns an array of values that this obejct holds when considered as an array.
    // Due to the nature of this function, calling this function for a non-array object
    // will be indistinguishable from calling this on an empty array object. To identify whether 
    // this object is an array, use IsThisArray();
    std::vector<Primitive> ThisAsPrimitiveArray() const;
    

  private:
    duk_context * source;

    const char * PointerToHiddenKey(void * p) const;
    static duk_ret_t method_call(duk_context * source);
    static duk_ret_t native_get(duk_context * source);
    static duk_ret_t native_set(duk_context * source);
    
    

    void PushPrimitive(const Primitive & data);
    void PushPrimitiveArray(const std::vector<Primitive> & data);

};

}
}
}

#endif
