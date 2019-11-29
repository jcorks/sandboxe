#ifndef h_dynacoe_sandboxe_gui_included
#define h_dynacoe_sandboxe_gui_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/transform.h>


namespace Sandboxe {


class GUIObject : public Dynacoe::GUI, public Sandboxe::ComponentAdaptor {
  public:
    TransformObject * transform;
    GUIObject() : Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::GUIT) {
        width = 8;
        height = 8;
        DefineRegion(8, 8);
        transform = new TransformObject();
        ReplaceTransform(&transform->transformReal);
    }
    
    int width;
    int height;

    void OnStep() {
        Dynacoe::GUI::OnStep();
        Native_OnStep();
    }

    void OnDraw() {
        Native_OnDraw();
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
