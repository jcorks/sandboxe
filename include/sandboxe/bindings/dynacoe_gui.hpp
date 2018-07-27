#ifndef dynacoe_gui_sandboxe_binding_included
#define dynacoe_gui_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/gui.h>
#include <sandboxe/bindings/dynacoe_component.hpp>

/*

    Dynacoe::GUI bindings 
    
    Notes:
        -Region width / height set and get through the widht and height properties 
        -Tooltip text is set/get via the tooltipText property
        -Is* functions are now boolean read-only properties
        - convenience Is* functions are not bound


*/


namespace Sandboxe {
namespace Bindings {








    

// managed properties

SANDBOXE_NATIVE_DEF(__gui_grab_input) {
    auto gui = (Sandboxe::GUIObject*)source;    
    gui->GrabInput();
}


SANDBOXE_NATIVE_DEF(__gui_set_focus) {
    auto gui = (Sandboxe::GUIObject*)source;    
    gui->SetFocus();
}




//// manged propertiess

SANDBOXE_NATIVE_DEF(__gui_focused_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->IsFocused());
}

SANDBOXE_NATIVE_DEF(__gui_hovered_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->IsHovered());
}

SANDBOXE_NATIVE_DEF(__gui_clicked_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->IsClicked());
}

SANDBOXE_NATIVE_DEF(__gui_being_dragged_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->IsBeingDragged());
}

SANDBOXE_NATIVE_DEF(__gui_width_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->width);
}

SANDBOXE_NATIVE_DEF(__gui_height_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->height);
}

SANDBOXE_NATIVE_DEF(__gui_width_set) {
    auto gui = (Sandboxe::GUIObject*)source;    
    int nw = arguments[0];
    if (nw != gui->width) {
        gui->width = nw;
        gui->DefineRegion(
            gui->width,
            gui->height
        );
    }
}

SANDBOXE_NATIVE_DEF(__gui_height_set) {
    auto gui = (Sandboxe::GUIObject*)source;    
    int nh = arguments[0];
    if (nh != gui->height) {
        gui->height = nh;
        gui->DefineRegion(
            gui->width,
            gui->height
        );
    }
}


SANDBOXE_NATIVE_DEF(__gui_text_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->GetTooltipText());
}

SANDBOXE_NATIVE_DEF(__gui_text_set) {
    auto gui = (Sandboxe::GUIObject*)source;    
    gui->SetTooltipText(arguments[0]);
}


SANDBOXE_NATIVE_DEF(__gui_node_get) {
    auto gui = (Sandboxe::GUIObject*)source;    
    context.SetReturnValue(gui->transform);
}





/// global functions
SANDBOXE_NATIVE_DEF(__gui_create) {
    context.SetReturnValue(new Sandboxe::GUIObject);
}

SANDBOXE_NATIVE_DEF(__gui_ungrab_input) {
    Dynacoe::GUI::UngrabInput();
}

SANDBOXE_NATIVE_DEF(__gui_unfocus) {
    Dynacoe::GUI::Unfocus();
}


void dynacoe_gui(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::GUIT,
        {
            {"grabInput", __gui_grab_input},
            {"setFocus", __gui_set_focus},
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

            {"tooltipText", {__gui_text_get, __gui_text_set}},
            {"width", {__gui_width_get, __gui_width_set}},
            {"height", {__gui_height_get, __gui_height_set}},
            {"focused", {__gui_focused_get, SANDBOXE_NATIVE_EMPTY}},
            {"hovered", {__gui_hovered_get, SANDBOXE_NATIVE_EMPTY}},
            {"clicked", {__gui_clicked_get, SANDBOXE_NATIVE_EMPTY}},
            {"beingDragged", {__gui_being_dragged_get, SANDBOXE_NATIVE_EMPTY}},
            {"node", {__gui_node_get, SANDBOXE_NATIVE_EMPTY}}

        }
        
    );
    
    fns.push_back({"__gui_create", __gui_create});  
    fns.push_back({"__gui_ungrab_input", __gui_ungrab_input});
    fns.push_back({"__gui_unfocus", __gui_unfocus});

  
}
    
    
    
}
}




#endif