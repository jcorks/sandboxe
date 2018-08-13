#include <sandboxe/script/runtime.h>
#include <sandboxe/script/shell.h>
#include <Dynacoe/Library.h>
#include <Dynacoe/RawData.h>
#include <sandboxe/trunk.h>
#include <stack>
#include <cassert>
#include <sandboxe/bindings/all.hpp>
#include <map>
#include <duktape.h> 
 

 
using Sandboxe::Script::Runtime::Function;
using Sandboxe::Script::Runtime::Primitive;
using Sandboxe::Script::Runtime::Context;

#include <sandboxe/script/duktape/runtime_dt_context.h>
#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <sandboxe/script/duktape/runtime_dt_object.h>
using Sandboxe::Script::Runtime::DTContext; 
using Sandboxe::Script::Runtime::TObject; 
using Sandboxe::Script::Runtime::Object; 
using Sandboxe::Script::Runtime::Object_Internal; 



std::string initialization_source = 
#include "../../sandboxe_initialization.js"
;
#include <sandboxe/script/garbageCollector.h>



void Sandboxe::Script::Runtime::Initialize() {
    new DTContext(); 
    DTContext::Get()->ApplyGlobalFunctions(Sandboxe::Script::GatherNativeBindings());
}  

void Sandboxe::Script::Runtime::Start() {
    // innitialize dynacoe shell extension
    Sandboxe::Script::Shell::Initialize();
       

    Sandboxe::Script::ApplyPostBindings();
    

    Dynacoe::Engine::AttachManager(Dynacoe::Entity::Create<Sandboxe::GarbageCollector>());

    // finally, load in base logic for sandboxe bindings
    {
        std::vector<uint8_t> initData(
            (uint8_t*)&initialization_source[0],
            ((uint8_t*)&initialization_source[0]) + initialization_source.size()
        );
        Sandboxe::Trunk::AddItem("sandboxe_initialization", initData);
    }
    
    Sandboxe::Script::Runtime::Load("sandboxe_initialization");
    Dynacoe::Console::OverlayMessageMode(Dynacoe::Console::MessageMode::Disabled);
    Dynacoe::Console::Info() 
        << "                         ____                  \n"
        << "   _________ _____  ____/ / /_  ____  _  _____ \n"
        << "  / ___/ __ `/ __ \\/ __  / __ \\/ __ \\| |/_/ _ \\\n"
        << " (__  ) /_/ / / / / /_/ / /_/ / /_/ />  </  __/\n"
        << "/____/\\__,_/_/ /_/\\__,_/_.___/\\____/_/|_|\\___/ \n"
        << "Johnathan Corkery, 2018 (coebeef.net/sandboxe)\n\n"
        << "Backend status:\n\n";

    Dynacoe::Console::OverlayMessageMode(Dynacoe::Console::MessageMode::Standard);




      
    
    Sandboxe::Script::Runtime::Load("main.js");
    
    Dynacoe::ViewManager::NewMain("temp");
    Dynacoe::Engine::Run();
}


std::string Sandboxe::Script::Runtime::Execute(const std::string & code, const std::string & name) {
    return DTContext::Get()->Execute(code, name);
}
  


void Sandboxe::Script::Runtime::Load(const std::string & path) {
    //TODO: sanitize?
    Execute(Dynacoe::Chain() << "__script_include(\"" << path << "\");\n");
}

void Sandboxe::Script::Runtime::ScriptError(const std::string & str) {
    DTContext::Get()->ThrowErrorObject(str); 
}

void Sandboxe::Script::Runtime::PerformGarbageCollection() {
    //??
}

void Sandboxe::Script::Runtime::CheckAndHandleErrors() {
    //
}


void Sandboxe::Script::Runtime::AddType  (int typeID,
               const std::vector<std::pair<std::string, Function>> & functions,
               const std::vector<std::pair<std::string, Primitive>> & properties,
               const std::vector<std::pair<std::string, std::pair<Function, Function>>> & nativeProperties) {
   DTContext::Get()->AddType(typeID, functions, properties, nativeProperties);
}








Object::Object(int typeID) {
    data = new Object_Internal(typeID, this);    
    data->AssignHeapEntry();
}

Object::~Object() {
    delete data;
} 

Object::Object(Object_Internal & n) {
    // pass ownership, internal only
    data = &n;
}


Primitive Object::Get(const std::string & name) {
    return data->Get(name);
}


void Object::Set(const std::string & name, const Primitive & value) {
    data->Set(name, value);
}


Primitive Object::CallMethod(const std::string & name, const std::vector<Primitive> & args) {
    return data->CallMethod(name, args);
}


bool Object::IsNative() const {
    return data->GetTypeID() > 0;
}


int Object::GetTypeID() const {
    return data->GetTypeID();
}


uint32_t Object::AddNonNativeReference(Object * ref) {
    return data->AddNonNativeReference(ref);
}


void Object::UpdateNonNativeReference(Object * ref, uint32_t index) {
    data->UpdateNonNativeReference(ref, index);

}


Object * Object::GetNonNativeReference(uint32_t index) const {
    return data->GetNonNativeReference(index);
}





