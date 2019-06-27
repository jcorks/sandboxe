#include <sandboxe/script/duktape/runtime_dt_debug.h>
#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <cassert>
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


std::string DTDebugger::GetBacktraceString() const {
    duk_context * source = ctx->GetCTX();
    int stackSize = duk_get_top(source);

    int level = -1;   
    duk_inspect_callstack_entry(source, level);
    std::vector<std::string> fns;
    std::vector<std::string> lineNumbers;
    std::vector<std::string> filenames;

    std::string empty;
    while(true) {
        TObject current(source);
    
        if (std::string(current.ThisAsPrimitive()) == empty) {
            duk_pop(source);
            break;
        } else {
            level--;
            std::string fn = "";
            std::string lineNumber = current.Get("lineNumber");
            std::string filename = "";

            duk_get_prop_string(source, -1, "function");
            {
                TObject nameObject(source);
                std::string temp = nameObject.Get("name");
                filename = nameObject.Get("fileName");
                if (temp != "") {
                    fn = temp + "()";
                }
            }
            duk_pop(source);

            if (!(lineNumber == "0" && filename == "undefined")) {
                fns.push_back(fn);
                lineNumbers.push_back(lineNumber);
                filenames.push_back(filename);
            }
            duk_pop(source);
            duk_inspect_callstack_entry(source, level);
        }
    }

    Dynacoe::Chain out = "Backtrace:\n";
    for(uint32_t i = 0; i < fns.size(); ++i) {
        out = out <<  "    (#" << i << ") -> " << fns[i] <<  "" << filenames[i] << " @ Line " << lineNumbers[i] << "\n"; 
    }


    assert(duk_get_top(source) == stackSize);
    return out;
}




#endif
