#ifndef H_sandboxe_binding_helpers_h
#define H_sandboxe_binding_helpers_h


#include <sandboxe/script/runtime.h>

// Simple macros to make definitions simpler
#define SANDBOXE_ASSERT__ARG_COUNT(__T__) if (arguments.size() != __T__) { context.ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: Function accepts only " << __T__ << " arguments"); return;}
#define SANDBOXE_ASSERT__ARG_TYPE(__I__, __T__) if (arguments[__I__].hint != Sandboxe::Script::Runtime::Primitive::TypeHint::__T__) {context.ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: argument " << __I__ << " is of an unsupported type."); return;}
#define SANDBOXE_ASSERT__ARG_NATIVE_TYPE(__A__, __T__) if (((int64_t)((Sandboxe::Script::Runtime::Object*)arguments[__A__])->GetNativeAddress(1)) != (uint64_t)Sandboxe::NativeType::__T__) context.ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: Referenced object is an unexpected type (expected " << std::string(NativeTypeToString(Sandboxe::NativeType::__T__)) << " but received " << std::string(NativeTypeToString((Sandboxe::NativeType)(uint64_t)((Sandboxe::Script::Runtime::Object*)arguments[__A__])->GetNativeAddress(1))) << ")");



namespace Sandboxe {

enum class NativeType {
    EntityIDT = 1,
    ComponentT,
    VectorT,
    Node_TransformT
};


const char * NativeTypeToString(NativeType type);

namespace NativeObject {
    // Creates a new runtime object of the given type
    // Is similar to a factor. As a new types are added, 
    // new should be able to handle them.
    Sandboxe::Script::Runtime::Object * New(NativeType, const std::vector<Sandboxe::Script::Runtime::Primitive> & args = {});

    // returns the type of the object.
    NativeType Type(const Sandboxe::Script::Runtime::Object *);

    template<typename T>
    T * Get(const Sandboxe::Script::Runtime::Object * o) {
        return (T*)o->GetNativeAddress();
    }
};





}




#endif
