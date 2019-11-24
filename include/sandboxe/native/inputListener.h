#ifndef sandboxe_native_input_listener_included
#define sandboxe_native_input_listener_included

namespace Sandboxe {
    
class InputListenerObject : public Dynacoe::InputListener, public Sandboxe::Script::Runtime::Object {
  public:
    InputListenerObject() :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::InputListenerT)
    {
        onPress = nullptr;
        onRelease = nullptr;
        onActive = nullptr;
        onChange = nullptr;

    }
    
    Sandboxe::Script::Runtime::Object * onPress;
    Sandboxe::Script::Runtime::Object * onActive;
    Sandboxe::Script::Runtime::Object * onChange;
    Sandboxe::Script::Runtime::Object * onRelease;


    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "InputListener";
    }
      
    void OnPress(int i) {
        if (onPress) onPress->CallMethod("", {i});
    }

    void OnActive(int i, float v) {
        if (onActive) onActive->CallMethod("", {i, v});
    }

    void OnChange(int i, float v) {
        if (onChange) onChange->CallMethod("", {i, v});
    }

    void OnRelease(int i) {
        if (onRelease) onRelease->CallMethod("", {i});
    }

    
};
    
}

#endif
