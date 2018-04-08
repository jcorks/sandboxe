#ifndef h_sandboxe_bindings_all_included
#define h_sandboxe_bindings_all_included

// all includes
#include "dynacoe_console.hpp"
#include "dynacoe_entity.hpp"
#include "dynacoe_component.hpp"
#include "dynacoe_vector.hpp"
#include "dynacoe_node_transform.hpp"
#include "dynacoe_node.hpp"
#include "dynacoe_engine.hpp"

namespace Sandboxe {
namespace Script {

std::vector<std::pair<std::string, Runtime::Function>> GatherNativeBindings() {
    std::vector<std::pair<std::string, Runtime::Function>> out;
    Bindings::dynacoe_console(out);
    Bindings::dynacoe_entity(out);
    Bindings::dynacoe_component(out);
    Bindings::dynacoe_vector(out);
    Bindings::dynacoe_node_transform(out);
    Bindings::dynacoe_node(out);
    Bindings::dynacoe_engine(out);

    return out;
}   

 
}
}

#endif