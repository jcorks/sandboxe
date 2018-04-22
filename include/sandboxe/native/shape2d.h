#ifndef h_dynacoe_sandboxe_shape2d_included
#define h_dynacoe_sandboxe_shape2d_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/node.h>


namespace Sandboxe {


class Shape2DObject : public Dynacoe::Shape2D, public Sandboxe::ComponentAdaptor {
  public:
    
    Shape2DObject() : Dynacoe::Shape2D(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::Shape2DT) {
        
        localColor = new Sandboxe::ColorObject;        
        localNode = new Sandboxe::NodeObject;


    }
    
    Sandboxe::ColorObject * localColor;
    Sandboxe::NodeObject * localNode;

    
    void OnDraw() {
        color = localColor->color;
        node.local.position = localNode->localTransform->position->vector;
        node.local.rotation = localNode->localTransform->rotation->vector;
        node.local.scale = localNode->localTransform->scale->vector;
        node.local.reverse = localNode->local.reverse;
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