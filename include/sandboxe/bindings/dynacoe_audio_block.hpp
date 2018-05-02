#ifndef dynacoe_audio_block_sandboxe_binding_included
#define dynacoe_audio_block_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/audioBlock.h>
#include <Dynacoe/AudioBlock.h>
/*
    Bindings of Dynacoe::AudioBlock
    Nodes:
        - static creation fns are not bound 
        - editing / writing of single samples are not bound.
        - read() has been added, which reads all samples of the block as an array of floats using GetSample()
        - Append() is not bound

*/


namespace Sandboxe {
namespace Bindings {
    

// managed properties

static Dynacoe::AudioBlock * __audio_block_retrieve(Sandboxe::Script::Runtime::Object * source) {
    auto obj = (Sandboxe::AudioBlockObject*)source;
    if (!obj->id.Valid()) return nullptr;
    return &Dynacoe::Assets::Get<Dynacoe::AudioBlock>(obj->id);
}

SANDBOXE_NATIVE_DEF(__audio_block_define) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto a = context.GetArrayArgument(0);
    if (!a) return;
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    uint32_t sampleArraySize = a->size()/2;
    Dynacoe::AudioSample * sampleArray = new Dynacoe::AudioSample[sampleArraySize];
    for(uint32_t i = 0; i < sampleArraySize; ++i) {
        sampleArray[i].leftSample    = (int)(*a)[i*2];
        sampleArray[i].rightSample   = (int)(*a)[i*2+1];
    }
    block->Define(sampleArray, sampleArraySize);
}

SANDBOXE_NATIVE_DEF(__audio_block_read) {
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    uint32_t sampleArraySize = block->NumSamples();
    std::vector<Sandboxe::Script::Runtime::Primitive> sampleArray(sampleArraySize*2);
    for(uint32_t i = 0; i < sampleArraySize; ++i) {
        sampleArray[i*2]   = block->GetSample(i).leftSample;
        sampleArray[i*2+1] = block->GetSample(i).rightSample;
    }
    context.SetReturnArray(sampleArray);
}

SANDBOXE_NATIVE_DEF(__audio_block_get_sub_block) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    auto out = new Sandboxe::AudioBlockObject(
        block->GetSubBlock(arguments[0], arguments[1])->GetAssetName()
    );
    context.SetReturnValue(out);
}

SANDBOXE_NATIVE_DEF(__audio_block_append_block) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, AudioBlockObject);
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    auto other = (Sandboxe::AudioBlockObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    if (!other->id.Valid()) return;
    auto otherBlock = &Dynacoe::Assets::Get<Dynacoe::AudioBlock>(other->id);
    
    block->AppendBlock(otherBlock);
}

SANDBOXE_NATIVE_DEF(__audio_block_remove_block) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    block->RemoveBlock(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__audio_block_insert_block) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(1, AudioBlockObject);
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    auto other = (Sandboxe::AudioBlockObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    if (!other->id.Valid()) return;
    auto otherBlock = &Dynacoe::Assets::Get<Dynacoe::AudioBlock>(other->id);
    
    block->InsertBlock(
        arguments[0],
        otherBlock
    );
}


SANDBOXE_NATIVE_DEF(__audio_block_get_seconds_from_sample) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    context.SetReturnValue(block->GetSecondsFromSamples(arguments[0]));
}


SANDBOXE_NATIVE_DEF(__audio_block_get_sample_from_seconds) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto block = __audio_block_retrieve(source);
    if (!block) return;

    context.SetReturnValue(block->GetSampleFromSeconds(arguments[0]));
}



//// managed properties 

SANDBOXE_NATIVE_DEF(__audio_block_get_volume) {
    auto block = __audio_block_retrieve(source);
    if (!block) return;
    context.SetReturnValue(block->GetVolume());
}

SANDBOXE_NATIVE_DEF(__audio_block_get_panning) {
    auto block = __audio_block_retrieve(source);
    if (!block) return;
    context.SetReturnValue(block->GetPanning());
}

SANDBOXE_NATIVE_DEF(__audio_block_get_num_bytes) {
    auto block = __audio_block_retrieve(source);
    if (!block) return;
    context.SetReturnValue(block->NumBytes());
}

SANDBOXE_NATIVE_DEF(__audio_block_get_num_samples) {
    auto block = __audio_block_retrieve(source);
    if (!block) return;
    context.SetReturnValue(block->NumSamples());
}





SANDBOXE_NATIVE_DEF(__audio_block_set_panning) {
    auto block = __audio_block_retrieve(source);
    if (!block) return;
    block->SetPanning(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__audio_block_set_volume) {
    auto block = __audio_block_retrieve(source);
    if (!block) return;
    block->SetVolume(arguments[0]);
}


void dynacoe_audio_block(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::AudioBlockT,
        // methods
        {
            {"define", __audio_block_define},
            {"read", __audio_block_define},
            {"getSubBlock", __audio_block_get_sub_block},
            {"appendBlock", __audio_block_append_block},
            {"removeBlock", __audio_block_remove_block},
            {"insertBlock", __audio_block_insert_block},
            {"getSecondsFromSample", __audio_block_get_seconds_from_sample},
            {"getSampleFromSeconds", __audio_block_get_sample_from_seconds},

        },

        // properties
        {
        },
        
        // managed properties,
        {
            {"volume", {__audio_block_get_volume, __audio_block_set_volume}},
            {"panning", {__audio_block_get_panning, __audio_block_set_panning}},
            {"numSamples", {__audio_block_get_num_bytes, SANDBOXE_NATIVE_EMPTY}},
            {"numBytes", {__audio_block_get_num_bytes, SANDBOXE_NATIVE_EMPTY}},

        } 
    );
      
}
    
    
    
}
}




#endif