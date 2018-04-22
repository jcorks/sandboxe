#ifndef h_dynacoe_sandboxe_gui_included
#define h_dynacoe_sandboxe_gui_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/node.h>


namespace Sandboxe {


class GUIObject : public Dynacoe::GUI, public Sandboxe::ComponentAdaptor {
  public:
    
    GUIObject() : Dynacoe::GUI(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::GUIT) {
        int width = 8;
        int height = 8;
        DefineRegion(8, 8);
        localNode = new Sandboxe::NodeObject;
    }
    
    Sandboxe::NodeObject * localNode;
    int width;
    int height;
    void OnDraw() {
        node.local.position = localNode->localTransform->position->vector;
        node.local.rotation = localNode->localTransform->rotation->vector;
        node.local.scale = localNode->localTransform->scale->vector;
        node.local.reverse = localNode->local.reverse;
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