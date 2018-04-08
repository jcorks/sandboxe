#ifndef dynacoe_node_sandboxe_binding_included
#define dynacoe_node_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/node.h>
#include <sandboxe/bindings/dynacoe_component.hpp>


namespace Sandboxe {
namespace Bindings {
    

// managed properties




/// global functions
SANDBOXE_NATIVE_DEF(__node_create) {
    context.SetReturnValue(Sandboxe::NativeObject::New(Sandboxe::NativeType::NodeT));
}


void dynacoe_node(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        Sandboxe::NativeTypeToString(Sandboxe::NativeType::NodeT),
        {
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////
            {"step", __component_step},
            {"draw", __component_draw},

            {"installEvent", __component_install_event},
            {"uninstallEvent", __component_uninstall_event},
            
            {"emitEvent", __component_emit_event},
            {"canHandleEvent", __component_emit_event},
            {"installHook", __component_install_hook},
            {"uninstallHook", __component_uninstall_hook},
            {"installHandler", __component_install_handler},
            {"uninstallHandler", __component_uninstall_handler},
            {"getKnownEvents", __component_get_known_events}
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

        },

        // properties
        {
            
        },
        
        // native properties
        {
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

            {"tag", {__component_get_tag, __component_set_tag}},
            {"info", {__component_get_info, __component_set_info}},
            {"isStepping", {__component_get_step, __component_set_step}},
            {"isDrawing", {__component_get_draw, __component_set_draw}},
            {"host", {__component_get_host, __component_set_host}}
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

        }
    );
    
    fns.push_back({"__node_create", __node_create});    
}
    
    
    
}
}




#endif