#ifndef h_dynacoe_sandboxe_scheduler_included
#define h_dynacoe_sandboxe_scheduler_included


#include <sandboxe/native/component.h>



namespace Sandboxe {




class SchedulerObject : public Dynacoe::Scheduler, public Sandboxe::ComponentAdaptor {
  public:
    
    SchedulerObject() : 
        Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::SchedulerT){}

    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Scheduler";
    }


    
    
    
    #include "component_implementation_common"
    
    
};
    
    

    
}


#endif