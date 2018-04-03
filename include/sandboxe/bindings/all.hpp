#ifndef h_sandboxe_bindings_all_included
#define h_sandboxe_bindings_all_included

// all includes
#include "dynacoe_console.hpp"
#include "dynacoe_entity.hpp"
#include "dynacoe_component.hpp"


namespace Sandboxe {
namespace Script {

std::vector<std::pair<std::string, Runtime::Function>> GatherNativeBindings() {
    std::vector<std::pair<std::string, Runtime::Function>> out;
    Bindings::dynacoe_console(out);
    Bindings::dynacoe_entity(out);
    Bindings::dynacoe_component(out);
    return out;
}   

 
}
}

#endif