#ifndef h_dynacoe_sandboxe_mutator_included
#define h_dynacoe_sandboxe_mutator_included


#include <sandboxe/native/component.h>


namespace Sandboxe {


class MutatorObject : public Dynacoe::Mutator, public Sandboxe::ComponentAdaptor {
  public:
    
    MutatorObject() : Dynacoe::Mutator(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::MutatorT) {
        localLoop = false;
    }
    
    bool localLoop;
    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Mutator";
    }

    
    #include "component_implementation_common"
    
    
    
};
    
    

    
}


#endif
