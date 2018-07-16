#ifndef h_component_sandboxe_included
#define h_component_sandboxe_included

#include <Dynacoe/Library.h>
#include <sandboxe/script/runtime.h>
#include <sandboxe/native/native.h>

/*
    Dynacoe::Component bindings 
    
    Notes:
        - EventHandlers in script do not take any additional arguments except 
          the component, self, and source objects.
          
        - InstallEvent() and UninstallEvent() are public.



 */



namespace Sandboxe {

// Base interface for components

class ComponentAdaptor : public Sandboxe::Script::Runtime::Object {
  public:
    // data is the function object
    // Generic event handler that calls non-native script object functions
    static DynacoeEvent(NativeHandler);
    ComponentAdaptor(int type) :
        Sandboxe::Script::Runtime::Object(type)
        {}
        
        
    virtual void Native_Draw(){}
    virtual void Native_Step(){}

    virtual void Native_InstallEvent(const std::string & tag, Sandboxe::Script::Runtime::Object * fn){}
    virtual void Native_UninstallEvent(const std::string & tag){}
    virtual void Native_EmitEvent(const std::string & evt, Dynacoe::Entity::ID id){}
    virtual bool Native_CanHandleEvent(const std::string &){return false;}
    virtual void Native_InstallHook(const std::string & name, Sandboxe::Script::Runtime::Object * fn){}
    virtual void Native_UninstallHook(const std::string & name){}
    virtual void Native_InstallHandler(const std::string & name, Sandboxe::Script::Runtime::Object * fn){}
    virtual void Native_UninstallHandler(const std::string & name){}
    virtual std::vector<std::string> Native_GetKnownEvents(){return{};}
    virtual std::string Native_GetTag(){return "";}
    virtual std::string Native_GetInfo(){return "";}
    virtual void Native_SetInfo(const std::string &){}
    virtual void Native_SetDraw(bool b){}
    virtual bool Native_GetDraw(){return false;}
    virtual void Native_SetStep(bool b){}
    virtual bool Native_GetStep(){return false;}
    
    virtual Dynacoe::Entity::ID Native_GetHostID() {return Dynacoe::Entity::ID();}
    virtual void * Native_GetParentPtr() {
        return nullptr;
    }
    
    virtual Dynacoe::Component * Native_GetDynacoeComponent() {
        return nullptr;
    }

};





class Component : public Dynacoe::Component, public Sandboxe::ComponentAdaptor {
  public:
    
    Component(const std::string & tag, const std::string & info_) :
      Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::ComponentT),
      Dynacoe::Component(tag),
      info(info_)
    {
        
    }
      
    std::string info;
    
    void OnGarbageCollection(){}
    const char * GetObjectName() const {return "Component";}

    #include "component_implementation"
      
    
};
}


#endif
