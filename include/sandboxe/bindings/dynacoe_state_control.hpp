#ifndef dynacoe_state_control_sandboxe_binding_included
#define dynacoe_state_control_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/stateControl.h>
#include <sandboxe/bindings/dynacoe_component.hpp>


/* 
    Bindings for Dynacoe::StateControl
    
    Notes:
        -State Loops are just arrays of upto 3 functions. Order: step, draw, init
        -ConnectState() and RemoveLoop() are not implemented
*/

namespace Sandboxe {
namespace Bindings {
    
// member functions 
SANDBOXE_NATIVE_DEF(__state_control_create_state) {
    SANDBOXE_ASSERT__ARG_COUNT(4);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceNonNativeT);    
    SANDBOXE_ASSERT__ARG_TYPE(2, ObjectReferenceNonNativeT);    
    SANDBOXE_ASSERT__ARG_TYPE(3, ObjectReferenceNonNativeT);    

    auto state = (Sandboxe::StateControlObject*)source;
    state->CreateStateNonNative(arguments[0], arguments[1], arguments[2], arguments[3]);    
}

SANDBOXE_NATIVE_DEF(__state_control_remove_state) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto state = (Sandboxe::StateControlObject*)source;    
    state->RemoveState(arguments[0]);    
}

SANDBOXE_NATIVE_DEF(__state_control_execute) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto state = (Sandboxe::StateControlObject*)source;    
    state->Execute(arguments[0]);    
}


SANDBOXE_NATIVE_DEF(__state_control_halt) {
    auto state = (Sandboxe::StateControlObject*)source;    
    state->Halt();
}





// managed properties


SANDBOXE_NATIVE_DEF(__state_control_get_state) {
    auto state = (Sandboxe::StateControlObject*)source;
    context.SetReturnValue(state->GetCurrentState());
}

SANDBOXE_NATIVE_DEF(__state_control_get_halted) {
    auto state = (Sandboxe::StateControlObject*)source;
    context.SetReturnValue(state->IsHalted());
}



void dynacoe_state_control(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::StateControlT,
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
            
            {"createState", __state_control_create_state},
            {"removeState", __state_control_remove_state},
            {"execute", __state_control_execute},
            {"halt", __state_control_halt},

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
            {"onStep", {__component_get_on_step, __component_set_on_step}},
            {"onDraw", {__component_get_on_draw, __component_set_on_draw}}
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////
            ,
            {"state", {__state_control_get_state, SANDBOXE_NATIVE_EMPTY}},
            {"halted", {__state_control_get_halted, SANDBOXE_NATIVE_EMPTY}}


        }
    );
 
}
    
    
    
}
}




#endif
