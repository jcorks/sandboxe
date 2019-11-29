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
        localColor = new Sandboxe::ColorObject;
        localColor->color = "white";
        localColor->delta.Set(ColorChanged, this);

        localCharPosition = new Sandboxe::VectorObject();
        localDimensions = new Sandboxe::VectorObject();
    }

    static void ColorChanged(ColorObject * object, void * data) {
        Text2DObject * t = (Text2DObject*)data;
        t->SetTextColor(t->localColor->color);
    }

    
    Sandboxe::AssetIDObject * localFont;
    int fontSize;
    int spacingMode;
    Sandboxe::ColorObject * localColor;


    void OnStep() {
        Native_OnStep();
    }
    
    void OnDraw() {
        Dynacoe::Text2D::OnDraw();
        Native_OnDraw();
    }

    void OnGarbageCollection() {
        // delete local objects?? maybe??
    }
    
    
    const char * GetObjectName() const {
        return "Text2D";
    }

    Sandboxe::VectorObject * localCharPosition;
    Sandboxe::VectorObject * localDimensions;
    
    #include "component_implementation_common"
    
    
    
};
    
    

    
}


#endif
