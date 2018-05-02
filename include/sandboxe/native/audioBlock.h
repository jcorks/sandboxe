#ifndef h_sandboxe_audio_block_included
#define h_sandboxe_audio_block_included
#include <cassert>
#include <sandboxe/native/delta.h>
namespace Sandboxe {
    
class AudioBlockObject : public Sandboxe::Script::Runtime::Object {
  public:
    AudioBlockObject(const std::string & name) : 
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::AudioBlockT)
        {
            id = Dynacoe::Assets::Query(Dynacoe::Assets::Type::Audio, name);
        }
        

    Dynacoe::AssetID id;
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "AudioBlock";
    }
        
};

}


#endif