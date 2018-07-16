#ifndef dynacoe_shape2d_sandboxe_binding_included
#define dynacoe_shape2d_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/shape2d.h>
#include <sandboxe/bindings/dynacoe_component.hpp>

/*

    Dynacoe::Shape2D bindings 
    
    Notes:
        - as usual, native object inherets from ComponentAdaptor 
        - std::vector<Dynacoe::vector> inputs are now arrays of floats instead 
          



*/


namespace Sandboxe {
namespace Bindings {




SANDBOXE_NATIVE_DEF(__shape2d_form_rectangle) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto shape = (Sandboxe::Shape2DObject*)source;
    shape->FormRectangle(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__shape2d_form_image) {
    if (arguments.size() < 1) {
        SANDBOXE_ASSERT__ARG_COUNT(1);
        return;
    }
    
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, AssetIDObject);    
    auto shape = (Sandboxe::Shape2DObject*)source;
    Sandboxe::AssetIDObject * id = (Sandboxe::AssetIDObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];

    if (arguments.size() > 2) {
        shape->FormImage(id->id, arguments[1], arguments[2]);
    } else {
        shape->FormImage(id->id);
    }
}

SANDBOXE_NATIVE_DEF(__shape2d_form_image_frame) {
    if (arguments.size() < 1) {
        SANDBOXE_ASSERT__ARG_COUNT(1);
        return;
    }
    
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, AssetIDObject);    
    auto shape = (Sandboxe::Shape2DObject*)source;
    Sandboxe::AssetIDObject * id = (Sandboxe::AssetIDObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];


    if (arguments.size() > 3) {
        shape->FormImageFrame(id->id, arguments[1], arguments[2], arguments[3]);
    } else {
        shape->FormImageFrame(id->id, arguments[1]);
    }
}


SANDBOXE_NATIVE_DEF(__shape2d_form_circle) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto shape = (Sandboxe::Shape2DObject*)source;

    shape->FormCircle(arguments[0], arguments[1]);
}


SANDBOXE_NATIVE_DEF(__shape2d_form_triangles) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto pts = context.GetArrayArgument(0);
    if (!pts) return; 
    
    
    auto shape = (Sandboxe::Shape2DObject*)source;

    std::vector<Dynacoe::Vector> ptsReal;
    for(uint32_t i = 0; i < pts->size()/3; ++i) {
        ptsReal.push_back({
            (float)(*pts)[i*3+0],
            (float)(*pts)[i*3+1],
            (float)(*pts)[i*3+2]
        });
    }


    shape->FormTriangles(ptsReal);
}

SANDBOXE_NATIVE_DEF(__shape2d_form_lines) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto pts = context.GetArrayArgument(0);
    if (!pts) return; 
    
    
    auto shape = (Sandboxe::Shape2DObject*)source;

    std::vector<Dynacoe::Vector> ptsReal;
    for(uint32_t i = 0; i < pts->size()/2; ++i) {
        ptsReal.push_back({
            (float)(*pts)[i*3+0],
            (float)(*pts)[i*3+1],
            (float)(*pts)[i*3+2]
        });
    }


    shape->FormLines(ptsReal);
}
    

// managed properties

SANDBOXE_NATIVE_DEF(__shape2d_color_get) {
    auto shape = (Sandboxe::Shape2DObject*)source;
    context.SetReturnValue(shape->localColor);
}

SANDBOXE_NATIVE_DEF(__shape2d_color_set) {
    auto shape = (Sandboxe::Shape2DObject*)source;
    argument_to_color_object(shape->localColor->color, arguments[0]);
}




SANDBOXE_NATIVE_DEF(__shape2d_mode_get) {
    auto shape = (Sandboxe::Shape2DObject*)source;
    context.SetReturnValue((int)shape->mode);
}

SANDBOXE_NATIVE_DEF(__shape2d_mode_set) {
    auto shape = (Sandboxe::Shape2DObject*)source;
    int arg = arguments[0];
    if (arg < 0 || arg > (int)Dynacoe::Render2D::RenderMode::None) return;
    shape->mode = (Dynacoe::Render2D::RenderMode)arg;
}


SANDBOXE_NATIVE_DEF(__shape2d_absolute_get) {
    auto shape = (Sandboxe::Shape2DObject*)source;
    context.SetReturnValue(shape->absolute);
}

SANDBOXE_NATIVE_DEF(__shape2d_absolute_set) {
    auto shape = (Sandboxe::Shape2DObject*)source;
    shape->absolute = arguments[0];
}



SANDBOXE_NATIVE_DEF(__shape2d_node_get) {
    auto shape = (Sandboxe::Shape2DObject*)source;
    context.SetReturnValue(dynamic_cast<Sandboxe::NodeObject*>(&shape->node));
}

SANDBOXE_NATIVE_DEF(__shape2d_node_set) {
}




/// global functions
SANDBOXE_NATIVE_DEF(__shape2d_create) {
    context.SetReturnValue(new Sandboxe::Shape2DObject);
}


void dynacoe_shape2d(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::Shape2DT,
        {
            {"formRectangle", __shape2d_form_rectangle},
            {"formImage", __shape2d_form_image},
            {"formImageFrame", __shape2d_form_image_frame},
            {"formCircle", __shape2d_form_circle},
            {"formTriangles", __shape2d_form_triangles},
            {"formLines", __shape2d_form_lines},
            
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
            {"host", {__component_get_host, __component_set_host}},
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

            {"color", {__shape2d_color_get, __shape2d_color_set}},
            {"mode", {__shape2d_mode_get, __shape2d_mode_set}},
            {"absolute", {__shape2d_absolute_get, __shape2d_absolute_set}},
            {"node", {__shape2d_node_get, __shape2d_node_set}},


        }
        
    );
    
    fns.push_back({"__shape2d_create", __shape2d_create});    
}
    
    
    
}
}




#endif