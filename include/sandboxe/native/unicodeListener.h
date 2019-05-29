#ifndef sandboxe_native_unicode_listener_included
#define sandboxe_native_unicode_listener_included

namespace Sandboxe {
    
class UnicodeListenerObject : public Dynacoe::UnicodeListener, public Sandboxe::Script::Runtime::Object {
  public:
    UnicodeListenerObject() :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::UnicodeListenerT)
    {
        onNewUnicode = nullptr;
        onRepeatUnicode = nullptr;
    }
    

    Sandboxe::Script::Runtime::Object * onNewUnicode;
    Sandboxe::Script::Runtime::Object * onRepeatUnicode;


    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "UnicodeListener";
    }
      
    void OnNewUnicode(int unicode) {
        if (onNewUnicode) onNewUnicode->CallMethod("", {unicode});
    }

    void OnRepeatUnicode(int unicode) {
        if (onRepeatUnicode) onRepeatUnicode->CallMethod("", {unicode});
    }



    
};
    
}

#endif
