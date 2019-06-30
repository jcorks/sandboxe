#include <sandboxe/script/duktape/runtime_dt_debug.h>
#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <duk_trans_dvalue.h>
#include <cassert>
#include <queue>
#ifdef SANDBOXE_DT_DEBUG

using namespace Sandboxe::Script::Runtime;


// support trans writes

static DTContext * ctx_attached = nullptr;
static duk_trans_dvalue_ctx * trans_ctx = nullptr;
static std::vector<std::string> messagesPending;
static DTDebugger * debugger = nullptr;
static bool paused = false;

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

static std::queue<DTCommand> lastCommand;



static void sandboxe_dt_trans_command__pause(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x12);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent pause request\n");

    lastCommand.push(DT_COMMAND__PAUSE);
}


static void sandboxe_dt_trans_command__resume(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x13);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent resume request\n");

    lastCommand.push(DT_COMMAND__RESUME);
    
}

static void sandboxe_dt_trans_command__get_call_stack(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x1c);  
    duk_trans_dvalue_send_eom(ctx);
    lastCommand.push(DT_COMMAND__GET_CALL_STACK);
    
}

 


static void sandboxe_dt_trans_command__step_into(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x14);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent step into request\n");
    lastCommand.push(DT_COMMAND__STEP_INTO);

}

static void sandboxe_dt_trans_command__step_over(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x15);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent step over request\n");
    lastCommand.push(DT_COMMAND__STEP_OVER);

}

static void sandboxe_dt_trans_command__step_out(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x16);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent step out request\n");
    lastCommand.push(DT_COMMAND__STEP_OUT);
}

static void sandboxe_dt_trans_command__add_break(duk_trans_dvalue_ctx * ctx, const std::string & filename, int line) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x18);  
    duk_trans_dvalue_send_string(ctx, filename.c_str());
    duk_trans_dvalue_send_integer(ctx, line);
    duk_trans_dvalue_send_eom(ctx);
    printf("sent add break request\n");

    lastCommand.push(DT_COMMAND__ADD_BREAK);
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
        std::vector<std::string> messages = messagesPending; messagesPending.clear();
        
        DTCommand command = DT_COMMAND__NONE;
        if (!lastCommand.empty()) {
            command = lastCommand.front();
            lastCommand.pop();
        }


        if (command == DT_COMMAND__INIT) {
            printf("Init response\n");
            sandboxe_dt_trans_command__resume(ctx);
        }


        // notify from debugger (status)
        if (messages[0] == "NFY") {
            if (messages[1] == "1") {
                if (messages[2] == "1" && paused == false) { // paused state
                    Dynacoe::Console::Show(true);
                    paused = true;
                    Dynacoe::Engine::Pause();
                    Dynacoe::Console::Info() << "Entered paused state @\n";
                    Dynacoe::Console::Info() << "->| -\t" <<
                        messages[4] << "()\t" <<
                        messages[3] << ":" << messages[5] << "\t" <<
                        "\n";

                } else if (messages[2] == "0" && paused == true) {
                    Dynacoe::Console::Show(false);
                    paused = false;
                    Dynacoe::Engine::Resume();
                    Dynacoe::Console::Info() << "Resuming execution\n";

                }
                


            }

    
        } else {


            switch(command) {
              case DT_COMMAND__ADD_BREAK:
                if (messages[0] == "ERR") {
                    Dynacoe::Console::Error() << "Could not add breakpoint! (" << messages[2] << "\n";
                } else {
                    Dynacoe::Console::Info() << "Added breakpoint " << messages[1] << "\n";
                }
                break;
              
              case DT_COMMAND__PAUSE:
                printf("Received pause response.\n"); fflush(stdout);


                break;
                
              case DT_COMMAND__RESUME:
                printf("Received resume response.\n"); fflush(stdout);
                break;
                
              case DT_COMMAND__GET_CALL_STACK:
                {
                    messages.erase(messages.begin()+0);
                    messages.erase(messages.begin()+(messages.size()-1));

                    for(size_t i = 0; i < messages.size()/4; ++i) {
                        std::string function = messages[i*4 + 1];
                        if (function == "undefined") function = "";                    
                        Dynacoe::Console::Info() <<
                            "  | " << i << "\t " <<
                            (function.empty() ? std::string("\t") : (function + "()\t")) <<

                            messages[i*4 + 0] << ":" <<
                            messages[i*4 + 2] << "\n";
                    }
                }
                break;

              default:
                //sandboxe_dt_trans_command__get_call_stack(ctx);
                printf("Received %d messages.\n", messages.size());
                fflush(stdout);
            }
        }
    
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


// TODO: be proper and make a separate class for each please thanks
class DTDebugger_ConsoleCommand : public Dynacoe::Interpreter::Command {
  public:
    DTCommand type;
    duk_trans_dvalue_ctx * ctx;
    DTDebugger_ConsoleCommand(duk_trans_dvalue_ctx * ctxin, DTCommand cmd) : type(cmd), ctx(ctxin) {};

    std::string operator()(const std::vector<std::string> & argvec) {
        switch(type) {
          case DT_COMMAND__RESUME:      sandboxe_dt_trans_command__resume(ctx); break;
          case DT_COMMAND__STEP_INTO:   sandboxe_dt_trans_command__step_into(ctx); break;
          case DT_COMMAND__STEP_OUT:    sandboxe_dt_trans_command__step_out(ctx); break;
          case DT_COMMAND__STEP_OVER:   sandboxe_dt_trans_command__step_over(ctx); break;
          case DT_COMMAND__GET_CALL_STACK:   sandboxe_dt_trans_command__get_call_stack(ctx); break;
          case DT_COMMAND__ADD_BREAK:   
            if (argvec.size() != 3) return Help();
            sandboxe_dt_trans_command__add_break(ctx, argvec[1], atoi(argvec[2].c_str())); break;

          default:;
        };
        return "";
    }

    /// \brief Function that contains text to be accessed when 
    /// requesting documentation on the command.
    std::string Help() const {
        switch(type) {
          case DT_COMMAND__RESUME:  return "Resumes execution";
          case DT_COMMAND__STEP_INTO:  return "Steps into the current function";
          case DT_COMMAND__STEP_OUT:  return "Steps out of the current function";
          case DT_COMMAND__STEP_OVER:  return "Steps over the current function";
          case DT_COMMAND__ADD_BREAK:  return "Adds a breakpoint. Format: `break [filename] [line number]`";
          case DT_COMMAND__GET_CALL_STACK:  return "Prints the callstack";

          default: return "ERROR!";
        }
    }
};

class DTDebugger_Updater : public Dynacoe::Entity {
  public:
    duk_context * ctx;
    void OnStep() {
        duk_debugger_cooperate(ctx);

    }
};
DTDebugger::DTDebugger(DTContext * context) {
    ctx = context;
    paused = false;
    trans_ctx = duk_trans_dvalue_init();
    ctx_attached = ctx;
    debugger = this;

    if (!trans_ctx) {
        return;
    }


    trans_ctx->cooperate = sandboxe_dt_trans_cooperate;
    trans_ctx->received = sandboxe_dt_trans_received;
    trans_ctx->handshake = sandboxe_dt_trans_handshake;
    trans_ctx->detached = sandboxe_dt_trans_detached;

    /* Attach debugger; this will fail with a fatal error here unless
     * debugger support is compiled in.  To fail more gracefully, call
     * this under a duk_safe_call() to catch the error.
     */
    lastCommand.push(DT_COMMAND__INIT);
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

    auto up = Dynacoe::Entity::CreateReference<DTDebugger_Updater>();
    up->ctx = ctx->GetCTX();

    Dynacoe::Engine::AttachManager(
        up->GetID(),
        false
    );
    duk_debugger_cooperate(ctx->GetCTX());



    Dynacoe::Console::AddCommand("c", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__RESUME));
    Dynacoe::Console::AddCommand("continue", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__RESUME));
    

    Dynacoe::Console::AddCommand("s", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__STEP_INTO));
    Dynacoe::Console::AddCommand("stepInto", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__STEP_INTO));

    Dynacoe::Console::AddCommand("n", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__STEP_OVER));
    Dynacoe::Console::AddCommand("next", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__STEP_OVER));

    Dynacoe::Console::AddCommand("o", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__STEP_OUT));
    Dynacoe::Console::AddCommand("out", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__STEP_OUT));

    Dynacoe::Console::AddCommand("b", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__ADD_BREAK));
    Dynacoe::Console::AddCommand("break", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__ADD_BREAK));

    Dynacoe::Console::AddCommand("bt", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__GET_CALL_STACK));
    Dynacoe::Console::AddCommand("backtrace", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__GET_CALL_STACK));
    
}

void DTDebugger::Pause() {
    sandboxe_dt_trans_command__pause(trans_ctx);
    while(!lastCommand.empty())
        duk_debugger_cooperate(ctx->GetCTX());
}


void DTDebugger::Resume() {
    // send request
    sandboxe_dt_trans_command__resume(trans_ctx);
    duk_debugger_cooperate(ctx->GetCTX());


}


void DTDebugger::StepInto() {
    // send request
    sandboxe_dt_trans_command__step_into(trans_ctx);
    duk_debugger_cooperate(ctx->GetCTX());

}

void DTDebugger::StepOver() {
    // send request
    sandboxe_dt_trans_command__step_over(trans_ctx);
    duk_debugger_cooperate(ctx->GetCTX());

}

void DTDebugger::StepOut() {
    // send request
    sandboxe_dt_trans_command__step_out(trans_ctx);
    duk_debugger_cooperate(ctx->GetCTX());
}

void DTDebugger::AddBreak(const std::string & filename, int line) {
    // send request
    sandboxe_dt_trans_command__add_break(trans_ctx, filename, line);
    //while(lastCommand)
    duk_debugger_cooperate(ctx->GetCTX());

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
