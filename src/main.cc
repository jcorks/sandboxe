#include <Dynacoe/Library.h>
#include <sandboxe/trunk.h>
#include <sandboxe/script/runtime.h>





int main(int argc, char ** argv) {
    Dynacoe::Engine::Startup();

    Sandboxe::Trunk::Initialize(argv[0]);

    Sandboxe::Script::Runtime::Initialize();
    





    Sandboxe::Script::Runtime::Start();

    Sandboxe::Script::Runtime::Load("main.js");
    Dynacoe::Engine::Run();
 
   return 0;

    
}
