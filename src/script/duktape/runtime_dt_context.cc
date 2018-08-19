#include <sandboxe/script/duktape/runtime_dt_context.h>
#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <sandboxe/trunk.h>
#include <duktape.h> 
#include <sandboxe/entity/terminal.h>
#include <Dynacoe/Library.h>
#include <Dynacoe/RawData.h>

#include <cassert>

using namespace Sandboxe::Script::Runtime;


static Dynacoe::Entity::ID terminal;


const char * DT_SANDBOXE_OBJECT_STORE    = "__sandboxe_internal__heap";
const char * DT_SANDBOXE_TYPE_STORE      = "__sandboxe_internal__type";
DTContext * DTContext::global = nullptr;

static std::vector<std::vector<std::pair<std::string, std::pair<Function, Function>>>> managedProperties_types;
static std::set<std::string> includedScripts; 
void runtime_include_script(Object *, const std::vector<Primitive> & args, Context & context) {
    //v8::HandleScope scopeMonitor;
    if (args.size() < 1) {
        return ScriptError((Dynacoe::Chain() << "Exactly one arg, dummy\n").ToString());
    }
    
    // having a second argument is a flag for only including rather than running.
    bool pragmaOnce = false;
    if (args.size() == 2) {
        pragmaOnce = args[1];
    }
    
    std::string path = args[0];

    // if include_once, ignore additional include requests
    if (pragmaOnce && includedScripts.find(path) != includedScripts.end()) {
        return;
    }
    
    Dynacoe::AssetID id;
    if (Sandboxe::Trunk::ItemExists(path)) {
        //Dynacoe::Console::Info() << "Loading " << *path << " from trunk\n";
        id = Dynacoe::Assets::LoadFromBuffer(
            "", 
            path, 
            Sandboxe::Trunk::ItemGet(path)
        );    
    } else {
        id = Dynacoe::Assets::Load("", path, false);
    }
    if (!id.Valid()) {
        ScriptError((Dynacoe::Chain() << "File " << path << " could not be accessed.\n").ToString());
        return;
    }
    
    // retrieve full string
    Dynacoe::RawData & data = Dynacoe::Assets::Get<Dynacoe::RawData>(id);
    char * rawStr = new char[data.GetSize()+1];
    rawStr[data.GetSize()] = 0;
    memcpy(rawStr, data.GetPtr(), data.GetSize());
    
    includedScripts.insert(path);
    
    // execute the script
    Sandboxe::Script::Runtime::Execute(rawStr, path);
        //delete[] rawStr;
        //return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "File " << *path << " could not be accessed.\n").ToString().c_str()));
    

    
    delete[] rawStr;
    
    return;
}




  
DTContext::DTContext() {
    managedProperties_types.push_back({});
    global = this;
    source = duk_create_heap(NULL, NULL, NULL, NULL, fatal_error);

    
    terminal = Dynacoe::Entity::Create<Sandboxe::Script::Terminal>();
    duk_push_object(source);
    duk_put_global_string(source, DT_SANDBOXE_OBJECT_STORE);

    duk_push_object(source);
    duk_put_global_string(source, DT_SANDBOXE_TYPE_STORE);
    heapIndex = 1;

    
    // built-in stuff
    duk_push_global_object(source);
    TObject global(source);
        global.SetFunction("__script_include", runtime_include_script);
    duk_pop(source);
    

}

void DTContext::ApplyGlobalFunctions(const std::vector<std::pair<std::string, Runtime::Function>> & natives) {
    int stackSize = duk_get_top(source);

    duk_push_global_object(source);
    TObject global(source);
    for(int i = 0; i < natives.size(); ++i) {
        global.SetFunction(natives[i].first, natives[i].second);
    }
    duk_pop(source);
    assert(duk_get_top(source) == stackSize);
}


void DTContext::AddType(int typeID, 
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
        while(typeID >= managedProperties_types.size()) managedProperties_types.push_back({});
        managedProperties_types[typeID] = (nativeProperties);
    }
    duk_put_prop_index(source, -2, typeID);

    // later on can use duk_enum/duk_next to walk all these to copy for a new object
    duk_pop(source); // storage object
    duk_pop(source); // global

    assert(duk_get_top(source) == stackSize);

}

// executes ES code directly with the given context name
std::string DTContext::Execute(const std::string & code, const std::string & name) {
    int stackSize = duk_get_top(source);

    duk_push_string(source, code.c_str());
    duk_push_string(source, name.c_str());

    std::string out;
    if (duk_pcompile(source, 0)) {
        ProcessErrorObject();
    } else {
        if (duk_pcall(source, 0)) {
            ProcessErrorObject();
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
void DTContext::ThrowErrorObject(const std::string & err) {
    duk_push_error_object(source, DUK_ERR_ERROR, "%s", err.c_str());
    duk_throw(source);
}


static duk_ret_t object_finalizer(duk_context * source) {
    // the object SHOULD be the first on the stack
    TObject obj(source);
    Object * parent = (Object*)obj.GetMappedPointer((void*)0x1);
    assert(parent);
    delete parent;
    printf("Finlized %p\n", parent);
    return 0;
}



// creates a new object of the given type in the heap store
uint32_t DTContext::CreateHeapEntryFromObject(Object * parent) {
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
    duk_get_prop_index(source, -1, parent->GetTypeID());                                 // global - store - typeBase

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

    // we need to push its finalizer! the finalizer will provide the mechanism to cleanup 
    // our program heap references 
    duk_push_c_function(source, object_finalizer, 1);                       // global - store - typeBase - {} - finalizer 
    duk_set_finalizer(source, -2);                                          // global - store - typeBase - {}

    // now, copy all properties of  the type object into the new object...
    duk_enum(source, -2, DUK_ENUM_NO_PROXY_BEHAVIOR);                       // global - store - typeBase - {} - enum
    
    
    
    // enumerate with keys and values
    int enumStack = duk_get_top(source);
    while(duk_next(source, -1, 1)) {                                        // global - store - typeBase - {} - enum - key - val
        if (duk_get_top(source) - enumStack == 2) { // key/value pair successful
            duk_to_string(source, -2); // stringify the key ?
            duk_put_prop(source, -4); // copy the value key pair into the 
                                      //new object. This pops both the key and value
        }
        else 
            duk_pop(source);   // only the key was found, so skip
    }
    duk_pop(source); // enum                                                // global - store - typeBase - {}

    // dont forget!! we also have our managed properties that are not enumerable 
    // from their ES5 defineProperty attribute
    {
        auto nativeProperties = managedProperties_types[parent->GetTypeID()];
        TObject object (source);
        for(uint32_t i = 0; i < nativeProperties.size(); ++i) {
            object.SetManagedProperty(nativeProperties[i].first, nativeProperties[i].second.first, nativeProperties[i].second.second);
        }            
    }




    // now that the new object is made, lets place it in the heap at the new index
    duk_get_prop_string(source, -4, DT_SANDBOXE_OBJECT_STORE);              // global - store - typeBase - {} - heap
    duk_swap(source, -1, -2);                                               // global - store - typeBase - heap - {} 
    duk_put_prop_index(source, -2, out);                                   // global - store - typeBase - heap
    
    
    duk_pop(source); // objectStore
    duk_pop(source); // base type object
    duk_pop(source); // object store 
    duk_pop(source); // global
    
    assert(duk_get_top(source) == stackSize);
    return out;
}


uint32_t DTContext::CreateHeapEntryFromDTStack(Object * parent) {
    int stackSize = duk_get_top(source);

    uint32_t out;
    if (dead.empty()) {
        out = heapIndex++;
    } else {
        out = dead.top();
        dead.pop();
    }
                                                                            // {}

    // get the global since we will be putting it in our heap
    duk_push_global_object(source);                                         // {} - global


    // we need the target obejct on top though!
    duk_swap(source, -1, -2);                                               // global - {}


    {
        TObject newObject(source);
        newObject.MapPointer((void*)0x1, (void*)parent);
    }

    // we need to push its finalizer! the finalizer will provide the mechanism to cleanup 
    // our program heap references 
    duk_push_c_function(source, object_finalizer, 1);                       // global - {} - finalizer 
    duk_set_finalizer(source, -2);                                          // global - {}

    
    
    // now that the new object is here, lets place it in the heap at the new index as a copy
    duk_get_prop_string(source, -2, DT_SANDBOXE_OBJECT_STORE);              // global - {} - heap
    duk_swap(source, -1, -2);                                               // global - heap - {} 
    duk_put_prop_index(source, -2, out);                                    // global - heap
    
    
    duk_pop(source); // objectStore
    duk_pop(source); // global
    PushHeapEntryToDTTop(out);
    
    assert(duk_get_top(source) == stackSize);
    return out;
}

void DTContext::PushHeapEntryToDTTop(uint32_t i) {
    if (i == 0 || i >= heapIndex) return;
    // get the global object heap
    duk_push_global_object(source);                                         // global
    duk_get_prop_string(source, -1, DT_SANDBOXE_OBJECT_STORE);              // global - heap
    duk_get_prop_index(source, -1, i);                                      // global - heap - {}
    duk_swap(source, -3, -1);                                               // {} - heap - global
    duk_pop(source); // global
    duk_pop(source); // heap
    
}


void DTContext::RemoveHeapEntry(uint32_t i) {
    if (i == 0 || i >= heapIndex) return;
    int stackSize = duk_get_top(source);
    // get the global object heap
    duk_push_global_object(source);                                         // global
    duk_get_prop_string(source, -1, DT_SANDBOXE_OBJECT_STORE);              // global - heap

    duk_push_null(source);                                                  // global - heap - null
    duk_put_prop_index(source, -2, i);                                      // global - heap 

    duk_pop(source); // heap
    duk_pop(source); // global
    
    dead.push(i);

    assert(duk_get_top(source) == stackSize);

}





  
void DTContext::fatal_error(void * data, const char * msg) {
    Sandboxe::Script::Terminal * term = terminal.IdentifyAs<Sandboxe::Script::Terminal>();
    term->ReportError(msg);

}

void DTContext::ProcessErrorObject() {
    auto win = Dynacoe::ViewManager::Get(Dynacoe::ViewManager::GetCurrent());
    if (!win) {
        Dynacoe::Console::Info() << "**Note**: A display was automatically created and shown to display the scripting error.\n";
        Dynacoe::ViewManager::NewMain("sandboxe");
    }

    //Dynacoe::Console::Show(true);
    
    TObject errObj(source);        
    std::string name = errObj.Get("name");    
    std::string message = errObj.Get("message");    
    std::string fileName = errObj.Get("fileName");    
    std::string lineNumber = errObj.Get("lineNumber");    
    std::string stack = errObj.Get("stack");    

    std::string msg = 
        std::string("@") + name + " from:   " + fileName + ", line " + lineNumber + ". Detail:\n\n";


    Dynacoe::Chain filter;
    filter = stack.c_str();
    filter.SetDelimiters("\r\n");
    while(filter.LinksLeft()) {
        std::string line = filter.GetLink();
        filter.NextLink();        


        // remove useless engine-internal stack references
        if (line.find(".c:") != std::string::npos) {
            continue;
        } 

        if (line.find(".cc:") != std::string::npos) {
            continue;
        } 

        if (line.find("native strict preventsyield") != std::string::npos) {
            continue;
        } 


        // remove unneeded keywords
        size_t p;
        while((p = line.find("preventsyield")) != std::string::npos) {
            line.replace(p, strlen("preventsyield"), "");
        }

        while((p = line.find("internal")) != std::string::npos) {
            line.replace(p, strlen("internal"), "");
        }
        msg += line + "\n";
    }
    
    
    

    Sandboxe::Script::Terminal * term = terminal.IdentifyAs<Sandboxe::Script::Terminal>();
    term->ReportError(msg);

    duk_pop(source);
    
    
}






















static void PrintKeys() {
    duk_context * source = DTContext::Get()->GetCTX();
    int stackSz = (duk_get_top(source));

    duk_enum(source, -1, DUK_ENUM_NO_PROXY_BEHAVIOR);  
    // enumerate with keys and values
    int enumStack = duk_get_top(source);
    while(duk_next(source, -1, 0)) {                                
        printf("%s, ", duk_to_string(source, -1));
        duk_pop(source); 
    }
    printf("\n");
    fflush(stdout);
    duk_pop(source); // enum 
    assert(stackSz == duk_get_top(source));
}


static void PrintIndex(uint32_t index) {
    duk_context * source = DTContext::Get()->GetCTX();

    duk_get_prop_index(source, -1, index);
    printf("%s\n", duk_safe_to_string(source, -1));
    duk_pop(source);
}

static void Execute(const char * str) {
    printf("%s\n", DTContext::Get()->Execute(str, "").c_str());
}




