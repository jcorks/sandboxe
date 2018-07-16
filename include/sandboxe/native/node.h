#ifndef h_dynacoe_sandboxe_node_included
#define h_dynacoe_sandboxe_node_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/vector.h>


namespace Sandboxe {


class NodeObject : public Dynacoe::Node, public Sandboxe::ComponentAdaptor {
  public:
    



    
    NodeObject() : Dynacoe::Node(),
        Sandboxe::ComponentAdaptor((int) Sandboxe::NativeType::NodeT)
     {        
        isReverse = false;
        localRotation = new Sandboxe::VectorObject(&Rotation());
        localScale = new Sandboxe::VectorObject(&Scale());
        localPosition = new Sandboxe::VectorObject(&Position());

    }
    
    
    
    bool isReverse;

    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Node";
    }



    Sandboxe::VectorObject * localRotation;
    Sandboxe::VectorObject * localPosition;
    Sandboxe::VectorObject * localScale;

    
    
    #include "component_implementation_common"
    
    
};
    
    

    
}


#endif