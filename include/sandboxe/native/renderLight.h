#ifndef h_render_light_included
#define h_render_light_included

#include <sandboxe/native/native.h>

namespace Sandboxe {
class RenderLightObject : public Sandboxe::ComponentAdaptor, public Dynacoe::RenderLight {
  public:
    RenderLightObject() : Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::RenderLightT) {
        localPosition = new VectorObject();
        localColor = new ColorObject();
        localEnabled = true;
        localType = Dynacoe::RenderLight::Light::Point;
    } 
    
    void OnStep() {
        state.position = localPosition->vector;
        state.color = localColor->color;
    }
    
    void OnDraw() {
        Dynacoe::RenderLight::OnDraw();
    }
    
    void OnGarbageCollection(){}
    
    const char * GetObjectName() const {
        return "RenderLight";
    }
    
    
    VectorObject * localPosition;
    ColorObject * localColor;
    bool localEnabled;
    Dynacoe::RenderLight::Light localType;
    
    #include "component_implementation_common"
};
}




#endif