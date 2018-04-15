#ifndef h_dynacoe_sandboxe_clock_included
#define h_dynacoe_sandboxe_clock_included


#include <sandboxe/native/component.h>



namespace Sandboxe {




class ClockObject : public Dynacoe::Clock, public Sandboxe::ComponentAdaptor {
  public:
    
    ClockObject() : 
        Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::ClockT){}

    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Clock";
    }


    
    
    
    #include "component_implementation_common"
    
    
};
    
    

    
}


#endif