#ifndef dynacoe_render_light_sandboxe_binding_included
#define dynacoe_render_light_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/renderLight.h>
#include <sandboxe/bindings/dynacoe_component.hpp>


/*
    Dynacoe::RenderLight Notes: 
        - Enable() is now a read/write property "enabled"
        - FormLight() is now a read/write property "type"
        - All the state properties are now locally available through their respective names 
          as it part of the base RenderLight object
        - Clear() is now "reset()" (name is a lot more clear)

*/


namespace Sandboxe {
namespace Bindings {
    







SANDBOXE_NATIVE_DEF(__render_light_reset) {
    auto light = (Sandboxe::RenderLightObject*)source;
    light->Clear();
}

SANDBOXE_NATIVE_DEF(__render_light_get_type) {
    auto light = (Sandboxe::RenderLightObject*)source;
    context.SetReturnValue((int)light->localType);
}

SANDBOXE_NATIVE_DEF(__render_light_set_type) {
    int type = arguments[0];
    if (type > (int)Dynacoe::RenderLight::Light::Directional) return;
    auto light = (Sandboxe::RenderLightObject*)source;
    light->FormLight((Dynacoe::RenderLight::Light) type);
    light->localType = (Dynacoe::RenderLight::Light)type;
}

SANDBOXE_NATIVE_DEF(__render_light_get_color) {
    auto light = (Sandboxe::RenderLightObject*)source;
    context.SetReturnValue(light->localColor);
}

SANDBOXE_NATIVE_DEF(__render_light_set_color) {
    auto light = (Sandboxe::RenderLightObject*)source;
    argument_to_color_object(light->localColor->color, arguments[0]);
}

SANDBOXE_NATIVE_DEF(__render_light_get_enabled) {
    auto light = (Sandboxe::RenderLightObject*)source;
    context.SetReturnValue(light->localEnabled);
}

SANDBOXE_NATIVE_DEF(__render_light_set_enabled) {
    auto light = (Sandboxe::RenderLightObject*)source;
    bool enabled = arguments[0];
    light->localEnabled = (enabled);
    light->Enable(enabled);
}

SANDBOXE_NATIVE_DEF(__render_light_get_position) {
    auto light = (Sandboxe::RenderLightObject*)source;
    context.SetReturnValue(light->localPosition);
}

SANDBOXE_NATIVE_DEF(__render_light_set_position) {
    auto light = (Sandboxe::RenderLightObject*)source;
    argument_to_vector_object(*light->localPosition->vector, arguments[0]);
}



SANDBOXE_NATIVE_DEF(__render_light_get_intensity) {
    auto light = (Sandboxe::RenderLightObject*)source;
    context.SetReturnValue(light->state.intensity);
}

SANDBOXE_NATIVE_DEF(__render_light_set_intensity) {
    auto light = (Sandboxe::RenderLightObject*)source;
    light->state.intensity = (arguments[0]);
}





void dynacoe_render_light(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::RenderLightT,
        {
            {"reset", __render_light_reset},
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
            {"type", {__render_light_get_type, __render_light_set_type}},
            {"enabled", {__render_light_get_enabled, __render_light_set_enabled}},
            {"position", {__render_light_get_position, __render_light_set_position}},
            {"intensity", {__render_light_get_intensity, __render_light_set_intensity}},
            {"color", {__render_light_get_color, __render_light_set_color}},

        }
    );
    
}
    
    
    
}
}




#endif
