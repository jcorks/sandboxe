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


static std::vector<std::string> errors;
static std::vector<std::string> newErrors;


void DTDebugger::ReportError(const std::string & str) {
    errors.push_back(str);
    newErrors.push_back(str);
}

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
    DT_COMMAND__EVAL_KEYS,
    DT_COMMAND__EVAL_ARR,
    DT_COMMAND__LIST_BREAKPOINTS,
    DT_COMMAND__DELETE_BREAKPOINT,
    
    // special symbolic commands. Doesnt require a round trip with the debugger 
    DT_COMMAND__SYMBOLIC_UP,
    DT_COMMAND__SYMBOLIC_DOWN,
    DT_COMMAND__SYMBOLIC_LIST_ERRORS,


};

static std::queue<DTCommand> lastCommand;

class DelayedSwitch : public Dynacoe::Entity {
  public:
    Dynacoe::Clock * clock;
    
    static DynacoeEvent(timesup) {
        Dynacoe::Console::Show(false);
        return false;
    }
    
    DelayedSwitch() {
        clock = AddComponent<Dynacoe::Clock>();
        clock->InstallHook("clock-expire", timesup);
    }
    void Start(float ms) {
        clock->Set(ms);
        clock->Reset();
        clock->Resume();
    }   
    
    void Cancel() {
        clock->Pause();
    }
};
static DelayedSwitch * timeoutConsoleOff = nullptr;

static void sandboxe_dt_reset_console() {
    Dynacoe::Console::Clear();
    Dynacoe::Console::Info(Dynacoe::Color("#9AB8D7"))
    << "                         ____                  \n"
    << "   _________ _____  ____/ / /_  ____  _  _____ \n"
    << "  / ___/ __ `/ __ \\/ __  / __ \\/ __ \\| |/_/ _ \\\n"
    << " (__  ) /_/ / / / / /_/ / /_/ / /_/ />  </  __/\n"
    << "/____/\\__,_/_/ /_/\\__,_/_.___/\\____/_/|_|\\___/ \n";
    

    Dynacoe::Console::Info(Dynacoe::Color("#60B48A"))
    << "Johnathan Corkery, 2019 (jcorks.github.io/sandboxe)\n\n"
    << "DEBUG MODE\n\n";
}

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
    //Dynacoe::Console::Lock(true);
}

static void sandboxe_dt_trans_command__step_over(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x15);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent step over request\n");
    lastCommand.push(DT_COMMAND__STEP_OVER);
    //Dynacoe::Console::Lock(true);


}

static void sandboxe_dt_trans_command__step_out(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x16);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent step out request\n");
    lastCommand.push(DT_COMMAND__STEP_OUT);
    //Dynacoe::Console::Lock(true);

}

static void sandboxe_dt_trans_command__list_breakpoints(duk_trans_dvalue_ctx * ctx) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x17);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent breakpoint list request\n");
    lastCommand.push(DT_COMMAND__LIST_BREAKPOINTS);

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

static void sandboxe_dt_trans_command__delete_breakpoint(duk_trans_dvalue_ctx * ctx, int index) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x19);  
    duk_trans_dvalue_send_integer(ctx, index);  
    duk_trans_dvalue_send_eom(ctx);
    printf("sent breakpoint delete request\n");
    lastCommand.push(DT_COMMAND__DELETE_BREAKPOINT);

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

static void sandboxe_dt_trans_command__eval_keys(duk_trans_dvalue_ctx * ctx, const std::string & eval, int callstackLevel) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x1e);  
    duk_trans_dvalue_send_integer(ctx, callstackLevel);
    duk_trans_dvalue_send_string(ctx, 
        std::string(std::string()+"(function(){var __out=''; var __arr = Object.keys("+eval+"); __out+='Object has '+__arr.length+' keys: '; for(var i = 0; i < __arr.length; ++i) {__out+='' + __arr[i] + ', ';}return __out})()").c_str()
    );
    duk_trans_dvalue_send_eom(ctx);
    printf("sent eval-keys request\n");

    lastCommand.push(DT_COMMAND__EVAL_KEYS);
}


static void sandboxe_dt_trans_command__eval_array(duk_trans_dvalue_ctx * ctx, const std::string & eval, int callstackLevel) {
    duk_trans_dvalue_send_req(ctx);
    duk_trans_dvalue_send_integer(ctx, 0x1e);  
    duk_trans_dvalue_send_integer(ctx, callstackLevel);
    duk_trans_dvalue_send_string(ctx, 
        std::string(std::string()+"(function(){var __out=''; var __arr = ("+eval+"); __out+='Array has '+__arr.length+' objects: '; for(var i = 0; i < __arr.length; ++i) {__out+='' + __arr[i] + ', ';}return __out})()").c_str()
    );
    duk_trans_dvalue_send_eom(ctx);
    printf("sent eval-array request\n");

    lastCommand.push(DT_COMMAND__EVAL_ARR);
}



static void sandboxe_dt_trans_received(duk_trans_dvalue_ctx * ctx, duk_dvalue * dv) {
    static std::vector<char> bufferSrc;
    int len = std::max((int)(dv->len+1), DUK_DVALUE_TOSTRING_BUFLEN+1);
    if (bufferSrc.size() <= len) bufferSrc.resize(len);
    duk_dvalue_to_string(dv, &bufferSrc[0]);
    //printf("dvalue received: %s\n", &bufferSrc[0]);
    messagesPending.push_back(&bufferSrc[0]);
    fflush(stdout);
}

static std::string sandboxe_get_stackframe_string(const StackFrame & frame, int stackIndex) {
    std::string out;
    std::string stackIndexStr =Dynacoe::Chain() << stackIndex;
    std::string functionName = frame.function;
    if (functionName == "") {
        functionName = "<anonymous>";
    }
    if (frame.function == "" && frame.file == "undefined") {
        out = Dynacoe::Chain() << "[level " << stackIndexStr  << "]\t " << "<internal call>";
        
    } else {
        out = Dynacoe::Chain() << "[level " << stackIndexStr << "]\t " << functionName << "()\t" << frame.file << ":" << frame.line;
    }
    return out;
}

static std::string sandboxe_get_stackframe_level_string(int level) {
    if (level >= callstack.size()) return "";
    return sandboxe_get_stackframe_string(callstack[level], level);
}

static std::string sandboxe_get_nearby_lines(const std::string & filename, int targetLine, std::string & before, std::string & after) {
    targetLine-=1; // convert from line number to a line index
    std::vector<std::string> & lines = registeredFiles[filename];

    // max 5 columns for line number 
    char line[6];

    if (lines.size() == 0) {
        return "  |...........................\n  |....(No lines available)...\n  |...........................\n";
    }
    
    if (targetLine < 0 || targetLine >= lines.size()+1) { // allow exceeding one line
        return "  |...........................\n  |....(Line mismatch?).......\n  |...........................\n";        
    }
    
    std::string current;
    std::string * out = &before;

    const int range = 8;
    for(int i = targetLine - range; i <= targetLine + range; ++i) {
        line[0] = 0;
        if (i < targetLine) {
            out = &before;
        } else if (i == targetLine) {
            out = &current;
        } else {
            out = &after;
        }

        
        
        if (i+1 > 0 && i+1 <= lines.size()) {
            snprintf(line, 6, "%-5d", i+1); 
            *out+=std::string(line);
        } else {
            *out+="     ";
        }
        if (i < 0 || i >= lines.size()) {
            *out += "\n";//*out+="  |...........................\n";
        } else {
            if (i == targetLine) {
                *out += "->| " + lines[i] + "\n";                
            } else {
                *out += "  | " + lines[i] + "\n";
            }
        }
    }

    return current;
}


static void sandboxe_dt_print_context(const StackFrame & frame, int level) {
    sandboxe_dt_reset_console();                        
    Dynacoe::Console::Info("#DFAF8F") << sandboxe_get_stackframe_string(frame, level) << "\n\n";
        
    std::string before;
    std::string current;
    std::string after;
    current = sandboxe_get_nearby_lines(frame.file, frame.line, before, after);
    Dynacoe::Console::Info("#807F5F") << before;
    Dynacoe::Console::Info("#F0DFAF") << current;
    Dynacoe::Console::Info("#807F5F") << after;

    if (newErrors.size()) {
        Dynacoe::Console::Info("#ff1111") << 
            "\n\nThe following NEW errors have been detected:\n\n";
        for(uint32_t i = 0; i < newErrors.size(); ++i) {
            Dynacoe::Console::Info("#ff6666") << Dynacoe::Chain() <<
                "Error #" << i << ":\n" << newErrors[i] << "\n\n";
        }
        if (newErrors.size() != errors.size()) {
            Dynacoe::Console::Info("#ff1111") << 
                "\n\n(run the command `errors` to list all encountered errors (" << errors.size() << " total)\n\n";            
        }
        newErrors.clear();
    }
    
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
            return;
        }


        // notify from debugger (status)
        if (messages[0] == "NFY") {
            if (messages[1] == "1") {
                sandboxe_dt_trans_command__get_call_stack(ctx);
                if (messages[2] == "1" && paused == false) { // paused state
                    //timeoutConsoleOff->Cancel();
                    if (!Dynacoe::Console::IsVisible()) {
                        Dynacoe::Console::Show(true);
                        Dynacoe::Console::Info() << "Debugger entered paused state\n";   
                    } else {
                        sandboxe_dt_reset_console();   
                        Dynacoe::Console::Info() << "\n";                           
                    }
                    paused = true;
                    
                    
                    StackFrame frame;
                    frame.function = messages[4];
                    frame.file = messages[3];
                    frame.line = atoi(messages[5].c_str());
                    sandboxe_dt_print_context(frame, 0);

                } else if (messages[2] == "0" && paused == true) { // resume
                    if (Dynacoe::Console::IsVisible()) {
                        Dynacoe::Console::Info() << "Resuming state...\n";
                        Dynacoe::Console::Show(false);

                    }
                    //timeoutConsoleOff->Start(500);

                    paused = false;
                    
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
                    Dynacoe::Console::Info() << "Error evaluating expresssion:\n" + messages[2] + "\n";                    
                }
                break;
              case DT_COMMAND__EVAL_KEYS:
                if (messages[1] == "0") {
                    Dynacoe::Console::Info() << messages[2] << "\n";
                } else {
                    Dynacoe::Console::Info() << "Error printing object keys.\n";                    
                }
                break;

              case DT_COMMAND__EVAL_ARR:
                if (messages[1] == "0") {
                    Dynacoe::Console::Info() << messages[2] << "\n";
                } else {
                    Dynacoe::Console::Info() << "Error printing array.\n";                    
                }
                break;

              case DT_COMMAND__STEP_INTO:
              case DT_COMMAND__STEP_OUT:
              case DT_COMMAND__STEP_OVER:
                level = 0;
                printf("Processed-step action\n");
                break;
                
              case DT_COMMAND__LIST_BREAKPOINTS:
                messages.erase(messages.begin()+0);
                if (messages.size()/2) {
                    Dynacoe::Console::Info() << "List of breakpoints:\n";
                    for(size_t i = 0; i < messages.size()/2; ++i) {
                        Dynacoe::Console::Info() << "[Breakpoint " << i << "] " << messages[2*i] << ":" << messages[2*i+1] << "\n";
                    }
                } else {
                    Dynacoe::Console::Info() << "No currently active breakpoints.\n";                    
                }
                break;
                
              case DT_COMMAND__DELETE_BREAKPOINT:
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
    static DTCommand lastCommand;
    static std::vector<std::string> lastInputs;
    DTCommand type;
    duk_trans_dvalue_ctx * ctx;
    DTDebugger_ConsoleCommand(duk_trans_dvalue_ctx * ctxin, DTCommand cmd) : type(cmd), ctx(ctxin) {};

    std::string operator()(const std::vector<std::string> & argvec) {
        lastCommand = type;
        lastInputs = argvec;
        switch(type) {
          case DT_COMMAND__RESUME:      sandboxe_dt_trans_command__resume(ctx); break;
          case DT_COMMAND__STEP_INTO:   sandboxe_dt_trans_command__step_into(ctx); break;
          case DT_COMMAND__STEP_OUT:    sandboxe_dt_trans_command__step_out(ctx); break;
          case DT_COMMAND__STEP_OVER:   sandboxe_dt_trans_command__step_over(ctx); break;
          case DT_COMMAND__LIST_BREAKPOINTS: sandboxe_dt_trans_command__list_breakpoints(ctx); break;
          case DT_COMMAND__DELETE_BREAKPOINT: 
            if (argvec.size() < 2) return Help();
            sandboxe_dt_trans_command__delete_breakpoint(ctx, atoi(argvec[1].c_str())); break;
            break;
          case DT_COMMAND__GET_CALL_STACK:
            if (callstack.size() == 0) {
                Dynacoe::Console::Info(Dynacoe::Color("#DFAF8F")) << "[Callstack empty or unknown.]\n";
                break;

            }
            for(int i = 0; i < callstack.size(); ++i) {
                Dynacoe::Console::Info(Dynacoe::Color("#DFAF8F")) << (i == level ? "-> " : "   ") << sandboxe_get_stackframe_level_string(i) << "\n";
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
          case DT_COMMAND__EVAL_KEYS:        
            if (argvec.size() > 1) {
                std::string expression;
                for(int i = 1; i < argvec.size(); ++i) {
                    expression += argvec[i] + " ";
                }
                sandboxe_dt_trans_command__eval_keys(ctx, expression, (level+1) * -1);
            }
            break;
          case DT_COMMAND__EVAL_ARR:        
            if (argvec.size() > 1) {
                std::string expression;
                for(int i = 1; i < argvec.size(); ++i) {
                    expression += argvec[i] + " ";
                }
                sandboxe_dt_trans_command__eval_array(ctx, expression, (level+1) * -1);
            }
            break;
          case DT_COMMAND__ADD_BREAK:
            if (argvec.size() == 2) {
                int line = atoi(argvec[1].c_str());
                // single number: line within the current file
                if (line > 0) {
                    sandboxe_dt_trans_command__add_break(
                        ctx,
                        callstack[level].file,
                        line
                    );
                } else {
                    Dynacoe::Chain com;
                    com = argvec[1];
                    com.SetDelimiters(":");
                    std::string filename = com.GetLink(); com++;
                    std::string line = com.GetLink();

                    int lineReal = atoi(line.c_str());
                    if (lineReal > 0) {

                        sandboxe_dt_trans_command__add_break(
                            ctx,
                            filename,
                            atoi(line.c_str())
                        );      
                    } else {
                        return Help();
                    }
                }
            } else if (argvec.size() == 1) {
                sandboxe_dt_trans_command__add_break(
                    ctx,
                    callstack[level].file,
                    callstack[level].line
                ); 
            } else {
                if (argvec.size() != 3) return Help();
                sandboxe_dt_trans_command__add_break(ctx, argvec[1], atoi(argvec[2].c_str()));
            }
            break;

          case DT_COMMAND__SYMBOLIC_UP:
            level++;
            if (level >= ((int)callstack.size())) level = ((int)callstack.size())-1;
            Dynacoe::Console::Info("#DFAF8F") << sandboxe_get_stackframe_level_string(level) << "\n\n";
            {
                StackFrame & frame = callstack[level];
                sandboxe_dt_print_context(frame, level);
            }
            break;

          case DT_COMMAND__SYMBOLIC_DOWN:
            level--;
            if (level < 0) level = 0;
            Dynacoe::Console::Info("#DFAF8F") << sandboxe_get_stackframe_level_string(level) << "\n\n";
            {
                StackFrame & frame = callstack[level];
                sandboxe_dt_print_context(frame, level);
            }

            break;

          case DT_COMMAND__SYMBOLIC_LIST_ERRORS:
            Dynacoe::Console::Info("#ff1111") << 
                "\n\nThe following runtime errors have been logged:\n\n";
            for(uint32_t i = 0; i < errors.size(); ++i) {
                Dynacoe::Console::Info("#ff6666") << Dynacoe::Chain() <<
                    "Error #" << i << ":\n" << errors[i] << "\n\n";
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
          case DT_COMMAND__LIST_BREAKPOINTS: return "Lists all currently set breakpoints.";
          case DT_COMMAND__DELETE_BREAKPOINT: return "Deletes a breakpoint. Format: `delete [breakpoint index]`";
          case DT_COMMAND__EVAL:  return "Prints an expression. Format: `print [expression]`";
          case DT_COMMAND__EVAL_KEYS:  return "Prints an object's keys. Format: `print-keys [expression]`";
          case DT_COMMAND__EVAL_ARR:  return "Prints an array's contents. Format: `print-array [expression]`";
          case DT_COMMAND__GET_CALL_STACK:  return "Prints the callstack";
          case DT_COMMAND__SYMBOLIC_UP: return "Puts the printing context in the call above";
          case DT_COMMAND__SYMBOLIC_DOWN: return "Puts the printing context in the call below";
          case DT_COMMAND__SYMBOLIC_LIST_ERRORS: return "Lists all encountered runtime errors in order of occurrence";
          
          default: return "ERROR!";
        }
    }
};

DTCommand DTDebugger_ConsoleCommand::lastCommand = DT_COMMAND__NONE;
std::vector<std::string> DTDebugger_ConsoleCommand::lastInputs;


class DTDebugger_Updater : public Dynacoe::Entity {
  public:
    duk_context * ctx;
    void OnStep() {
        if (
            !Dynacoe::Console::IsVisible() &&

            (Dynacoe::Input::GetState(Dynacoe::Keyboard::Key_lctrl) || 
             Dynacoe::Input::GetState(Dynacoe::Keyboard::Key_rctrl))
            &&
            Dynacoe::Input::GetState(Dynacoe::Keyboard::Key_c)
            ) {
            sandboxe_dt_trans_command__pause(trans_ctx);
        }


        duk_debugger_cooperate(ctx);


    }
};


static DynacoeEvent(sandboxe_dt_repeat_handler) {
    if (args.size() == 0 || (args.size() && args[0] == "")) {
        printf("TEST\n");
        if (DTDebugger_ConsoleCommand::lastCommand != DT_COMMAND__NONE) {
            DTDebugger_ConsoleCommand last(trans_ctx, last.lastCommand);
            last(last.lastInputs);
        }
        return false;
    }
    return true;
}

DTDebugger::DTDebugger(DTContext * context) {
    ctx = context;
    paused = false;
    trans_ctx = duk_trans_dvalue_init();
    ctx_attached = ctx;
    debugger = this;

    if (!trans_ctx) {
        return;
    }
    Dynacoe::Console::SetCommandCallback(sandboxe_dt_repeat_handler);
    timeoutConsoleOff = Dynacoe::Entity::Create<DelayedSwitch>().IdentifyAs<DelayedSwitch>();
    Dynacoe::Engine::AttachManager(timeoutConsoleOff->GetID(), false);
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

    Dynacoe::Console::AddCommand("l", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__LIST_BREAKPOINTS));
    Dynacoe::Console::AddCommand("list", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__LIST_BREAKPOINTS));

    Dynacoe::Console::AddCommand("e", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__SYMBOLIC_LIST_ERRORS));
    Dynacoe::Console::AddCommand("errors", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__SYMBOLIC_LIST_ERRORS));


    Dynacoe::Console::AddCommand("bt", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__GET_CALL_STACK));
    Dynacoe::Console::AddCommand("backtrace", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__GET_CALL_STACK));

    Dynacoe::Console::AddCommand("d", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__DELETE_BREAKPOINT));
    Dynacoe::Console::AddCommand("delete", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__DELETE_BREAKPOINT));


    Dynacoe::Console::AddCommand("p", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL));
    Dynacoe::Console::AddCommand("print", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL));

    Dynacoe::Console::AddCommand("pk", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL_KEYS));
    Dynacoe::Console::AddCommand("print-keys", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL_KEYS));

    Dynacoe::Console::AddCommand("pa", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL_ARR));
    Dynacoe::Console::AddCommand("print-array", new DTDebugger_ConsoleCommand(trans_ctx, DT_COMMAND__EVAL_ARR));

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
