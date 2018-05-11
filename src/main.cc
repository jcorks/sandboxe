#include <Dynacoe/Library.h>
#include <sandboxe/trunk.h>
#include <sandboxe/script/runtime.h>
#include <sandboxe/script/garbageCollector.h>
#include <sandboxe/bindings/all.hpp>


std::string initialization_source = 
#include "sandboxe_initialization"
;

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
    {
        std::vector<uint8_t> initData(
            (uint8_t*)&initialization_source[0],
            ((uint8_t*)&initialization_source[0]) + initialization_source.size()
        );
        Sandboxe::Trunk::AddItem("sandboxe_initialization", initData);
    }
    
    Sandboxe::Script::Runtime::Load("sandboxe_initialization");
    Sandboxe::Script::Runtime::Load("main.js");



    Dynacoe::Engine::Run();

    return 0;

    
}