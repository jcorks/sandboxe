#include <sandboxe/script/shell.h>
#include <sandboxe/script/runtime.h>
#include <Dynacoe/Library.h>



DynacoeEvent(console_script_router) {
    Dynacoe::Console::Info() << Sandboxe::Script::Runtime::Execute(args[0]) << "\n";
    return false;
}

void Sandboxe::Script::Shell::Initialize() {
    //Dynacoe::Console::SetCommandCallback(console_script_router);
    Dynacoe::Console::Clear();
}
