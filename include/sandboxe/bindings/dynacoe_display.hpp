#ifndef dynacoe_display_sandboxe_binding_included
#define dynacoe_display_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/display.h>


/*

    Dynacoe::Display bindings
    
    Notes: 
        - Add/Remove * callbacks are now properties "onClose" and "onResize"
        - w/y/width/height are read-only properties
        - Interal - system-dependent bindings have been left out.
        - View manager type symbols have been imported as static methods
*/

namespace Sandboxe {
namespace Bindings {
    

// managed properties



SANDBOXE_NATIVE_DEF(__display_resize) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    display->Resize(arguments[0], arguments[1]);
}


SANDBOXE_NATIVE_DEF(__display_set_position) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    display->SetPosition(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__display_fullscreen) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    display->Fullscreen(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__display_hide) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    display->Hide(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__display_has_input_focus) {
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    context.SetReturnValue(display->HasInputFocus());
}

SANDBOXE_NATIVE_DEF(__display_lock_client_resize) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    display->LockClientResize(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__display_lock_client_position) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    display->LockClientPosition(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__display_set_view_policy) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    int viewPolicy = arguments[0];
    if (viewPolicy < 0 || viewPolicy > (int)Dynacoe::Display::ViewPolicy::MatchSize) return;
    display->SetViewPolicy((Dynacoe::Display::ViewPolicy)viewPolicy);
}


SANDBOXE_NATIVE_DEF(__display_set_name) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    display->SetName(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__display_is_capable) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    int cap = arguments[0];
    if (cap < 0 || cap > (int)Dynacoe::Display::Capability::CanLockSize) return;
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    context.SetReturnValue(display->IsCapable((Dynacoe::Display::Capability)cap));
}



SANDBOXE_NATIVE_DEF(__display_get_x) {
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    context.SetReturnValue(display->X());
}

SANDBOXE_NATIVE_DEF(__display_get_y) {
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    context.SetReturnValue(display->Y());
}

SANDBOXE_NATIVE_DEF(__display_get_width) {
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    context.SetReturnValue(display->Width());
}

SANDBOXE_NATIVE_DEF(__display_get_height) {
    auto dispSource = (Sandboxe::DisplayObject*)source;
    auto display = Dynacoe::ViewManager::Get(dispSource->id);
    if (!display) return;
    context.SetReturnValue(display->Height());
}



SANDBOXE_NATIVE_DEF(__view_manager_create_display) {
    std::string name = "";
    int w = 640;
    int h = 480;
    if (arguments.size() > 0) {
        name = (std::string)arguments[0];
    }
    if (arguments.size() > 1) {
        w = arguments[1];
    }
    if (arguments.size() > 2) {
        h = arguments[2];
    }

    auto out = new Sandboxe::DisplayObject(
        Dynacoe::ViewManager::New(name, w, h)
    );
    context.SetReturnValue(out);
}


SANDBOXE_NATIVE_DEF(__view_manager_destroy_display) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, DisplayObject);
    
    auto disp = (Sandboxe::DisplayObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    
    Dynacoe::ViewManager::Destroy(disp->id);
}

SANDBOXE_NATIVE_DEF(__view_manager_set_main) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, DisplayObject);
    
    auto disp = (Sandboxe::DisplayObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    
    Dynacoe::ViewManager::SetMain(disp->id);
}


void dynacoe_display(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::DisplayT,
        // methods
        {
            {"resize", __display_resize},
            {"setPosition", __display_set_position},
            {"fullscreen", __display_fullscreen},
            {"hide", __display_hide},
            {"hasInputFocus", __display_has_input_focus},
            {"lockClientResize", __display_lock_client_resize},
            {"lockClientPosition", __display_lock_client_position},
            {"setViewPolicy", __display_set_view_policy},
            {"setName", __display_set_name},
            {"isCapable", __display_is_capable}
        },
        // properties
        {
            {"onResize", Sandboxe::Script::Runtime::Primitive()},
            {"onClose", Sandboxe::Script::Runtime::Primitive()}
        },
        
        // managed properties,
        {
            {"width", {__display_get_width, SANDBOXE_NATIVE_EMPTY}},
            {"height", {__display_get_height, SANDBOXE_NATIVE_EMPTY}},
            {"x", {__display_get_x, SANDBOXE_NATIVE_EMPTY}},
            {"y", {__display_get_y, SANDBOXE_NATIVE_EMPTY}}

        } 
    );
    fns.push_back({"__display_create", __view_manager_create_display});
    fns.push_back({"__display_destroy", __view_manager_destroy_display});
    fns.push_back({"__display_set_main", __view_manager_set_main});
 
}
    
    
    
}
}




#endif