#ifndef dynacoe_mutator_sandboxe_binding_included
#define dynacoe_mutator_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/mutator.h>
#include <sandboxe/bindings/dynacoe_component.hpp>

/*

    Dynacoe::Mutator bindings 
    
    Notes:
        - symbol name Function is now "mutation" in JS enumeration  
        - NewRandomMutation was not added
        - SetMutationDestination was not added 
        - NewMutation is bound as add()
        - Expired() is now a boolean read-only property named "expired"
        - GetENd() is now a read-only property named "duration"
        - GetCurrentTime() is now a read-only property named "currentTime"
        - Loop() is now a boolean property
        - StepTowards is just "step()"
        - StepTowards vector variant has no binding
*/


namespace Sandboxe {
namespace Bindings {








    

// managed properties

SANDBOXE_NATIVE_DEF(__mutator_clear) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto mut = (Sandboxe::MutatorObject*)source;    
    mut->Clear(arguments[0]);
}


SANDBOXE_NATIVE_DEF(__mutator_add) {
    SANDBOXE_ASSERT__ARG_COUNT(3);
    auto mut = (Sandboxe::MutatorObject*)source;    
    int function = arguments[2];
    if (function < 0 || function > (int)Dynacoe::Mutator::Function::RandomDistribution) return;
    mut->NewMutation(arguments[0], arguments[1], (Dynacoe::Mutator::Function)function);
}



SANDBOXE_NATIVE_DEF(__mutator_start) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    mut->Start();
}

SANDBOXE_NATIVE_DEF(__mutator_stop) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    mut->Stop();
}

SANDBOXE_NATIVE_DEF(__mutator_get_at) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto mut = (Sandboxe::MutatorObject*)source;    
    context.SetReturnValue(mut->GetAt(arguments[0]));
}

SANDBOXE_NATIVE_DEF(__mutator_get_value) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    context.SetReturnValue(mut->Value());
}




//// manged propertiess

SANDBOXE_NATIVE_DEF(__mutator_loop_set) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    mut->localLoop = arguments[0];
    mut->Loop(mut->localLoop);
}

SANDBOXE_NATIVE_DEF(__mutator_loop_get) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    context.SetReturnValue(mut->localLoop);
}


SANDBOXE_NATIVE_DEF(__mutator_get_expired) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    context.SetReturnValue(mut->Expired());
}

SANDBOXE_NATIVE_DEF(__mutator_get_current_time) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    context.SetReturnValue(mut->GetCurrentTime());
}

SANDBOXE_NATIVE_DEF(__mutator_get_duration) {
    auto mut = (Sandboxe::MutatorObject*)source;    
    context.SetReturnValue(mut->GetEnd());
}




/// global functions
SANDBOXE_NATIVE_DEF(__mutator_create) {
    context.SetReturnValue(new Sandboxe::MutatorObject);
}

SANDBOXE_NATIVE_DEF(__mutator_step) {
    switch(arguments.size()) {
      case 0:
      case 1: 
        SANDBOXE_ASSERT__ARG_COUNT(2);
      case 2:
        context.SetReturnValue(Dynacoe::Mutator::StepTowards(arguments[0], arguments[1])); return;
      case 3:
        context.SetReturnValue(Dynacoe::Mutator::StepTowards(arguments[0], arguments[1], arguments[2])); return;
      default: {
        int fun = arguments[2];
        context.SetReturnValue(Dynacoe::Mutator::StepTowards(arguments[0], arguments[1], arguments[2], (Dynacoe::Mutator::Function)fun)); return;
      }
    }
}






void dynacoe_mutator(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::MutatorT,
        {
            {"clear", __mutator_clear},
            {"add", __mutator_add},
            {"start", __mutator_start},
            {"stop", __mutator_stop},
            {"getAt", __mutator_get_at},
            {"value", __mutator_get_value},

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
            {"expired", {__mutator_get_expired, SANDBOXE_NATIVE_EMPTY}},
            {"currentTime", {__mutator_get_current_time, SANDBOXE_NATIVE_EMPTY}},
            {"duration", {__mutator_get_duration, SANDBOXE_NATIVE_EMPTY}},
            {"loop", {__mutator_loop_get, __mutator_loop_set}}



        }
        
    );
    
    fns.push_back({"__mutator_create", __mutator_create});  
    fns.push_back({"__mutator_step", __mutator_step});

  
}
    
    
    
}
}




#endif
