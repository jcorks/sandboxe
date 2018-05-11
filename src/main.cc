#include <Dynacoe/Library.h>
#include <sandboxe/trunk.h>
#include <sandboxe/script/runtime.h>
#include <sandboxe/script/garbageCollector.h>
#include <sandboxe/bindings/all.hpp>



int main(int argc, char ** argv) {
    Dynacoe::Engine::Startup();

    Sandboxe::Trunk::Initialize(argv[0]);

    Sandboxe::Script::Runtime::Initialize(
        Sandboxe::Script::GatherNativeBindings()
    );
    
    // remainign logic initialization for bindings
    Sandboxe::Script::ApplyPostBindings();

    Dynacoe::Engine::AttachManager(Dynacoe::Entity::Create<Sandboxe::GarbageCollector>());

    // finally, load in base logic for sandboxe bindings
    Sandboxe::Script::Runtime::Load("base.js");



    Dynacoe::Engine::Run();

    return 0;

    
}