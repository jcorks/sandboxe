#ifndef dynacoe_clock_sandboxe_binding_included
#define dynacoe_clock_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/clock.h>
#include <sandboxe/bindings/dynacoe_component.hpp>


/* 
    Bindings for Dynacoe::Clock
    
    Notes:
        - most functions are now read-only or RW proprties
          (same name except get/set omitted)

*/

namespace Sandboxe {
namespace Bindings {
    
// member functions 
SANDBOXE_NATIVE_DEF(__clock_set) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    if (arguments.size() >= 1)
        clock->Set(arguments[0]);
    else 
        clock->Set();
}


SANDBOXE_NATIVE_DEF(__clock_reset) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    clock->Reset();
}

SANDBOXE_NATIVE_DEF(__clock_pause) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    clock->Pause();
}

SANDBOXE_NATIVE_DEF(__clock_resume) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    clock->Resume();
}


/// global functions
SANDBOXE_NATIVE_DEF(__clock_create) {
    context.SetReturnValue(Sandboxe::NativeObject::New(Sandboxe::NativeType::ClockT));
}



// managed properties

SANDBOXE_NATIVE_DEF(__clock_get_paused) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    context.SetReturnValue(clock->IsPaused());
}

SANDBOXE_NATIVE_DEF(__clock_get_expired) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    context.SetReturnValue(clock->IsExpired());
}

SANDBOXE_NATIVE_DEF(__clock_get_time_left) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    context.SetReturnValue(clock->GetTimeLeft());
}

SANDBOXE_NATIVE_DEF(__clock_get_time_since) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    context.SetReturnValue(clock->GetTimeSince());
}


SANDBOXE_NATIVE_DEF(__clock_get_duration) {
    auto t = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(source);
    auto clock = (Sandboxe::Clock *) t->Native_GetParentPtr();
    context.SetReturnValue(clock->GetDuration());
}


void dynacoe_clock(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        Sandboxe::NativeTypeToString(Sandboxe::NativeType::ClockT),
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
            ,
            
            {"set", __clock_set},
            {"reset", __clock_reset},
            {"pause", __clock_pause},
            {"resume", __clock_resume}
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
            {"timeSince", {__clock_get_time_since, SANDBOXE_NATIVE_EMPTY}},
            {"timeLeft", {__clock_get_time_left, SANDBOXE_NATIVE_EMPTY}},
            {"duration", {__clock_get_duration, SANDBOXE_NATIVE_EMPTY}},
            {"expired", {__clock_get_expired, SANDBOXE_NATIVE_EMPTY}},
            {"paused", {__clock_get_paused, SANDBOXE_NATIVE_EMPTY}},

        }
    );
    
    fns.push_back({"__clock_create", __clock_create});   
}
    
    
    
}
}




#endif