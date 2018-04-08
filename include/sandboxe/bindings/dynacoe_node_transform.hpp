#ifndef dynacoe_node_transform_sandboxe_binding_included
#define dynacoe_node_transform_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/node.h>


namespace Sandboxe {
namespace Bindings {
    

// managed properties



SANDBOXE_NATIVE_DEF(__node_transform_get_reverse) {
    Sandboxe::Node_Transform * t = Sandboxe::NativeObject::Get<Sandboxe::Node_Transform>(source);
    context.SetReturnValue(t->reverse);
}

SANDBOXE_NATIVE_DEF(__node_transform_set_reverse) {
    Sandboxe::Node_Transform * t = Sandboxe::NativeObject::Get<Sandboxe::Node_Transform>(source);
    t->reverse = arguments[0];
}







/// global functions
SANDBOXE_NATIVE_DEF(__node_transform_create) {
    context.SetReturnValue(Sandboxe::NativeObject::New(Sandboxe::NativeType::Node_TransformT));
}


void dynacoe_node_transform(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        Sandboxe::NativeTypeToString(Sandboxe::NativeType::Node_TransformT),
        // methods
        {

        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"reverse", {__node_transform_get_reverse, __node_transform_set_reverse}},

        } 
    );
    
    fns.push_back({"__node_transform_create", __node_transform_create});    
}
    
    
    
}
}




#endif