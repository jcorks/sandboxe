static Dynacoe::Entity::ID terminal;

class DTContext {
  public:


      
    DTContext() {
        source = duk_create_heap(NULL, NULL, NULL, NULL, fatal_error);
        auto natives = Sandboxe::Script::GatherNativeBindings();
        for(int i = 0; i < natives.size(); ++i) {
            int stackSize = duk_get_top(source);
            
            // prepare the c function to be called later. Also, associate the
            // function pointer with the data itself
            duk_push_c_function(source, global_invocation, DUK_VARARGS);
            duk_push_pointer(source, (void*)natives[i].second);
            duk_put_prop_string(source, -2, DUK_HIDDEN_SYMBOL("fn"));

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

    
  private:
    duk_context * source;
    static duk_ret_t global_invocation(duk_context * ctx) {
        return 0;
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

