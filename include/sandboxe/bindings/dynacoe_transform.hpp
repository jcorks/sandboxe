#ifndef dynacoe_node_sandboxe_binding_included
#define dynacoe_node_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/transform.h>
#include <sandboxe/bindings/dynacoe_component.hpp>


namespace Sandboxe {
namespace Bindings {
    

// managed properties




/// global functions
SANDBOXE_NATIVE_DEF(__transform_create) {
    context.SetReturnValue(new Sandboxe::TransformObject);
}




SANDBOXE_NATIVE_DEF(__transform_get_reverse) {
    auto node = (Sandboxe::TransformObject*)source;    
    context.SetReturnValue(node->isReverse);
}

SANDBOXE_NATIVE_DEF(__transform_set_reverse) {
    auto node = (Sandboxe::TransformObject*)source;
    node->isReverse = (arguments[0]);
    node->transformReal.SetReverseTranslation(node->isReverse);
}


SANDBOXE_NATIVE_DEF(__transform_get_position) {
    auto node = (Sandboxe::TransformObject*)source;
    context.SetReturnValue(node->localPosition);
}

SANDBOXE_NATIVE_DEF(__transform_set_position) {
    auto node = (Sandboxe::TransformObject*)source;
    argument_to_vector_object(node->transformReal.Position(), arguments[0]);    
    *node->localPosition->vector = node->transformReal.GetPosition();
}



SANDBOXE_NATIVE_DEF(__transform_get_rotation) {
    auto node = (Sandboxe::TransformObject*)source;
    context.SetReturnValue(node->localRotation);
}

SANDBOXE_NATIVE_DEF(__transform_set_rotation) {
    auto node = (Sandboxe::TransformObject*)source;
    argument_to_vector_object(node->transformReal.Rotation(), arguments[0]);    
    *node->localRotation->vector = node->transformReal.GetRotation();
}



SANDBOXE_NATIVE_DEF(__transform_get_scale) {
    auto node = (Sandboxe::TransformObject*)source;
    context.SetReturnValue(node->localScale);
}

SANDBOXE_NATIVE_DEF(__transform_set_scale) {
    auto node = (Sandboxe::TransformObject*)source;
    argument_to_vector_object(node->transformReal.Scale(), arguments[0]);    
    *node->localScale->vector = node->transformReal.GetScale();
}



void dynacoe_node(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::TransformT,
        {
        

        },

        // properties
        {
            
        },
        
        // native properties
        {
            
            {"reverse", {__transform_get_reverse, __transform_set_reverse}},
            {"position", {__transform_get_position, __transform_set_position}},
            {"scale", {__transform_get_scale, __transform_set_scale}},
            {"rotation", {__transform_get_rotation, __transform_set_rotation}},

        }
    );
    
    fns.push_back({"__transform_create", __transform_create});    
}
    
    
    
}
}




#endif