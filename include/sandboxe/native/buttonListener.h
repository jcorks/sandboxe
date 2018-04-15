#ifndef sandboxe_native_button_listener_included
#define sandboxe_native_button_listener_included

namespace Sandboxe {
    
class ButtonListenerObject : public Dynacoe::ButtonListener, public Sandboxe::Script::Runtime::Object {
  public:
    ButtonListenerObject() :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ButtonListenerT)
    {
        
    }
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "ButtonListener";
    }
      
    void OnPress() {
        CallMethod("onPress");
    }

    void OnHold() {
        CallMethod("onHold");
    }

    void OnRelease() {
        CallMethod("onRelease");
    }

    
};
    
}

#endif