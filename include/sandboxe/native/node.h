#ifndef h_dynacoe_sandboxe_node_included
#define h_dynacoe_sandboxe_node_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/vector.h>


namespace Sandboxe {

class Node_TransformObject : public Sandboxe::Script::Runtime::Object {
  public:
      
    static void OnChange_Position(VectorObject * object, void * data) {
        Node_TransformObject * node = (Node_TransformObject*)data;
        node->t->position = object->vector;
    }    

    static void OnChange_Scale(VectorObject * object, void * data) {
        Node_TransformObject * node = (Node_TransformObject*)data;
        node->t->scale = object->vector;
    }    

    static void OnChange_Rotation(VectorObject * object, void * data) {
        Node_TransformObject * node = (Node_TransformObject*)data;
        node->t->rotation = object->vector;
    }    
      
    Node_TransformObject() :
        Sandboxe::Script::Runtime::Object((int) Sandboxe::NativeType::Node_TransformT)
    {
        
        position = new Sandboxe::VectorObject;
        scale = new Sandboxe::VectorObject({1.f, 1.f, 1.f});
        rotation = new Sandboxe::VectorObject;
        
        position->delta.Set(OnChange_Position, (void*)this);
        rotation->delta.Set(OnChange_Rotation, (void*)this);
        scale   ->delta.Set(OnChange_Scale,    (void*)this);
        
        
    }
      
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "Node Transform";
    }
      
    Sandboxe::VectorObject * position;
    Sandboxe::VectorObject * scale;
    Sandboxe::VectorObject * rotation;
    Dynacoe::Node::Transform * t;

};


class NodeObject : public Dynacoe::Node, public Sandboxe::ComponentAdaptor {
  public:
    



    
    NodeObject() : Dynacoe::Node(),
        Sandboxe::ComponentAdaptor((int) Sandboxe::NativeType::NodeT)
     {
        
        localTransform = new Sandboxe::Node_TransformObject();        
        Set("local", localTransform);
        localTransform->t = &local;
        

        
        globalTransform = new Sandboxe::Node_TransformObject();        
        Set("global", globalTransform);
        globalTransform->t = &global;

        
        //local.scale = Dynacoe::Vector(0, 0, 0);
    }

    
    Sandboxe::Node_TransformObject * localTransform;
    Sandboxe::Node_TransformObject * globalTransform;

    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Node";
    }




    
    
    
    void OnTransformUpdate() {
        globalTransform->position->vector = global.position;
        globalTransform->scale->vector = global.scale;
        globalTransform->rotation->vector = global.rotation;
    }
    
    
    
    
    #include "component_implementation_common"
    
    
};
    
    

    
}


#endif