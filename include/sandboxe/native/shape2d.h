#ifndef h_dynacoe_sandboxe_shape2d_included
#define h_dynacoe_sandboxe_shape2d_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/transform.h>


namespace Sandboxe {


class Shape2DObject : public Dynacoe::Shape2D, public Sandboxe::ComponentAdaptor {
  public:

    TransformObject * transform;
    Shape2DObject() : Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::Shape2DT) {
        transform = new TransformObject;
        localColor = new Sandboxe::ColorObject;        
        ReplaceTransform(&transform->transformReal);
    }
    
    Sandboxe::ColorObject * localColor;

    
    void OnDraw() {
        color = localColor->color;
        Dynacoe::Shape2D::OnDraw();
    }
    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Shape2D";
    }

    
    #include "component_implementation_common"
    
    
    
};
    
    

    
}


#endif
