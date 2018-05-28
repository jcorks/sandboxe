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
    context.SetReturnValue(new Sandboxe::NodeObject);
}

SANDBOXE_NATIVE_DEF(__node_set_local){}
SANDBOXE_NATIVE_DEF(__node_set_global){}


SANDBOXE_NATIVE_DEF(__node_get_local) {
    auto node = (Sandboxe::NodeObject*)source;
    context.SetReturnValue(node->localTransform);
}

SANDBOXE_NATIVE_DEF(__node_get_global) {
    auto node = (Sandboxe::NodeObject*)source;
    context.SetReturnValue(node->globalTransform);
}





SANDBOXE_NATIVE_DEF(__node_get_reverse) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    context.SetReturnValue(t->t->reverse);
}

SANDBOXE_NATIVE_DEF(__node_set_reverse) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    t->t->reverse = arguments[0];
}


SANDBOXE_NATIVE_DEF(__node_get_position) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    context.SetReturnValue(t->position);
}

SANDBOXE_NATIVE_DEF(__node_set_position) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    argument_to_vector_object(t->position->vector, arguments[0]);
    t->position->delta.Changed(t->position);
}



SANDBOXE_NATIVE_DEF(__node_get_rotation) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    context.SetReturnValue(t->rotation);
}

SANDBOXE_NATIVE_DEF(__node_set_rotation) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    argument_to_vector_object(t->rotation->vector, arguments[0]);
    t->rotation->delta.Changed(t->rotation);

}



SANDBOXE_NATIVE_DEF(__node_get_scale) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    context.SetReturnValue(t->scale);
}

SANDBOXE_NATIVE_DEF(__node_set_scale) {
    auto node = (Sandboxe::NodeObject*)source;
    auto t = node->localTransform;
    argument_to_vector_object(t->scale->vector, arguments[0]);
    t->scale->delta.Changed(t->scale);
}



void dynacoe_node(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::NodeT,
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
            ,
            {"local", {__node_get_local, __node_set_local}},
            {"global", {__node_get_global, __node_set_global}},
            
            {"reverse", {__node_get_reverse, __node_set_reverse}},
            {"position", {__node_get_position, __node_set_position}},
            {"scale", {__node_get_scale, __node_set_scale}},
            {"rotation", {__node_get_rotation, __node_set_rotation}},

        }
    );
    
    fns.push_back({"__node_create", __node_create});    
}
    
    
    
}
}




#endif