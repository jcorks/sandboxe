#ifndef H_sandboxe_binding_helpers_h
#define H_sandboxe_binding_helpers_h


#include <sandboxe/script/runtime.h>

// Simple macros to make definitions simpler
#define SANDBOXE_ASSERT__ARG_COUNT(__T__) if (arguments.size() != __T__) { Sandboxe::Script::Runtime::ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: Function accepts only " << __T__ << " arguments"); return;}
#define SANDBOXE_ASSERT__ARG_TYPE(__I__, __T__) if (arguments[__I__].hint != Sandboxe::Script::Runtime::Primitive::TypeHint::__T__) {Sandboxe::Script::Runtime::ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: argument " << __I__ << " is of an unsupported type."); return;}
#define SANDBOXE_ASSERT__ARG_NATIVE(__I__, __T__) if (!dynamic_cast<Sandboxe::__T__*>((Sandboxe::Script::Runtime::Object*)arguments[__I__])) {Sandboxe::Script::Runtime::ScriptError(Dynacoe::Chain() << "Unexpected type given as argument " << __I__); return;}




namespace Sandboxe {

enum class NativeType {
    EntityIDT = 1,
    ComponentT,
    VectorT,
    TransformT,
    ButtonListenerT,
    AssetIDT,
    ByteArrayT,
    ColorT,
    Shape2DT,
    ClockT,
    Text2DT,
    DataTableT,
    GUIT,
    MutatorT,
    Object2DT,
    Camera_EntityIDT,
    RenderLightT,
    MeshT,
    MaterialT,
    ShaderT,
    RenderMeshT,
    SchedulerT,
    StateControlT,
    DisplayT,
    ActiveSoundT,
    AudioBufferT,
    AudioEffectT,
    AudioBlockT,
    ImageT,
    ImageFrameT,
    ParticleEmitter2D_EntityIDT,
    InputBufferT,
    OutputBufferT,
    ModelT,
    UnicodeListenerT
};





}




#endif
