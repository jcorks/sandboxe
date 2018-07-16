#ifndef H_sandboxe_bindings_camera
#define H_sandboxe_bindings_camera

#include <sandboxe/native/native.h>
#include <sandboxe/native/camera.h>
#include <sandboxe/native/component.h>
#include <sandboxe/native/node.h>

/*
    Dynacoe::Camera class bindings.
    
    Notes:
        Missing bindings:
            - 

 */





namespace Sandboxe {
namespace Bindings {
    
#define Index_EntityID 0






// methods 
SANDBOXE_NATIVE_DEF(__camera_refresh) {    
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    cam->Self()->Refresh();
}

SANDBOXE_NATIVE_DEF(__camera_set_target) {    
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    
    Dynacoe::Vector vec;
    argument_to_vector_object(vec, arguments[0]);
    cam->Self()->SetTarget(vec);
}

SANDBOXE_NATIVE_DEF(__camera_set_render_resolution) {    
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    cam->Self()->SetRenderResolution(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__camera_transform_screen_to_world) {    
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;

    auto out = new Sandboxe::VectorObject();
    Dynacoe::Vector vec;
    argument_to_vector_object(vec, arguments[0]);
    *out->vector = cam->Self()->TransformScreenToWorld(vec, arguments[1]);
    context.SetReturnValue(out);
}

SANDBOXE_NATIVE_DEF(__camera_transform_world_to_screen) {    
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;

    auto out = new Sandboxe::VectorObject();
    Dynacoe::Vector vec;
    argument_to_vector_object(vec, arguments[0]);
    *out->vector = cam->Self()->TransformWorldToScreen(vec);
    context.SetReturnValue(out);
}




// properties

SANDBOXE_NATIVE_DEF(__camera_set_type) {
    int type = arguments[0];
    if (type > (int)Dynacoe::Camera::Type::Orthographic2D) {
        return;
    }
    
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    cam->Self()->SetType((Dynacoe::Camera::Type)type);
}


SANDBOXE_NATIVE_DEF(__camera_get_width) {    
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    context.SetReturnValue(cam->Self()->Width());
}

SANDBOXE_NATIVE_DEF(__camera_get_height) {    
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    context.SetReturnValue(cam->Self()->Height());
}

SANDBOXE_NATIVE_DEF(__camera_get_auto_refresh) {    
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    context.SetReturnValue(cam->Self()->autoRefresh);
}

SANDBOXE_NATIVE_DEF(__camera_set_auto_refresh) {    
    auto cam = ((CameraEntityID*)source)->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    cam->Self()->autoRefresh = arguments[0];
}


SANDBOXE_NATIVE_DEF(__camera_create) {
    context.SetReturnValue(new Sandboxe::CameraEntityID());
}





void dynacoe_camera(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::Camera_EntityIDT,
        // methods
        {
            {"refresh", __camera_refresh},
            {"setTarget", __camera_set_target},
            {"setRenderResolution", __camera_set_render_resolution},
            {"transformScreenToWorld", __camera_transform_screen_to_world},
            {"transformWorldToScreen", __camera_transform_world_to_screen},
            
            //////// inherited from entity
            {"draw", __entity_draw},
            {"step", __entity_step},
            {"valid", __entity_valid},
            {"remove", __entity_remove},

            {"attach", __entity_attach},
            {"detach", __entity_detach},

            {"getNumChildren", __entity_get_num_children},
            {"contains", __entity_contains},
            {"getChildren", __entity_get_children},
            {"getAllSubEntities", __entity_get_all_sub_entities},
            {"findChildByName", __entity_find_child_by_name},
            {"createChild", __entity_create_child},

            {"stepDuration", __entity_step_duration},
            {"drawDuration", __entity_draw_duration},

            {"setPriority", __entity_set_priority},
            {"setPriorityLast", __entity_set_priority_last},
            {"setPriorityFirst", __entity_set_priority_first},
            {"getPriority", __entity_get_priority},
            
            {"getParent", __entity_get_parent},
            {"hasParent", __entity_has_parent},
            
            {"addComponent", __entity_add_component},
            {"queryComponent", __entity_query_component},
            {"getComponents", __entity_get_components},
            {"removeComponent", __entity_remove_component}
            ////////// inherited from entity
            
        },
        // properties
        {

        },
        
        // managed properties,
        {
            {"width", {__camera_get_width, SANDBOXE_NATIVE_EMPTY}},
            {"height", {__camera_get_height, SANDBOXE_NATIVE_EMPTY}},
            {"type", {SANDBOXE_NATIVE_EMPTY, __camera_set_type}},
            {"autoRefresh", {__camera_get_auto_refresh, __camera_set_auto_refresh}},

            //////// inherited from entity
            {"isStepping", {__entity_get_step, __entity_set_step}},
            {"isDrawing", {__entity_get_draw, __entity_set_draw}},
            {"id", {__entity_get_id, __entity_set_id}},
            {"name", {__entity_get_name, __entity_set_name}},
            {"node", {__entity_get_node, __entity_set_node}}

            ///////// inherited from entity
        }
    );
    fns.push_back({"__camera_create", __camera_create});

}
    
}
}





#endif