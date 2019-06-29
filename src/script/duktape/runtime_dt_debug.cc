#include <sandboxe/script/duktape/runtime_dt_debug.h>
#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <duk_trans_dvalue.h>
#include <cassert>
#ifdef SANDBOXE_DT_DEBUG

using namespace Sandboxe::Script::Runtime;



static DTContext * ctx_attached = nullptr;
static duk_trans_dvalue_ctx * trans_ctx = nullptr;
static std::vector<std::string> messagesPending;
static DTDebugger * debugger = nullptr;


enum DTCommand{
    DT_COMMAND__NONE,
    DT_COMMAND__INIT,
    DT_COMMAND__PAUSE,
    DT_COMMAND__RESUME,
    DT_COMMAND__STEP_INTO,
    DT_COMMAND__STEP_OVER,
    DT_COMMAND__STEP_OUT,
    DT_COMMAND__ADD_BREAK,
    DT_COMMAND__GET_CALL_STACK,


};

static DTCommand lastCommand;



static void sandboxe_dt_trans_command__pause(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x12);  
    duk_trans_dvalue_send_eom(ctx);
    lastCommand = DT_COMMAND__PAUSE;
}


static void sandboxe_dt_trans_command__resume(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x13);  
    duk_trans_dvalue_send_eom(ctx);
    lastCommand = DT_COMMAND__RESUME;
    
}


static void sandboxe_dt_trans_command__step_into(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x14);  
    duk_trans_dvalue_send_eom(ctx);
    lastCommand = DT_COMMAND__STEP_INTO;
}

static void sandboxe_dt_trans_command__step_over(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x15);  
    duk_trans_dvalue_send_eom(ctx);
    lastCommand = DT_COMMAND__STEP_OVER;
}

static void sandboxe_dt_trans_command__step_out(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x16);  
    duk_trans_dvalue_send_eom(ctx);
    lastCommand = DT_COMMAND__STEP_OUT;
}

static void sandboxe_dt_trans_command__add_break(duk_trans_dvalue_ctx * ctx, const std::string & filename, int line) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x18);  
    duk_trans_dvalue_send_string(ctx, filename.c_str());
    duk_trans_dvalue_send_integer(ctx, line);
    duk_trans_dvalue_send_eom(ctx);
    lastCommand = DT_COMMAND__ADD_BREAK;
}

static void sandboxe_dt_trans_command__get_call_stack(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x1c);  
    duk_trans_dvalue_send_eom(ctx);
    lastCommand = DT_COMMAND__GET_CALL_STACK;
    
}

 
void sandboxe_dt_trans_received(duk_trans_dvalue_ctx * ctx, duk_dvalue * dv) {
    char output[DUK_DVALUE_TOSTRING_BUFLEN];    
    duk_dvalue_to_string(dv, output);
    printf("dvalue received: %s\n", output);
    messagesPending.push_back(output);
    fflush(stdout);
}

void sandboxe_dt_trans_cooperate(duk_trans_dvalue_ctx * ctx, int block) {
    
    if (messagesPending.size() && messagesPending[messagesPending.size()-1] == "EOM") {
        switch(lastCommand) {
          case DT_COMMAND__ADD_BREAK:
            if (messagesPending[0] == "ERR") {
                Dynacoe::Console::Error() << "Could not add breakpoint! (" << messagesPending[2] << "\n";
            } else {
                Dynacoe::Console::Info() << "Added breakpoint " << messagesPending[0] << "\n";
            }
            break;
          
        
            
          case DT_COMMAND__RESUME:
            Dynacoe::Console::Show(false);
            Dynacoe::Engine::Resume();
            printf("Received resume response.\n"); fflush(stdout);
            break;
            
          case DT_COMMAND__GET_CALL_STACK:
            {
                Dynacoe::Console::Info() << "Callstack:\n";

                for(size_t i = 0; i < messagesPending.size()/4; ++i) {
                    Dynacoe::Console::Info() <<
                        messagesPending[i*4 + 1] << "()\t" <<
                        messagesPending[i*4 + 0] << ":" <<
                        messagesPending[i*4 + 2] << "\n";
                }
            }
            break;


          default:
            sandboxe_dt_trans_command__get_call_stack(ctx);
            printf("Received %d messages.\n", messagesPending.size());
            fflush(stdout);
        }
        messagesPending.clear();

    
    }
    if (!block) return; // still receiving messages

    
    Dynacoe::Engine::Iterate();

}


void sandboxe_dt_trans_handshake(duk_trans_dvalue_ctx * ctx, const char * handshake) {
    printf("handshake: %s\n", handshake);
    fflush(stdout);

}

void sandboxe_dt_trans_detached(duk_trans_dvalue_ctx * ctx) {
    printf("was detached!\n");
    fflush(stdout);

}

DTDebugger::DTDebugger(DTContext * context) {
    ctx = context;
    paused = false;
}

void DTDebugger::Pause() {
    if (ctx_attached) {
        return;
    }

    trans_ctx = duk_trans_dvalue_init();
    if (!trans_ctx) {
        return;
    }


    ctx_attached = ctx;
    debugger = this;
    paused = true;

    Dynacoe::Console::Show(true);
    Dynacoe::Engine::Pause();
    

    trans_ctx->cooperate = sandboxe_dt_trans_cooperate;
    trans_ctx->received = sandboxe_dt_trans_received;
    trans_ctx->handshake = sandboxe_dt_trans_handshake;
    trans_ctx->detached = sandboxe_dt_trans_detached;

    /* Attach debugger; this will fail with a fatal error here unless
     * debugger support is compiled in.  To fail more gracefully, call
     * this under a duk_safe_call() to catch the error.
     */
    duk_debugger_attach(
        ctx->GetCTX(),
        duk_trans_dvalue_read_cb,
        duk_trans_dvalue_write_cb,
        duk_trans_dvalue_peek_cb,
        duk_trans_dvalue_read_flush_cb,
        duk_trans_dvalue_write_flush_cb,
        NULL,  /* app request cb */
        duk_trans_dvalue_detached_cb,
        (void *) trans_ctx
    );
    
    while(Dynacoe::Engine::IsPaused()) {
        duk_debugger_cooperate(ctx->GetCTX());
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
    sandboxe_dt_trans_command__resume(trans_ctx);

}


void DTDebugger::StepInto() {
    if (!ctx_attached) return;
    // send request
    sandboxe_dt_trans_command__step_into(trans_ctx);
}

void DTDebugger::StepOver() {
    if (!ctx_attached) return;
    // send request
    sandboxe_dt_trans_command__step_over(trans_ctx);
}

void DTDebugger::StepOut() {
    if (!ctx_attached) return;
    // send request
    sandboxe_dt_trans_command__step_out(trans_ctx);
}

void DTDebugger::AddBreak(const std::string & filename, int line) {
    if (!ctx_attached) return;
    // send request
    sandboxe_dt_trans_command__add_break(trans_ctx, filename, line);
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
