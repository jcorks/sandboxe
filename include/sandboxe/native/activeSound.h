#ifndef h_active_sound_sandboxe_dynacoe_included 
#define h_active_sound_sandboxe_dynacoe_included

namespace Sandboxe {
class ActiveSoundObject : public Sandboxe::Script::Runtime::Object {
  public:    
    ActiveSoundObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ActiveSoundT){}
    
    Dynacoe::ActiveSound sound;
    float volume;
    float panning;
    uint32_t channel;
    bool repeat;
    

    void OnGarbageCollection(){}

    

    const char * GetObjectName() const {
        return "ActiveSound";
    }
};
}


#endif