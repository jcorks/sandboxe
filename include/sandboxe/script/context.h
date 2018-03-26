#ifndef h_sandboxe_context_included
#define h_sandboxe_context_included

#include <string>

namespace Sandboxe {
namespace Script {
namespace Context {


// initializes the scripting context
void Initialize();

// executes raw script code. Result is returned
std::string Execute(const std::string & code, const std::string & name = "_anonymous");

// Loads a script file
void Load(const std::string & path);
    
}    
}
}


#endif