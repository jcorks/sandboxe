#include <Dynacoe/Library.h>
#include <sandboxe/script/context.h>

int main() {
    Dynacoe::Engine::Startup();

    Dynacoe::ViewManager::NewMain("sandboxe");
    Sandboxe::Script::Context::Initialize();
    
    Dynacoe::Engine::Run();

    return 0;

    
}