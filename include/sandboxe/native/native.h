#ifndef H_sandboxe_binding_helpers_h
#define H_sandboxe_binding_helpers_h


#include <sandboxe/script/runtime.h>

// Simple macros to make definitions simpler
#define SANDBOXE_ASSERT__ARG_COUNT(__T__) if (arguments.size() != __T__) { context.ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: Function accepts only " << __T__ << " arguments"); return;}
#define SANDBOXE_ASSERT__ARG_TYPE(__I__, __T__) if (arguments[__I__].hint != Sandboxe::Script::Runtime::Primitive::TypeHint::__T__) {context.ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: argument " << __I__ << " is of an unsupported type."); return;}
#define SANDBOXE_ASSERT__ARG_NATIVE(__I__, __T__) if (!dynamic_cast<Sandboxe::__T__*>((Sandboxe::Script::Runtime::Object*)arguments[__I__])) {context.ScriptError(Dynacoe::Chain() << "Unexpected type given as argument " << __I__); return;}




namespace Sandboxe {

enum class NativeType {
    EntityIDT = 1,
    ComponentT,
    VectorT,
    Node_TransformT,
    NodeT,
    ButtonListenerT,
    AssetIDT,
    ByteArrayT,
    ColorT,
    Shape2DT,
    ClockT
};





}




#endif
