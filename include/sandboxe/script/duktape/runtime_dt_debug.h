#ifndef H_SANDBOXE_DT_DEBUG_INCLUDED
#define H_SANDBOXE_DT_DEBUG_INCLUDED
#include "runtime_dt_context.h"
#include <duktape.h>


#if defined(SANDBOXE_DT_DEBUG)

namespace Sandboxe {
namespace Script {
namespace Runtime {


// Allows for debugging of the duktape context. Debugging traps the 
// current callstack
class DTDebugger {
  public:
    DTDebugger(DTContext *);

    std::string GetBacktraceString() const;


    void Pause();

    void Resume();

    void StepInto();
    
    void StepOver();
    
    void StepOut();
    
    void AddBreak(const std::string & filename, int line);
    
    
    
    
    int GetCurrentLine() const;

    std::string GetCurrentFile() const;
  private:
    DTContext * ctx;
    bool paused;
};  


}
}
}


#endif
#endif
