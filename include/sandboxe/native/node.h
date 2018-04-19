#ifndef h_dynacoe_sandboxe_node_included
#define h_dynacoe_sandboxe_node_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/vector.h>


namespace Sandboxe {

class Node_TransformObject : public Sandboxe::Script::Runtime::Object {
  public:
    Node_TransformObject() :
        Sandboxe::Script::Runtime::Object((int) Sandboxe::NativeType::Node_TransformT)
    {
        
        position = new Sandboxe::VectorObject;
        scale = new Sandboxe::VectorObject({1.f, 1.f, 1.f});
        rotation = new Sandboxe::VectorObject;
        
        reverse = false;
    }
      
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "Node Transform";
    }
      
    Sandboxe::VectorObject * position;
    Sandboxe::VectorObject * scale;
    Sandboxe::VectorObject * rotation;
    
    bool reverse;
};


class NodeObject : public Dynacoe::Node, public Sandboxe::ComponentAdaptor {
  public:
    
    NodeObject() : Dynacoe::Node(),
        Sandboxe::ComponentAdaptor((int) Sandboxe::NativeType::NodeT)
     {
        
        localTransform = new Sandboxe::Node_TransformObject();        
        Set("local", localTransform);
        
        
        globalTransform = new Sandboxe::Node_TransformObject();        
        Set("global", globalTransform);
        
        local.scale = Dynacoe::Vector(0, 0, 0);
    }

    
    Sandboxe::Node_TransformObject * localTransform;
    Sandboxe::Node_TransformObject * globalTransform;

    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Node";
    }




    void OnStep() {

        local.position = localTransform->position->vector;
        local.scale = localTransform->scale->vector;
        local.rotation = localTransform->rotation->vector;
        local.reverse = localTransform->reverse;
        
        Dynacoe::Node::OnStep();
    }
    
    
    
    
    void OnTransformUpdate() {
        globalTransform->position->vector = global.position;
        globalTransform->scale->vector = global.scale;
        globalTransform->rotation->vector = global.rotation;
        globalTransform->reverse = global.reverse;
    }
    
    
    
    
    #include "component_implementation_common"
    
    
};
    
    

    
}


#endif