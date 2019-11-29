#ifndef dynacoe_scheduler_sandboxe_binding_included
#define dynacoe_scheduler_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/scheduler.h>
#include <sandboxe/bindings/dynacoe_component.hpp>


/* 
    Bindings for Dynacoe::Scheduler
    
    Notes:
        - GetTasks() -> read-only "tasks" property returns an array
*/

namespace Sandboxe {
namespace Bindings {
    
// member functions 
SANDBOXE_NATIVE_DEF(__scheduler_start_task) {
    auto sch = (Sandboxe::SchedulerObject*)source;
    if (arguments.size() < 3) {
        SANDBOXE_ASSERT__ARG_COUNT(3);
    }

    SANDBOXE_ASSERT__ARG_TYPE(2, ObjectReferenceNonNativeT);
    
    uint32_t t = 0;
    if (arguments.size() > 3) {
        t = arguments[3];
    }
    
    sch->AddNonNativeReference((Sandboxe::Script::Runtime::Object*)arguments[2]);
    sch->StartTask(
        arguments[0],
        arguments[1],
        Sandboxe::ComponentAdaptor::NativeHandler,
        t,
        (Sandboxe::Script::Runtime::Object*)arguments[2]
    );
}


SANDBOXE_NATIVE_DEF(__scheduler_end_task) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto sch = (Sandboxe::SchedulerObject*)source;
    sch->EndTask(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__scheduler_get_task_interval) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto sch = (Sandboxe::SchedulerObject*)source;
    context.SetReturnValue(sch->GetTaskInterval(arguments[0]));
}

SANDBOXE_NATIVE_DEF(__scheduler_pause) {
    auto sch = (Sandboxe::SchedulerObject*)source;
    sch->Pause();
}

SANDBOXE_NATIVE_DEF(__scheduler_resume) {
    auto sch = (Sandboxe::SchedulerObject*)source;
    sch->Resume();
}





// managed properties


SANDBOXE_NATIVE_DEF(__scheduler_get_tasks) {
    auto sch = (Sandboxe::SchedulerObject*)source;
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    auto tasks = sch->GetTasks();
    
    for(uint32_t i = 0; i < tasks.size(); ++i) {
        out.push_back(tasks[i]);
    }
    context.SetReturnArray(out);
}


void dynacoe_scheduler(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::SchedulerT,
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
            
            {"startTask", __scheduler_start_task},
            {"endTask", __scheduler_end_task},
            {"getTaskInterval", __scheduler_get_task_interval},
            {"resume", __scheduler_resume},
            {"pause", __scheduler_pause}
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
            {"onDraw", {__component_get_on_draw, __component_set_on_draw}},
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////
            {"tasks", {__scheduler_get_tasks, SANDBOXE_NATIVE_EMPTY}}


        }
    );
     
}
    
    
    
}
}




#endif
