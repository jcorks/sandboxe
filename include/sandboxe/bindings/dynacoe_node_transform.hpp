#ifndef dynacoe_node_transform_sandboxe_binding_included
#define dynacoe_node_transform_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/node.h>


namespace Sandboxe {
namespace Bindings {
    

// managed properties



SANDBOXE_NATIVE_DEF(__node_transform_get_reverse) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    context.SetReturnValue(t->t->reverse);
}

SANDBOXE_NATIVE_DEF(__node_transform_set_reverse) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    t->t->reverse = arguments[0];
}


SANDBOXE_NATIVE_DEF(__node_transform_get_position) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    context.SetReturnValue(t->position);
}

SANDBOXE_NATIVE_DEF(__node_transform_set_position) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    t->position->vector = Dynacoe::Vector(std::string(arguments[0]));
    t->position->delta.Changed(t->position);
}



SANDBOXE_NATIVE_DEF(__node_transform_get_rotation) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    context.SetReturnValue(t->rotation);
}

SANDBOXE_NATIVE_DEF(__node_transform_set_rotation) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    t->rotation->vector = Dynacoe::Vector(std::string(arguments[0]));
    t->rotation->delta.Changed(t->rotation);

}



SANDBOXE_NATIVE_DEF(__node_transform_get_scale) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    context.SetReturnValue(t->scale);
}

SANDBOXE_NATIVE_DEF(__node_transform_set_scale) {
    auto t = (Sandboxe::Node_TransformObject*)source;
    t->scale->vector = Dynacoe::Vector(std::string(arguments[0]));
    t->scale->delta.Changed(t->scale);

}





void dynacoe_node_transform(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::Node_TransformT,
        // methods
        {

        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"reverse", {__node_transform_get_reverse, __node_transform_set_reverse}},
            {"position", {__node_transform_get_position, __node_transform_set_position}},
            {"scale", {__node_transform_get_scale, __node_transform_set_scale}},
            {"rotation", {__node_transform_get_rotation, __node_transform_set_rotation}},

        } 
    );
    
}
    
    
    
}
}




#endif
