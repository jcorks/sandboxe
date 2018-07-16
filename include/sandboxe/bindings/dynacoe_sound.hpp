#ifndef H_sandboxe_bindings_dynacoe_sound
#define H_sandboxe_bindings_dynacoe_sound
#include <sandboxe/native/native.h>
#include <sandboxe/native/activeSound.h>

/*
    Dynacoe::Sound Bindings
    
    notes:
        -ChannelRemoveEffect() is not bound
        -AudioEffects are function objects

*/

namespace Sandboxe {
namespace Bindings {


SANDBOXE_NATIVE_DEF(__sound_is_playing) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, AssetIDObject);
    auto id = (Sandboxe::AssetIDObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    context.SetReturnValue(Dynacoe::Sound::IsPlaying(id->id));
}

SANDBOXE_NATIVE_DEF(__sound_play_audio) {
    if (arguments.size() < 1) {
        SANDBOXE_ASSERT__ARG_COUNT(1);
    }
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, AssetIDObject);
    uint8_t ef    = arguments.size() > 1 ? (int)arguments[1] : 0;
    float volume  = arguments.size() > 2 ? (float)arguments[2] : 1.f;
    float panning = arguments.size() > 3 ? (float)arguments[3] : .5f;
    auto id = (Sandboxe::AssetIDObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    auto out = new ActiveSoundObject();
    
    out->sound = Dynacoe::Sound::PlayAudio(
        id->id,
        ef,
        volume,
        panning
    );
    
    out->volume = volume;
    out->panning = panning;
    out->channel = ef;
    out->repeat = false;
    context.SetReturnValue(out);
}







class AudioBufferObject : public Sandboxe::Script::Runtime::Object {
  public:
    virtual ~AudioBufferObject(){}
    AudioBufferObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::AudioBufferT){}

    float * data;
    uint32_t length;

    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "AudioBuffer";
    }
    
};



SANDBOXE_NATIVE_DEF(__audio_buffer_get) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto obj = (AudioBufferObject*)source;
    uint32_t i = arguments[0];
    if (i > obj->length) return;
    context.SetReturnValue(obj->data[i]);
}

SANDBOXE_NATIVE_DEF(__audio_buffer_length) {
    auto obj = (AudioBufferObject*)source;
    context.SetReturnValue(obj->length);
}


SANDBOXE_NATIVE_DEF(__audio_buffer_set) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto obj = (AudioBufferObject*)source;
    uint32_t i = arguments[0];
    if (i > obj->length) return;
    obj->data[i] = arguments[1];
}





class AudioEffectObject : public Dynacoe::AudioEffect, public Sandboxe::Script::Runtime::Object {
  public:
    static std::vector<AudioEffectObject*> base[256];
    AudioEffectObject(Sandboxe::Script::Runtime::Object * obj, uint8_t ch) 
        : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::AudioEffectT)
    {
        AddNonNativeReference(obj);
        bufferObj = new AudioBufferObject;
        base[ch].push_back(this);
        fn = obj;
    }
    
    virtual ~AudioEffectObject() {
        delete bufferObj;
    }
    
    static void ClearChannel(uint8_t ch) {
        std::vector<AudioEffectObject*> & v = base[ch];
        for(uint32_t i = 0; i < v.size(); ++i) {
            delete v[i];
        }
        v.clear();
    }
    
    
    Sandboxe::Script::Runtime::Object * fn;
    AudioBufferObject * bufferObj;
    
    void operator()(float * data, uint32_t numValues) const {
        bufferObj->data = data;
        bufferObj->length = numValues;
        fn->CallMethod("", {bufferObj});
        bufferObj->length = 0;
    }
    
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "AudioEffect";
    }
    
};
std::vector<AudioEffectObject*> AudioEffectObject::base[256];


SANDBOXE_NATIVE_DEF(__sound_channel_add_effect) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    AudioEffectObject * fnObj = new AudioEffectObject(arguments[0], (int)arguments[1]);
    Dynacoe::Sound::ChannelAddEffect(fnObj, (int)arguments[1]);
}

SANDBOXE_NATIVE_DEF(__sound_channel_reset) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    uint8_t ch = (int) arguments[0];
    
    AudioEffectObject::ClearChannel(ch);
    Dynacoe::Sound::ChannelReset(ch);
}

SANDBOXE_NATIVE_DEF(__sound_channel_set_volume) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    Dynacoe::Sound::ChannelSetVolume((int)arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__sound_channel_set_panning) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    Dynacoe::Sound::ChannelSetVolume((int)arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__sound_channel_keep_awake) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    Dynacoe::Sound::ChannelKeepAwake((int)arguments[0], arguments[1]);
}


void dynacoe_sound(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::AudioEffectT,
        {},{},{}
    );
    
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::AudioBufferT,
        {
            {"set", __audio_buffer_set},
            {"get", __audio_buffer_get},
            {"length", __audio_buffer_length},

        },{},{}
    );
    
    fns.push_back({"__sound_is_playing", __sound_is_playing});
    fns.push_back({"__sound_play_audio", __sound_play_audio});

    fns.push_back({"__sound_channel_add_effect", __sound_channel_add_effect});
    fns.push_back({"__sound_channel_reset", __sound_channel_reset});
    fns.push_back({"__sound_channel_set_volume", __sound_channel_set_volume});
    fns.push_back({"__sound_channel_set_panning", __sound_channel_set_panning});
    fns.push_back({"__sound_channel_keep_awake", __sound_channel_keep_awake});


}

}
}



#endif
