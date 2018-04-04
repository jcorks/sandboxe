#ifndef h_component_sandboxe_included
#define h_component_sandboxe_included

#include <Dynacoe/Library.h>
#include <sandboxe/script/runtime.h>


/*
    Dynacoe::Component bindings 
    
    Notes:
        - EventHandlers in script do not take any additional arguments except 
          the component, self, and source objects.
          
        - InstallEvent() and UninstallEvent() are public.



 */



namespace Sandboxe {
class Component : public Dynacoe::Component {
  public:
    
      // data is the function object
      // Generic event handler that calls non-native script object functions
      static DynacoeEvent(NativeHandler) {
          ((Sandboxe::Script::Runtime::Object*)functionData)->CallMethod(
              "", 
              {
                  Script::Runtime::Primitive(((Sandboxe::Component*)component)->GetObjectSource()),
                  self.Valid() ? Script::Runtime::Primitive(self.IdentifyAs<Sandboxe::Entity>()->GetObjectSource()) : Script::Runtime::Primitive(),
                  source.Valid() ? Script::Runtime::Primitive(source.IdentifyAs<Sandboxe::Entity>()->GetObjectSource()) : Script::Runtime::Primitive()
              }
          );
      }
      
      
      
    
    // publicly exposes InstallEvent()
    void InstallEvent_Sandboxe(const std::string & name, Sandboxe::Script::Runtime::Object * fn) {
        object->SetNonNativeReference(fn, nonNativeIndex++);
        InstallEvent(name, NativeHandler, fn);
    }
    
    void UninstallEvent_Sandboxe(const std::string & name) {
        UninstallEvent(name);
    }
      
    // publicly exposes InstallEvent()
    void InstallHook_Sandboxe(const std::string & name, Sandboxe::Script::Runtime::Object * fn) {
        object->SetNonNativeReference(fn, nonNativeIndex++);
        InstallHook(name, NativeHandler, fn);
    }
    
    void InstallHandler_Sandboxe(const std::string & name, Sandboxe::Script::Runtime::Object * fn) {
        object->SetNonNativeReference(fn, nonNativeIndex++);
        InstallHandler(name, NativeHandler, fn);
    }
      
    Component(const std::string & tag, const std::string & info_) :
        Dynacoe::Component(tag),
        info(info_),
        nonNativeIndex(0)
    {}
    
    ~Component() {
        delete object;
    }
    
    void SetObjectSource(Sandboxe::Script::Runtime::Object * o) {
        object = o;
    }
    
    Sandboxe::Script::Runtime::Object * GetObjectSource() {
        return object;
    }
    
    

    void OnStep() {
        object->CallMethod("onStep");
    }

    void OnDraw() {
        object->CallMethod("onDraw");
    }
    
    void OnAttach() {
        object->CallMethod("onAttach");
    }
    
    std::string GetInfo() {return info;}
    
  private:
    Sandboxe::Script::Runtime::Object * object;
    // returned result for GetInfo();
    std::string info;
    uint32_t nonNativeIndex;
};
    
}


#endif