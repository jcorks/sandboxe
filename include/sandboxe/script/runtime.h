#ifndef H_SANDBOXE_BINDING_INCLUDED
#define H_SANDBOXE_BINDING_INCLUDED

#include <Dynacoe/Library.h>


namespace Sandboxe {
namespace Script {
namespace Runtime {

class Object;
struct NativeRef;

// easy type primitive data type.
// Used for all IO when working with the runtime
class Primitive {
  public:
    Primitive(); // undefined

    Primitive(bool);
    Primitive(int);
    Primitive(float);
    Primitive(double);
    Primitive(uint32_t);    
    Primitive(uint64_t);    
    Primitive(const std::string &);    
    Primitive(const Dynacoe::Entity::ID &);   

    void Modify(const Primitive & other) {*this = other;}
    const std::string & Data() {return data;}
    bool IsDefined() {return defined;}

    operator int() const;
    operator bool() const;
    operator float() const;
    operator double() const;
    operator uint32_t() const;
    operator uint64_t() const;
    operator std::string() const;
    operator Dynacoe::Entity::ID() const;
    
  private:
    std::string data;
    bool defined;
};


class Context {
  public:    
      
    // generates an error from the calling script context.
    // Behavior is implementation dependent
    void ScriptError(const std::string & str);
    
    // Sets a new Object to use as the return value of the native function
    // If set, the real return value from the native funciton is ignored and this is used instead.
    void SetReturnObject(Object * o) {returnObject = o;}
        
    Object * GetReturnObject() {return returnObject;}
  private:
    Object * returnObject;
};

// Represents a native function. Native functions usually 
// represent native code to be run when a script runs a function
typedef Primitive (*Function)(Object *, const std::vector<Primitive> & arguments, Context & context);
#define SANDBOXE_NATIVE_DEF(__T__) Sandboxe::Script::Runtime::Primitive __T__(Sandboxe::Script::Runtime::Object * source, const std::vector<Sandboxe::Script::Runtime::Primitive> & arguments, Sandboxe::Script::Runtime::Context & context)


// initializes the scripting context
// Optional argument to bind native functions to the global context
// by name
void Initialize(const std::vector<std::pair<std::string, Function>> & globalFunctions = {});

// executes raw script code. Result is returned
std::string Execute(const std::string & code, const std::string & name = "_anonymous");

// Loads a script file
void Load(const std::string & path);
    







// Adds a new template for an Object's Type
// lasts for the duration of the program
// @param functions Native functions added to the type. Script calling arguments are passed and the runtime object set given
// @param properties Initialized properties and their values.
// @param nativeProperties Properties that, when accessed, call native functions to retrieve and update native data. Getter function followed by setter function.
void AddType  (const std::string & name,
               const std::vector<std::pair<std::string, Function>> & functions,
               const std::vector<std::pair<std::string, Primitive>> & properties = {},
               const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties = {});



// A 2-way runtime object
class Object {
  public: 
    // Instantiates a new object of the given type
    Object(const std::string &);
    ~Object();   
    
    // Returns a property of the object of the given name.
    // If none such property exists, an "Undefined" primitive is returned
    Primitive Get(const std::string & name);
    
    // Sets the named runtime property with the specified data
    void Set(const std::string & name, const Primitive &);
        
    // Returns the type that the object was instantiated with
    const std::string & GetType() const;
    
    // Sets data associated with the object only retrievable 
    // through GetNativeAddress();
    void SetNativeAddress(void * data, uint32_t index = 0);

    // Retrieves the indexed data set with
    // SetNativeAddress()
    void * GetNativeAddress(uint32_t index = 0);
    
    NativeRef * GetNative() {return data;}
  private:
    Object(void *);
    NativeRef * data;
};

// call occasionally to cleanup built-up data generated for management 
// of communicating with the scripting language
void PerformGarbageCollection();



    
}
}
}


#endif