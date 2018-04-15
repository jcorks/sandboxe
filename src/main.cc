#include <Dynacoe/Library.h>
#include <sandboxe/script/runtime.h>
#include <sandboxe/script/garbageCollector.h>
#include <sandboxe/bindings/all.hpp>



int main() {
    Dynacoe::Engine::Startup();

    Dynacoe::ViewManager::NewMain("sandboxe");

    Sandboxe::Script::Runtime::Initialize(
        Sandboxe::Script::GatherNativeBindings()
    );
    
    // finally, load in base logic for sandboxe bindings
    Sandboxe::Script::Runtime::Load("base.js");

    Dynacoe::Engine::AttachManager(Dynacoe::Entity::Create<Sandboxe::GarbageCollector>());

    Dynacoe::Engine::Run();

    return 0;

    
}