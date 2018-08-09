static Dynacoe::Entity::ID terminal;

class DTContext {
  public:
    const char * DT_SANDBOXE_OBJECT_STORE    = "__sandboxe_internal__heap";
    const char * DT_SANDBOXE_TYPE_STORE      = "__sandboxe_internal__type";

      
    DTContext() {
        source = duk_create_heap(NULL, NULL, NULL, NULL, fatal_error);

        
        terminal = Dynacoe::Entity::Create<Sandboxe::Script::Terminal>();
        duk_push_object(source);
        duk_put_global_string(source, DT_SANDBOXE_OBJECT_STORE);

        duk_push_object(source);
        duk_put_global_string(source, DT_SANDBOXE_TYPE_STORE);
        heapIndex = 1;
    }
    
    
    void InitializeGlobals() {
        auto natives = Sandboxe::Script::GatherNativeBindings();

        duk_push_global_object(source);
        TObject global(source);
        for(int i = 0; i < natives.size(); ++i) {
            global.SetFunction(natives[i].first, natives[i].second);
        }
    }
    
    void AddType(int typeID, 
        const std::vector<std::pair<std::string, Function>> & functions,
        const std::vector<std::pair<std::string, Primitive>> & properties,
        const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties) {
        
        int stackSize = duk_get_top(source);


        // get the type store object
        duk_push_global_object(source);
        duk_get_prop_string(source, -1, DT_SANDBOXE_TYPE_STORE);
        
 

        // add an empty object for that type
        duk_push_object(source);
        {
            TObject store(source);

            for(uint32_t i = 0; i < functions.size(); ++i) {
                store.SetFunction(functions[i].first, functions[i].second);
            }

            for(uint32_t i = 0; i < properties.size(); ++i) {
                store.Set(properties[i].first, properties[i].second);
            }
            
            for(uint32_t i = 0; i < nativeProperties.size(); ++i) {
                store.SetManagedProperty(nativeProperties[i].first, nativeProperties[i].second.first, nativeProperties[i].second.second);
            }            
        }
        duk_put_prop_index(source, -2, typeID);

        // later on can use duk_enum/duk_next to walk all these to copy for a new object
        duk_pop(source); // storage object
        duk_pop(source); // global

        assert(duk_get_top(source) == stackSize);

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
    
    
    // creates a new object of the given type in the heap store
    uint32_t CreateNewObject(int typeID, Object * parent) {
        int stackSize = duk_get_top(source);

        uint32_t out;
        if (dead.empty()) {
            out = heapIndex++;
        } else {
            out = dead.top();
            dead.pop();
        }


        // prepare an object that copies
        duk_push_global_object(source);                                         // global
        duk_get_prop_string(source, -1, DT_SANDBOXE_TYPE_STORE);                // global - store

        // get the type storage unit on the stack
        duk_get_prop_index(source, -2, typeID);                                 // global - store - typeBase

        // lets make sure we're working with a type here!
        if (!duk_is_object(source, -1)) {
            ThrowErrorObject("Internal error: type doesnt exist!");
            return 0;
        }
        
        
        // create new object
        duk_push_object(source);                                                // global - store - typeBase - {}
    
        {
            TObject newObject(source);
            newObject.MapPointer((void*)0x1, (void*)parent);
        }
    
    
        // now, copy all properties of  the type object into the new object...
        duk_enum(source, -2, DUK_ENUM_NO_PROXY_BEHAVIOR);                       // global - store - typeBase - {} - enum
        
        
        
        // enumerate with keys and values
        while(duk_next(source, -1, 1)) {                                        // global - store - typeBase - {} - enum - key - val
            duk_put_prop(source, -4); // copy the value key pair into the new object. This pops both the key and value
        }
        duk_pop(source); // enum                                                // global - store - typeBase - {}

        // now that the new object is made, lets place it in the heap at the new index
        duk_get_prop_string(source, -4, DT_SANDBOXE_OBJECT_STORE);              // global - store - typeBase - {} - heap
        duk_swap(source, -1, -2);                                               // global - store - typeBase - heap - {} 
        duk_put_prop_index(source, -2, heapIndex);                              // global - store - typeBase - heap
        
        
        duk_pop(source); // objectStore
        duk_pop(source); // base type object
        duk_pop(source); // object store 
        duk_pop(source); // global
        
        assert(duk_get_top(source) == stackSize);
        return heapIndex;
    }
 

    
  private:
    duk_context * source;
    std::stack<uint32_t> dead;
    uint32_t heapIndex;
      
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

