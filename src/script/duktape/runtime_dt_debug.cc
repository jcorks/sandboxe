#include <sandboxe/script/duktape/runtime_dt_debug.h>
#ifdef SANDBOXE_DT_DEBUG

using namespace Sandboxe::Script::Runtime;



static DTContext * ctx_attached = nullptr;



DTDebugger::DTDebugger(DTContext * context) {
    ctx = context;
    paused = false;
}

void DTDebugger::Pause() {
    if (ctx_attached) {
        return;
    }
    ctx_attached = ctx;
    paused = true;

    Dynacoe::Console::Show(true);
    Dynacoe::Engine::Break();
    
    while(Dynacoe::Engine::IsPaused()) {
        Dynacoe::Engine::Iterate();
    }
    paused = false;
    Dynacoe::Engine::Resume();

    //duk_debugger_detach(ctx_attached->GetCTX());
    ctx_attached = nullptr;    
}


void DTDebugger::Resume() {
    if (!ctx_attached) return;
    // send request
    //duk_debugger_cooperate(ctx_attached->GetCTX());
    Dynacoe::Console::Show(false);
    Dynacoe::Engine::Resume();
}




#endif
