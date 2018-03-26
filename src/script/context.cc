#include <sandboxe/script/context.h>
#include <sandboxe/entity/terminal.h>
#include <sandboxe/script/shell.h>
#include <Dynacoe/Library.h>
#include <Dynacoe/RawData.h>
#include <v8.h>

using namespace Sandboxe::Script;


struct SandboxeContextModel {
    v8::Persistent<v8::Context> context;
    v8::Handle<v8::ObjectTemplate> sandboxeJS;
    
    Dynacoe::Entity::ID terminal;
    
};

static SandboxeContextModel * global = nullptr;


// loads a new script file
static v8::Handle<v8::Value> script_include(const v8::Arguments & args) {
    v8::HandleScope scopeMonitor;
    if (args.Length() != 1) {
        return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "Exactly one arg, dummy\n").ToString().c_str()));
    }
    
    
    v8::String::Utf8Value path(args[0]);
    Dynacoe::AssetID id = Dynacoe::Assets::Load("", *path);
    if (!id.Valid()) {
        return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "File " << *path << " could not be accessed.\n").ToString().c_str()));
    }
    
    // retrieve full string
    Dynacoe::RawData & data = Dynacoe::Assets::Get<Dynacoe::RawData>(id);
    char * rawStr = new char[data.GetSize()+1];
    rawStr[data.GetSize()] = 0;
    memcpy(rawStr, data.GetPtr(), data.GetSize());
    
    
    // execute the script
    Context::Execute(rawStr);
        //delete[] rawStr;
        //return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "File " << *path << " could not be accessed.\n").ToString().c_str()));
    
    delete[] rawStr;
    
    
    return v8::Undefined();
}



// reports exceptions 
static void script_exception_handler(v8::TryCatch * tcatch) {
    v8::HandleScope scopeMonitor;
    v8::String::Utf8Value exception(tcatch->Exception());


    Sandboxe::Script::Terminal * term = global->terminal.IdentifyAs<Sandboxe::Script::Terminal>();
    if (!term) return;


    const char * rawString = *exception;
    
    v8::Handle<v8::Message> detail = tcatch->Message();

    // no other info but the bassic message string
    if(detail.IsEmpty()) {
        term->ReportError(rawString);
        return;
    }
    

    Dynacoe::Chain message;

    
    // location first
    v8::String::Utf8Value filename(detail->GetScriptResourceName());
    int linenum = detail->GetLineNumber();
    
    
    // erroneous code
    message 
        << (const char*)*filename << ", line " << linenum << ": " << rawString << "\n"
        << (const char*)*v8::String::Utf8Value(detail->GetSourceLine()) << "\n"
    ;
    
    for(int i = 0; i < detail->GetStartColumn(); ++i)
        message << " ";
        
    for(int i = detail->GetStartColumn(); i < detail->GetEndColumn(); ++i) 
        message << "^";
    
    
    
    
    
    // erroneous code
    v8::String::Utf8Value st(tcatch->StackTrace());
    if (*st) {
        message << "\nCall Stack info:\n" << (const char*)*st << "\n";
    }   
    term->ReportError(message.ToString().c_str());

}




#include "../bindings/all.hpp"

void Context::Initialize() {
    v8::HandleScope top;
    global = new SandboxeContextModel;
    global->terminal = Dynacoe::Entity::Create<Sandboxe::Script::Terminal>();
    
    global->sandboxeJS = v8::ObjectTemplate::New();
    // set base functions
    global->sandboxeJS->Set(v8::String::New("__script_include"), v8::FunctionTemplate::New(script_include)); 

    // include base bindings 
    Sandboxe::Script::BindAll(global->sandboxeJS);

    global->context = v8::Context::New(NULL, global->sandboxeJS);
    
    //assert(!global->context.IsEmpty());
    global->context->Enter();


    

    // innitialize dynacoe shell extension
    Sandboxe::Script::Shell::Initialize();
    
    

    // finally, load in base logic for sandboxe bindings
    Load("base.js");
    
    
}


std::string Context::Execute(const std::string & source, const std::string & name) {
    v8::HandleScope scopeMonitor;
    v8::TryCatch tcatch;
    v8::Handle<v8::String> sourceHandle = v8::String::New(source.c_str());
    v8::Handle<v8::String> nameHandle = v8::String::New(name.c_str());

    v8::Handle<v8::Script> script = v8::Script::Compile(sourceHandle, nameHandle);
    
    // compilation error
    if (script.IsEmpty()) {
        script_exception_handler(&tcatch);
        return "";
    }
    
    // runtime error
    v8::Handle<v8::Value> result = script->Run();
    if (result.IsEmpty()) {
        script_exception_handler(&tcatch);
        return "";
    }
    
    v8::String::Utf8Value resultStr(result);

    return std::string(*resultStr ? *resultStr : "<undefined>");
}

void Context::Load(const std::string & path) {
    //TODO: sanitize?
    Execute(Dynacoe::Chain() << "__script_include(\"" << path << "\");\n");
}


