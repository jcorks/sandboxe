#ifndef h_dynacoe_sandboxe_gui_included
#define h_dynacoe_sandboxe_gui_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/node.h>


namespace Sandboxe {


class GUIObject : public Dynacoe::GUI, public Sandboxe::ComponentAdaptor {
  public:
    
    GUIObject() : Dynacoe::GUI(new Sandboxe::NodeObject), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::GUIT) {
        int width = 8;
        int height = 8;
        DefineRegion(8, 8);
    }
    
    int width;
    int height;
    void OnDraw() {
        Dynacoe::GUI::OnDraw();
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