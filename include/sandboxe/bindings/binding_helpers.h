#ifndef H_sandboxe_binding_helpers_h
#define H_sandboxe_binding_helpers_h

// Simple macros to make definitions simpler
#define SANDBOXE_ASSERT__ARG_COUNT(__T__) if (arguments.size() != __T__) { context.ScriptError(Dynacoe::Chain() << "Sandboxe Script Error: Function accepts only " << __T__ << " arguments"); return Sandboxe::Script::Runtime::Primitive();}
#define SANDBOXE_NORETURN return Sandboxe::Script::Runtime::Primitive();

#endif
