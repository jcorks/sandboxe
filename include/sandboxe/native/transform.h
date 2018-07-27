#ifndef h_dynacoe_sandboxe_node_included
#define h_dynacoe_sandboxe_node_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/vector.h>


namespace Sandboxe {


class TransformObject : public Sandboxe::Script::Runtime::Object {
  public:
    Transform transformReal;

    static void OnPosition(VectorObject * object, void * data) {
        TransformObject * t;
        t->transformReal.GetPosition();
    }

    static void OnRotation(VectorObject * object, void * data) {
        TransformObject * t;
        t->transformReal.GetRotation();
    }

    static void OnScale(VectorObject * object, void * data) {
        TransformObject * t;
        t->transformReal.GetScale();
    }

    
    TransformObject() : 
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::TransformT)
     {        
        isReverse = false;
        localRotation = new Sandboxe::VectorObject(&transformReal.Rotation());
        localScale = new Sandboxe::VectorObject(&transformReal.Scale());
        localPosition = new Sandboxe::VectorObject(&transformReal.Position());

        localPosition->delta.Set(OnPosition, this);
        localRotation->delta.Set(OnRotation, this);
        localScale->delta.Set(OnScale, this);

    }
    
    
    
    bool isReverse;

    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Transform";
    }



    Sandboxe::VectorObject * localRotation;
    Sandboxe::VectorObject * localPosition;
    Sandboxe::VectorObject * localScale;

    
    
};
    
    

    
}


#endif