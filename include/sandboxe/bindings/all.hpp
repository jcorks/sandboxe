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
#include "dynacoe_input.hpp"
#include "dynacoe_assets.hpp"
#include "dynacoe_color.hpp"
#include "dynacoe_shape2d.hpp"

#include "sandboxe_byte_array.hpp"

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
    Bindings::dynacoe_input(out);
    Bindings::dynacoe_assets(out);
    Bindings::dynacoe_color(out);
    Bindings::dynacoe_shape2d(out);
    
    Bindings::sandboxe_byte_array(out);

    return out;
}   

 
}
}

#endif