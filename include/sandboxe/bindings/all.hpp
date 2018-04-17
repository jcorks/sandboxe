#ifndef h_sandboxe_bindings_all_included
#define h_sandboxe_bindings_all_included

// all includes
#include "dynacoe_vector.hpp"
#include "dynacoe_component.hpp"
#include "dynacoe_console.hpp"
#include "dynacoe_entity.hpp"
#include "dynacoe_component.hpp"
#include "dynacoe_node_transform.hpp"
#include "dynacoe_node.hpp"
#include "dynacoe_engine.hpp"
#include "dynacoe_input.hpp"
#include "dynacoe_assets.hpp"
#include "dynacoe_color.hpp"
#include "dynacoe_clock.hpp"
#include "dynacoe_shape2d.hpp"
#include "dynacoe_text2d.hpp"
#include "dynacoe_data_table.hpp"
#include "dynacoe_gui.hpp"
#include "dynacoe_mutator.hpp"
#include "dynacoe_object2d.hpp"

#include "sandboxe_byte_array.hpp"

namespace Sandboxe {
namespace Script {

std::vector<std::pair<std::string, Runtime::Function>> GatherNativeBindings() {
    std::vector<std::pair<std::string, Runtime::Function>> out;
    Bindings::dynacoe_vector(out);
    Bindings::dynacoe_component(out);
    Bindings::dynacoe_console(out);
    Bindings::dynacoe_entity(out);
    Bindings::dynacoe_node_transform(out);
    Bindings::dynacoe_node(out);
    Bindings::dynacoe_engine(out);
    Bindings::dynacoe_input(out);
    Bindings::dynacoe_assets(out);
    Bindings::dynacoe_color(out);
    Bindings::dynacoe_clock(out);
    Bindings::dynacoe_shape2d(out);
    Bindings::dynacoe_text2d(out);
    Bindings::dynacoe_data_table(out);
    Bindings::dynacoe_gui(out);
    Bindings::dynacoe_mutator(out);
    Bindings::dynacoe_object2d(out);

    Bindings::sandboxe_byte_array(out);

    return out;
}   

 
}
}

#endif
