#ifndef h_dynacoe_sandboxe_text2d_included
#define h_dynacoe_sandboxe_text2d_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/node.h>


namespace Sandboxe {


class Text2DObject : public Dynacoe::Text2D, public Sandboxe::ComponentAdaptor {
  public:
    
    Text2DObject() : Dynacoe::Text2D(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::Text2DT) {
        
        localNode = new Sandboxe::NodeObject;
        localFont = new Sandboxe::AssetIDObject;
        fontSize = -1;
        spacingMode = (int)Dynacoe::Text2D::SpacingMode::Kerned;
    }
    
    Sandboxe::NodeObject * localNode;
    Sandboxe::AssetIDObject * localFont;
    int fontSize;
    int spacingMode;
    
    void OnDraw() {
        node.local.position = localNode->localTransform->position->vector;
        node.local.rotation = localNode->localTransform->rotation->vector;
        node.local.scale = localNode->localTransform->scale->vector;
        node.local.reverse = localNode->localTransform->reverse;
        Dynacoe::Text2D::OnDraw();
    }
    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "Text2D";
    }

    
    #include "component_implementation_common"
    
    
    
};
    
    

    
}


#endif