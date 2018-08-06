#ifndef sandboxe_native_button_listener_included
#define sandboxe_native_button_listener_included

namespace Sandboxe {
    
class ButtonListenerObject : public Dynacoe::ButtonListener, public Sandboxe::Script::Runtime::Object {
  public:
    ButtonListenerObject() :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ButtonListenerT)
    {
        onPress = nullptr;
        onHold = nullptr;
        onRelease = nullptr;

    }
    
    Sandboxe::Script::Runtime::Object * onPress;
    Sandboxe::Script::Runtime::Object * onHold;
    Sandboxe::Script::Runtime::Object * onRelease;


    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "ButtonListener";
    }
      
    void OnPress() {
        if (onPress) onPress->CallMethod();
    }

    void OnHold() {
        if (onHold) onHold->CallMethod();
    }

    void OnRelease() {
        if (onRelease) onRelease->CallMethod();
    }

    
};
    
}

#endif
