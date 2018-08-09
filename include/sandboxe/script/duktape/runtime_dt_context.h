#ifndef H_SANDBOXE_DT_CONTEXT_INCLUDED
#define H_SANDBOXE_DT_CONTEXT_INCLUDED

#include <sandboxe/script/runtime.h>
#include <duktape.h>

namespace Sandboxe {
namespace Script {
namespace Runtime {


// COntextual object holding state-related attributes for the duktape context 
// within sandboxe.
class DTContext {
  public:

    // constructor expects global functions to bind to the context
    DTContext();
    
    void ApplyGlobalFunctions(const std::vector<std::pair<std::string, Runtime::Function>> & natives);


    // initializes global stuff
    void InitializeGlobals();
    
    // performs the addition of a type on behalf of the general interface function
    void AddType(int typeID, 
        const std::vector<std::pair<std::string, Function>> & functions,
        const std::vector<std::pair<std::string, Primitive>> & properties,
        const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties);


    // executes ES code directly with the given context name
    std::string Execute(const std::string & code, const std::string & name);


    // Generates the given error. May longjump the program.
    void ThrowErrorObject(const std::string & err);


    // creates a new object of the given type in the heap store
    uint32_t CreateNewObject(int typeID, Object * parent);
 
    // Return context
    duk_context * GetCTX() {return source;}

    // Gets the singleton reference;
    static DTContext * Get() {return global;}
    
  private:
    duk_context * source;
    std::stack<uint32_t> dead;
    uint32_t heapIndex;
      
    static void fatal_error(void * data, const char * msg);

    void ScriptErrorMessage();
    static DTContext * global;


};


}
}
}

#endif
