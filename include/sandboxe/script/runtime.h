#ifndef H_SANDBOXE_BINDING_INCLUDED
#define H_SANDBOXE_BINDING_INCLUDED

#include <Dynacoe/Library.h>


namespace Sandboxe {
namespace Script {
namespace Runtime {

class Object;


// easy type primitive data type.
// Used for all IO when working with the runtime
class Primitive {
  public:
    class Object;
    enum class TypeHint {
        IntegerT,
        BooleanT,
        FloatT,
        DoubleT,
        UInt32T,
        UInt64T,
        StringT,
        ObjectReferenceT,
        ObjectReferenceNonNativeT
    };
    Primitive(); // undefined

    Primitive(bool);
    Primitive(int);
    Primitive(float);
    Primitive(double);
    Primitive(uint32_t);    
    Primitive(uint64_t);    
    Primitive(const std::string &);    
    Primitive(Sandboxe::Script::Runtime::Object *);

    void Modify(const Primitive & other) {*this = other;}
    const std::string & Data() const {return data;}
    bool IsDefined() const {return defined;}
    TypeHint hint;

    operator int() const;
    operator bool() const;
    operator float() const;
    operator double() const;
    operator uint32_t() const;
    operator uint64_t() const;
    operator std::string() const;
    operator Sandboxe::Script::Runtime::Object *() const;
    
  private:
    // TODO: optimize copy constructor and assignment operator to avoid 
    // string copy if not needed.
    std::string data;
    int64_t intData;
    bool defined;
    bool nsu;
    double fltData;
    Sandboxe::Script::Runtime::Object * objectData;
    
};


class Context {
  public: Context() : inputArray(nullptr), isArray(false) {}
    ~Context();

    
    // Gets the n'th argument as an array, if it exists.
    std::vector<Primitive> * GetArrayArgument(uint32_t argument);
    
    void SetArrayArgument(uint32_t arg, const std::vector<Primitive> &);
    // sets the return value for the native function.
    // If the primitive
    void SetReturnValue(const Primitive & v) {value = v; isArray = false;}
        
    // Sets an array of primitives to be returned by the function rather 
    // than the simple primitive
    void SetReturnArray(const std::vector<Primitive> & arr) { returnArray = arr; isArray = true;} 
        
    // Gets the return value set
    const Primitive & GetReturnValue() const {return value;}

    // gets the return value set
    const std::vector<Primitive> & GetReturnArray() const {return returnArray;}

    // returns whether isArray is set
    bool ReturnsArray() const {return isArray;}


    
    
  private:
    Primitive value;
    std::vector<Primitive> returnArray;
    std::vector<std::vector<Primitive>> * inputArray;
    int isArray;
};


// Represents a native function. Native functions usually 
// represent native code to be run when a script runs a function
typedef void (*Function)(Object *, const std::vector<Primitive> & arguments, Context & context);
#define SANDBOXE_NATIVE_DEF(__T__) void __T__(Sandboxe::Script::Runtime::Object * source, const std::vector<Sandboxe::Script::Runtime::Primitive> & arguments, Sandboxe::Script::Runtime::Context & context)
#define SANDBOXE_NATIVE_EMPTY Sandboxe::Script::Runtime::Empty
void Empty(Sandboxe::Script::Runtime::Object * source, const std::vector<Sandboxe::Script::Runtime::Primitive> & arguments, Sandboxe::Script::Runtime::Context & context);





///// BEGIN LANGUAGE-DEPENDENT BEHAVIOR



// initializes the scripting context
// 
void Initialize();

// begins the main loop
void Start();

// executes raw script code. Result is returned
std::string Execute(const std::string & code, const std::string & name = "<Sandboxe>");

// Loads a script file
void Load(const std::string & path);

// generates an error from the calling script context.
// Behavior is implementation dependent
void ScriptError(const std::string & str);


// Attempts to get debugging information of the current calling context.
// No guarantee on the contents of the string. Some imeplementations may choose 
// not to implement this function for security reasons or limitations.
std::string GetContextInfo();

// call occasionally to cleanup built-up data generated for management 
// of communicating with the scripting language
void PerformGarbageCollection();

void CheckAndHandleErrors();

    



// Adds a new template for an Object's Type
// lasts for the duration of the program
// @param functions Native functions added to the type. Script calling arguments are passed and the runtime object set given
// @param properties Initialized properties and their values.
// @param nativeProperties Properties that, when accessed, call native functions to retrieve and update native data. Getter function followed by setter function.
void AddType  (int typeID,
               const std::vector<std::pair<std::string, Function>> & functions,
               const std::vector<std::pair<std::string, Primitive>> & properties = {},
               const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties = {});



// A 2-way runtime object
struct Object_Internal;
class Object {
  public: 
    // Instantiates a new object of the given type
    Object(int typeID);
    Object(Object_Internal &);
    virtual ~Object();
    
    // creates a new object based on the current object's value.
    Object(const Object*);

    
    // Returns a property of the object of the given name.
    // If none such property exists, an "Undefined" primitive is returned
    Primitive Get(const std::string & name);
    
    // Sets the named runtime property with the specified data
    void Set(const std::string & name, const Primitive &);
    
    // Calls the given method. If name is blank, the 
    // object itself is attempted to be called as a function
    Primitive CallMethod(const std::string & name = "", const std::vector<Primitive> & args = {});
    
    bool IsCallable() const;
    
    // Returns whether the object is native. NonNative objects 
    // have restricted functionality.
    bool IsNative() const;
    
    Object_Internal * GetNative() {return data;}
    
    int GetTypeID() const;

    
    
    // callback, if set, called when the script runtime reference 
    // of the object has been removed
    virtual void OnGarbageCollection(){};

    // Returns the type that the object was instantiated with
    virtual const char * GetObjectName(){return "Object";}

    // Makes this object the owner of ref. In garbage collected 
    // languages, this adds a reference count from the ownership 
    // to guarantee the validity of this reference. THe normal 
    // use of this function is to capture local / script-sourced 
    // references and preserve them. If another object has already claimed 
    // ref, it is reparented to this object.
    uint32_t AddNonNativeReference(Object * ref);

    // Sets data associated with the object only retrievable 
    // through GetNonObject_Internalerence();
    // If the given object is native, no action is taken
    void UpdateNonNativeReference(Object *, uint32_t index = 0);

    // Sets data associated with the object only retrievable 
    // through GetNonObject_Internalerence();
    Object * GetNonNativeReference(uint32_t index = 0) const;


  protected:


        
  private:
    Object_Internal * data;
    
};


}
}
}


#endif
