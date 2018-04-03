#ifndef H_sandboxe_binding_helpers_h
#define H_sandboxe_binding_helpers_h

// Simple macros to make definitions simpler
#define SANDBOXE_ASSERT__ARG_COUNT(__T__) if (arguments.size() != __T__) { context.ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: Function accepts only " << __T__ << " arguments"); return;}
#define SANDBOXE_ASSERT__ARG_TYPE(__I__, __T__) if (arguments[__I__].hint != Sandboxe::Script::Runtime::Primitive::TypeHint::__T__) {context.ScriptError(Dynacoe::Chain() << "Sandboxe assertion failure: argument " << __I__ << " is of an unsupported type."); return;}

#endif
