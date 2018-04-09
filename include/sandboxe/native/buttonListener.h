#ifndef sandboxe_native_button_listener_included
#define sandboxe_native_button_listener_included

namespace Sandboxe {
    
class ButtonListener : public Dynacoe::ButtonListener {
  public:
    ButtonListener(Sandboxe::Script::Runtime::Object * obj) {
        object = obj;
    }
      
    void OnPress() {
        object->CallMethod("onPress");
    }

    void OnHold() {
        object->CallMethod("onHold");
    }

    void OnRelease() {
        object->CallMethod("onRelease");
    }

    
    Sandboxe::Script::Runtime::Object * object;
};
    
}

#endif