#ifndef h_dynacoe_sandboxe_text2d_included
#define h_dynacoe_sandboxe_text2d_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/transform.h>


namespace Sandboxe {


class Text2DObject : public Dynacoe::Text2D, public Sandboxe::ComponentAdaptor {
  public:
    TransformObject * transform;
    Text2DObject() : Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::Text2DT) {
        localFont = new Sandboxe::AssetIDObject;
        fontSize = -1;
        spacingMode = (int)Dynacoe::Text2D::SpacingMode::Kerned;
        transform = new TransformObject;
        ReplaceTransform(&transform->transformReal);
    }
    
    Sandboxe::AssetIDObject * localFont;
    int fontSize;
    int spacingMode;
    
    void OnDraw() {
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
