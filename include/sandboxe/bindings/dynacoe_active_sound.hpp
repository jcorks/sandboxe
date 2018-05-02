#ifndef dynacoe_active_sound_sandboxe_binding_included
#define dynacoe_active_sound_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/activeSound.h>

/*
    Bindings of Dynacoe::ActiveSound 
    Nodes:
        - Most Sets are ew properties with local copies of values

*/


namespace Sandboxe {
namespace Bindings {
    

// managed properties



SANDBOXE_NATIVE_DEF(__active_sound_seek) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->sound.Seek(arguments[0]);    
}

SANDBOXE_NATIVE_DEF(__active_sound_stop) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->sound.Stop();    
}

SANDBOXE_NATIVE_DEF(__active_sound_pause) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->sound.Pause();    
}

SANDBOXE_NATIVE_DEF(__active_sound_resume) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->sound.Resume();    
}







SANDBOXE_NATIVE_DEF(__active_sound_get_volume) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    context.SetReturnValue(obj->volume);    
}

SANDBOXE_NATIVE_DEF(__active_sound_set_volume) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->volume = arguments[0];
    obj->sound.SetVolume(obj->volume);
}
 


SANDBOXE_NATIVE_DEF(__active_sound_get_panning) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    context.SetReturnValue(obj->panning);    
}

SANDBOXE_NATIVE_DEF(__active_sound_set_panning) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->panning = arguments[0];
    obj->sound.SetPanning(obj->panning);
}




SANDBOXE_NATIVE_DEF(__active_sound_get_repeat) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    context.SetReturnValue(obj->repeat);    
}

SANDBOXE_NATIVE_DEF(__active_sound_set_repeat) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->repeat = arguments[0];
    obj->sound.SetRepeat(obj->repeat);
}




SANDBOXE_NATIVE_DEF(__active_sound_get_channel) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    context.SetReturnValue(obj->channel);    
}

SANDBOXE_NATIVE_DEF(__active_sound_set_channel) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    obj->channel = arguments[0];
    obj->sound.SetChannel(obj->channel);
}



SANDBOXE_NATIVE_DEF(__active_sound_get_valid) {
    auto obj = (Sandboxe::ActiveSoundObject*)source;
    context.SetReturnValue(obj->sound.Valid());    
}




void dynacoe_active_sound(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::ActiveSoundT,
        // methods
        {
            {"seek", __active_sound_seek},
            {"stop", __active_sound_stop},
            {"pause", __active_sound_stop},
            {"resume", __active_sound_stop},

        },

        // properties
        {
        },
        
        // managed properties,
        {
            {"volume", {__active_sound_get_volume, __active_sound_set_volume}},
            {"panning", {__active_sound_get_panning, __active_sound_set_panning}},
            {"repeat", {__active_sound_get_repeat, __active_sound_set_repeat}},
            {"channel", {__active_sound_get_channel, __active_sound_set_channel}},
            {"valid", {__active_sound_get_valid, SANDBOXE_NATIVE_EMPTY}},

        } 
    );
      
}
    
    
    
}
}




#endif