#ifndef h_sandboxe_script_garbage_collector_included
#define h_sandboxe_script_garbage_collector_included
namespace Sandboxe {
class GarbageCollector : public Dynacoe::Entity {
  public:
    Dynacoe::Clock * clock;

    static DynacoeEvent(GarbageTime) {
        Sandboxe::GarbageCollector * gc = self.IdentifyAs<Sandboxe::GarbageCollector>();
        Sandboxe::Script::Runtime::PerformGarbageCollection();
        gc->clock->Reset();
        return false;
    }
    
    GarbageCollector() {
        clock = AddComponent<Dynacoe::Clock>();
        clock->Set(300);
        clock->InstallHook("clock-expire", GarbageTime);
        
    }
    
    
    void OnStep() {
        Sandboxe::Script::Runtime::CheckAndHandleErrors();

    }
};
}

#endif
