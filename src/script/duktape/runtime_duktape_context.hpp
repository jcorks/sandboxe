static Dynacoe::Entity::ID terminal;

class DTContext {
  public:


      
    DTContext() {
        source = duk_create_heap(NULL, NULL, NULL, NULL, fatal_error);
        auto natives = Sandboxe::Script::GatherNativeBindings();
        for(int i = 0; i < natives.size(); ++i) {
            int stackSize = duk_get_top(source);
            
            // prepare the c function to be called later. 
            duk_push_c_function(source, global_invocation, DUK_VARARGS);
            {
                // associate the function pointer with the data itself
                TObject func(source);
                func.MapPointer((void*)0x1, (void*)natives[i].second);

                printf("mapped %p to 0x1\n", func.GetMappedPointer((void*)0x1));

            }

            // add the function to the global object (func should be on the)
            duk_put_global_string(source, natives[i].first.c_str());
            
            assert(duk_get_top(source) == stackSize);
        }
        
        terminal = Dynacoe::Entity::Create<Sandboxe::Script::Terminal>();
        
    }
    
    void AddType(int typeID, 
        const std::vector<std::pair<std::string, Function>> & functions,
        const std::vector<std::pair<std::string, Primitive>> & properties,
        const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties) {
        
        
    }
    
    // executes ES code directly with the given context name
    std::string Execute(const std::string & code, const std::string & name) {
        int stackSize = duk_get_top(source);

        duk_push_string(source, code.c_str());
        duk_push_string(source, name.c_str());

        std::string out;
        if (duk_pcompile(source, 0)) {
            ScriptErrorMessage();
        } else {
            if (duk_pcall(source, 0)) {
                ScriptErrorMessage();
            } else {
                const char * result = duk_safe_to_string(source, -1);
                out = (result ? result : "<null>");
                duk_pop(source);
            }
        }
        
        
        assert(duk_get_top(source) == stackSize);
        return out;
    }


    // Generates the given error
    void ThrowErrorObject(const std::string & err) {
        duk_push_error_object(source, DUK_ERR_ERROR, "%s", err.c_str());
        duk_throw(source);
    }
 

    
  private:
    duk_context * source;
    static duk_ret_t global_invocation(duk_context * ctx) {
        int args = duk_get_top(ctx);
        std::vector<Primitive> argsConverted;
        for(uint32_t i = 0; i < args; ++i) {
            duk_dup(ctx, i);
            {
                TObject arg(ctx);
                argsConverted.push_back(arg.GetAsPrimitive());
            }
            duk_pop(ctx);

            Dynacoe::Console::Info() << "ARG" << i << ":" << argsConverted[i].Data() << "\n";
        }


        duk_push_current_function(ctx);
        Function f;
        {
            TObject thisFunction(ctx);
            f = (Function)thisFunction.GetMappedPointer((void*)0x1);
        }
        Sandboxe::Script::Runtime::Context context;
        f(nullptr, argsConverted, context);


        // TODO: need to handle arrays
        duk_push_string(ctx, context.GetReturnValue().Data().c_str());

        return 1;
    }
      
    static void fatal_error(void * data, const char * msg) {
        Sandboxe::Script::Terminal * term = terminal.IdentifyAs<Sandboxe::Script::Terminal>();
        term->ReportError(msg);

    }

    void ScriptErrorMessage() {
        TObject errObj(source);        
        std::string name = errObj.Get("name");    
        std::string message = errObj.Get("message");    
        std::string fileName = errObj.Get("fileName");    
        std::string lineNumber = errObj.Get("lineNumber");    
        std::string stack = errObj.Get("stack");    

               
        std::string msg = 
            std::string("@") + name + " from:   " + fileName + ", line " + lineNumber + ". Detail:\n\n" + stack;


        Sandboxe::Script::Terminal * term = terminal.IdentifyAs<Sandboxe::Script::Terminal>();
        term->ReportError(msg);

        duk_pop(source);
    }




};

