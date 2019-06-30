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
static int level = 0;

static std::unordered_map<std::string, std::vector<std::string>> registeredFiles;

struct StackFrame {
    std::string function;
    int line;
    std::string file;
};
static std::vector<StackFrame> callstack;
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
    DT_COMMAND__EVAL,
    
    // special symbolic commands. Doesnt require a round trip with the debugger 
    DT_COMMAND__SYMBOLIC_UP,
    DT_COMMAND__SYMBOLIC_DOWN

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
    Dynacoe::Console::Lock(true);
}

static void sandboxe_dt_trans_command__step_over(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x15);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent step over request\n");
    lastCommand.push(DT_COMMAND__STEP_OVER);
    Dynacoe::Console::Lock(true);


}

static void sandboxe_dt_trans_command__step_out(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x16);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent step out request\n");
    lastCommand.push(DT_COMMAND__STEP_OUT);
    Dynacoe::Console::Lock(true);

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


static void sandboxe_dt_trans_command__eval(duk_trans_dvalue_ctx * ctx, const std::string & eval, int callstackLevel) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x1e);  
    duk_trans_dvalue_send_integer(ctx, callstackLevel);
    duk_trans_dvalue_send_string(ctx, eval.c_str());
    duk_trans_dvalue_send_eom(ctx);
    printf("sent eval request\n");

    lastCommand.push(DT_COMMAND__EVAL);
}



static void sandboxe_dt_trans_received(duk_trans_dvalue_ctx * ctx, duk_dvalue * dv) {
    static std::vector<char> bufferSrc;
    int len = std::max((int)(dv->len+1), DUK_DVALUE_TOSTRING_BUFLEN+1);
    if (bufferSrc.size() <= len) bufferSrc.resize(len);
    duk_dvalue_to_string(dv, &bufferSrc[0]);
    printf("dvalue received: %s\n", &bufferSrc[0]);
    messagesPending.push_back(&bufferSrc[0]);
    fflush(stdout);
}

static std::string sandboxe_get_stackframe_string(const StackFrame & frame, int stackIndex) {
    std::string out;
    std::string stackIndexStr = stackIndex < 0 ? Dynacoe::Chain("") : Dynacoe::Chain() << stackIndex;
    if (frame.function == "" && frame.file == "undefined") {
        out = Dynacoe::Chain() << "| " << stackIndexStr  << "\t " << "<internal call>";
        
    } else {
        out = Dynacoe::Chain() << "| " << stackIndexStr << "\t " << frame.function << "()\t" << frame.file << ":" << frame.line;
    }
    return out;
}

static std::string sandboxe_get_stackframe_level_string(int level) {
    if (level >= callstack.size()) return "";
    return sandboxe_get_stackframe_string(callstack[level], level);
}

static std::string sandboxe_get_nearby_lines(std::string & filename, int targetLine) {
    targetLine-=1; // convert from line number to a line index
    std::vector<std::string> & lines = registeredFiles[filename];
    if (lines.size() == 0) {
        return "  |...........................\n  |....(No lines available)...\n  |...........................";
    }
    
    if (targetLine < 0 || targetLine >= lines.size()) {
        return "  |...........................\n  |....(Line mismatch?).......\n  |...........................";        
    }
    
    std::string out;
    const int range = 3;
    for(int i = targetLine - range; i <= targetLine + range; ++i) {
        if (i < 0 || i >= lines.size()) {
            out+="  |...........................\n";
        } else {
            if (i == targetLine) {
                out += "->| " + lines[i] + "\n";                
            } else {
                out += "  | " + lines[i] + "\n";
            }
        }
    }

    return out;
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
                sandboxe_dt_trans_command__get_call_stack(ctx);
                if (messages[2] == "1" && paused == false) { // paused state
                    Dynacoe::Console::Show(true);
                    if (Dynacoe::Console::IsLocked()) {
                        Dynacoe::Console::Lock(false);
                    } else {
                        Dynacoe::Console::Info() << "Entered paused state\n";   
                    }
                    paused = true;
                    
                    
                    StackFrame frame;
                    frame.function = messages[4];
                    frame.file = messages[3];
                    frame.line = atoi(messages[5].c_str());
                    Dynacoe::Console::Info() << sandboxe_get_stackframe_string(frame, -1) << "\n\n";
                    Dynacoe::Console::Info() << sandboxe_get_nearby_lines(frame.file, frame.line) << "\n";

                    
                } else if (messages[2] == "0" && paused == true) { // resume
                    if (!Dynacoe::Console::IsLocked()) {
                        Dynacoe::Console::Info() << "Entered resume state\n";
                    }
                    Dynacoe::Console::Show(false);
                    paused = false;
                    
                    // likely from the step-oriented commands
                    Dynacoe::Console::Lock(false);

                }
                


            }

    
        } else {


            switch(command) {
              case DT_COMMAND__ADD_BREAK:
                if (messages[0] == "ERR") {
                    Dynacoe::Console::Error() << "Could not add breakpoint! (" << messages[2] << "\n\n";
                } else {
                    Dynacoe::Console::Info() << "Added breakpoint " << messages[1] << "\n";
                }
                break;
              
              case DT_COMMAND__PAUSE:
                printf("Received pause response.\n"); fflush(stdout);
                level = 0;



                break;
                
              case DT_COMMAND__RESUME:
                printf("Received resume response.\n"); fflush(stdout);
                Dynacoe::Console::Info() << "Resuming execution\n";
                level = 0;

                break;
                
              case DT_COMMAND__EVAL:
                if (messages[1] == "0") {
                    Dynacoe::Console::Info() << messages[2] << "\n";
                } else {
                    Dynacoe::Console::Info() << "Error evaluating expresssion:\n" + messages[2];                    
                }
                break;
              case DT_COMMAND__STEP_INTO:
              case DT_COMMAND__STEP_OUT:
              case DT_COMMAND__STEP_OVER:
                level = 0;
                printf("Processed-step action\n");
                break;
              
              case DT_COMMAND__GET_CALL_STACK:
                {
                    messages.erase(messages.begin()+0);
                    messages.erase(messages.begin()+(messages.size()-1));

                    callstack.clear();

                    StackFrame frame;
                    for(size_t i = 0; i < messages.size()/4; ++i) {
                        frame.function = messages[i*4+1];
                        frame.line = atoi(messages[i*4+2].c_str());
                        frame.file = messages[i*4 + 0];
                        
                        callstack.push_back(frame);
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
          case DT_COMMAND__GET_CALL_STACK:
        
            for(int i = 0; i < callstack.size(); ++i) {
                Dynacoe::Console::Info() << (i == level ? "->" : "  ") << sandboxe_get_stackframe_level_string(i) << "\n";
            }
            break;
          case DT_COMMAND__EVAL:        
            if (argvec.size() > 1) {
                std::string expression;
                for(int i = 1; i < argvec.size(); ++i) {
                    expression += argvec[i] + " ";
                }
                sandboxe_dt_trans_command__eval(ctx, expression, (level+1) * -1);
            }
            break;
          case DT_COMMAND__ADD_BREAK:   
            if (argvec.size() != 3) return Help();
            sandboxe_dt_trans_command__add_break(ctx, argvec[1], atoi(argvec[2].c_str())); break;

          case DT_COMMAND__SYMBOLIC_UP:
            level++;
            if (level >= ((int)callstack.size())) level = ((int)callstack.size())-1;
            Dynacoe::Console::Info() << sandboxe_get_stackframe_level_string(level) << "\n\n";
            {
                StackFrame & frame = callstack[level];
                Dynacoe::Console::Info() << sandboxe_get_nearby_lines(frame.file, frame.line) << "\n";
            }
            break;

          case DT_COMMAND__SYMBOLIC_DOWN:
            level--;
            if (level < 0) level = 0;
            Dynacoe::Console::Info() << sandboxe_get_stackframe_level_string(level) << "\n\n";
            {
                StackFrame & frame = callstack[level];
                Dynacoe::Console::Info() << sandboxe_get_nearby_lines(frame.file, frame.line) << "\n";
            }

            break;


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
          case DT_COMMAND__ADD_BREAK:  return "Adds a breakpoint. Format: `break [filename] [line number]` OR `break [line number]` to break in the current inspection context.";
          case DT_COMMAND__EVAL:  return "Prints an expression. Format: `print [expression]`";
          case DT_COMMAND__GET_CALL_STACK:  return "Prints the callstack";
          case DT_COMMAND__SYMBOLIC_UP: return "Puts the printing context in the call above";
          case DT_COMMAND__SYMBOLIC_DOWN: return "Puts the printing context in the call below";
          
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

    Dynacoe::Console::AddCommand("p", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL));
    Dynacoe::Console::AddCommand("print", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL));

    Dynacoe::Console::AddCommand("up", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__SYMBOLIC_UP));
    Dynacoe::Console::AddCommand("down", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__SYMBOLIC_DOWN));

    
}






static bool getNext(const char ** ptr, std::string & str) {
    const char * in = *ptr;
    if (!*in) return false;

    if (*in == '\n') {
        (*ptr)++;
        return true;
    }
    
    if (*in && (*in == '\r' && *in == '\n')) {
        (*ptr)+=2;
        return true;
    }

    str += *in;
    
    (*ptr)++; in = *ptr;

    
    return false;
}

void DTDebugger::RegisterFile(const std::string & name, const std::string & code) {
    std::vector<std::string> & lines = registeredFiles[name];
    std::string line;
    lines.clear();
    
    const char * ptr = code.c_str();
    while(*ptr) {
        if (getNext(&ptr, line)) {
            lines.push_back(line);
            line = "";
        }
    }
    
    printf("Registered %s (%d lines)\n", name.c_str(), (int)lines.size());
    
}


#endif
