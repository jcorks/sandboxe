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


    static void RegisterFile(const std::string & stringName, const std::string & data);

    static void ReportError(const std::string &);
        
  private:
    DTContext * ctx;
};  


}
}
}


#endif
#endif
