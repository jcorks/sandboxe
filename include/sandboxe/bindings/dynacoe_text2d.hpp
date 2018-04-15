#ifndef dynacoe_text2d_sandboxe_binding_included
#define dynacoe_text2d_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/text2d.h>
#include <sandboxe/bindings/dynacoe_component.hpp>

/*

    Dynacoe::Text2D bindings 
    
    Notes:
          



*/


namespace Sandboxe {
namespace Bindings {




SANDBOXE_NATIVE_DEF(__text2d_get_char_position) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto shape = (Sandboxe::Text2DObject*)source;
    auto out = new Sandboxe::VectorObject();
    out->vector = shape->GetCharPosition(arguments[0]);
    context.SetReturnValue(out);
}

SANDBOXE_NATIVE_DEF(__text2d_get_dimensions) {
    auto shape = (Sandboxe::Text2DObject*)source;
    auto out = new Sandboxe::VectorObject();
    out->vector = shape->GetDimensions();
    context.SetReturnValue(out);
}





    

// managed properties

SANDBOXE_NATIVE_DEF(__text2d_color_get) {
}

SANDBOXE_NATIVE_DEF(__text2d_color_set) {
    auto shape = (Sandboxe::Text2DObject*)source;
    shape->SetTextColor(Dynacoe::Color((std::string)arguments[0]));
}


SANDBOXE_NATIVE_DEF(__text2d_font_get) {
    auto shape = (Sandboxe::Text2DObject*)source;
    context.SetReturnValue(shape->localFont);
}

SANDBOXE_NATIVE_DEF(__text2d_font_set) {
}

SANDBOXE_NATIVE_DEF(__text2d_text_get) {
    auto shape = (Sandboxe::Text2DObject*)source;
    context.SetReturnValue(shape->text);
}

SANDBOXE_NATIVE_DEF(__text2d_text_set) {
    auto shape = (Sandboxe::Text2DObject*)source;
    shape->text = (std::string)arguments[0];
}

SANDBOXE_NATIVE_DEF(__text2d_font_size_get) {
    auto shape = (Sandboxe::Text2DObject*)source;
    context.SetReturnValue(shape->fontSize);
}

SANDBOXE_NATIVE_DEF(__text2d_font_size_set) {
    auto shape = (Sandboxe::Text2DObject*)source;
    shape->fontSize = arguments[0];
    shape->SetFontSize(shape->fontSize);
}

SANDBOXE_NATIVE_DEF(__text2D_spacing_mode_get) {
    auto shape = (Sandboxe::Text2DObject*)source;
    context.SetReturnValue(shape->spacingMode);
}

SANDBOXE_NATIVE_DEF(__text2D_spacing_mode_set) {
    auto shape = (Sandboxe::Text2DObject*)source;
    int g = arguments[0];
    if (g < 0 || g > (int)Dynacoe::Text2D::SpacingMode::Bitmap) return;
    shape->spacingMode = g;
    shape->SetSpacingMode((Dynacoe::Text2D::SpacingMode)g);
}


SANDBOXE_NATIVE_DEF(__text2d_mode_get) {
    auto shape = (Sandboxe::Text2DObject*)source;
    context.SetReturnValue((int)shape->mode);
}

SANDBOXE_NATIVE_DEF(__text2d_mode_set) {
    auto shape = (Sandboxe::Text2DObject*)source;
    int arg = arguments[0];
    if (arg < 0 || arg > (int)Dynacoe::Render2D::RenderMode::None) return;
    shape->mode = (Dynacoe::Render2D::RenderMode)arg;
}






SANDBOXE_NATIVE_DEF(__text2d_absolute_get) {
    auto shape = (Sandboxe::Text2DObject*)source;
    context.SetReturnValue(shape->absolute);
}

SANDBOXE_NATIVE_DEF(__text2d_absolute_set) {
    auto shape = (Sandboxe::Text2DObject*)source;
    shape->absolute = arguments[0];
}



SANDBOXE_NATIVE_DEF(__text2d_node_get) {
    auto shape = (Sandboxe::Text2DObject*)source;
    context.SetReturnValue(shape->localNode);
}

SANDBOXE_NATIVE_DEF(__text2d_node_set) {
}




/// global functions
SANDBOXE_NATIVE_DEF(__text2d_create) {
    context.SetReturnValue(new Sandboxe::Text2DObject);
}


void dynacoe_text2d(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::Text2DT,
        {
            {"getCharPosition", __text2d_get_char_position},
            {"getDimensions", __text2d_get_char_position},

            
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

            {"color", {__text2d_color_get, __text2d_color_set}},
            {"text", {__text2d_text_get, __text2d_text_set}},
            {"fontSize", {__text2d_font_size_get, __text2d_font_size_set}},
            {"spacingMode", {__text2D_spacing_mode_get, __text2d_spacing_mode_set}},
            {"font", {__text2d_font_get, __text2d_font_set}},
            {"mode", {__shape2d_mode_get, __shape2d_mode_set}},
            {"absolute", {__shape2d_absolute_get, __text2d_absolute_set}},
            {"node", {__shape2d_node_get, __text2d_node_set}}

        }
        
    );
    
    fns.push_back({"__text2d_create", __text2d_create});    
}
    
    
    
}
}




#endif