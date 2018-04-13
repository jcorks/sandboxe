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
class ComponentAdaptor {
  public:
    
    // data is the function object
    // Generic event handler that calls non-native script object functions
    static DynacoeEvent(NativeHandler) {
        ((Sandboxe::Script::Runtime::Object*)functionData)->CallMethod(
            "", 
            {
                Script::Runtime::Primitive(dynamic_cast<Sandboxe::ComponentAdaptor*>(component)->GetObjectSource()),
                self.Valid() ? Script::Runtime::Primitive(self.IdentifyAs<Sandboxe::Entity>()->GetObjectSource()) : Script::Runtime::Primitive(),
                source.Valid() ? Script::Runtime::Primitive(source.IdentifyAs<Sandboxe::Entity>()->GetObjectSource()) : Script::Runtime::Primitive()
            }
        );
    }
    
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
    
    void SetObjectSource(Sandboxe::Script::Runtime::Object * o) {
        object = o;
    }
    
    Sandboxe::Script::Runtime::Object * GetObjectSource() {
        return object;
    }
    
    
    
  private: 
    Sandboxe::Script::Runtime::Object * object;
};


class Component : public Dynacoe::Component, public Sandboxe::ComponentAdaptor {
  public:
    

      
      

    ////////////////////////////////////
    /////////////// STANDARD IMPLEMENTATION 
      
    void Native_Draw() {
        Draw();
    }
      
    void Native_Step() {
        Step();
    }

    void Native_InstallEvent(const std::string & tag, Sandboxe::Script::Runtime::Object * fn) {
        GetObjectSource()->SetNonNativeReference(fn, nonNativeIndex++);
        InstallEvent(tag, NativeHandler, fn);
    }
    
    void Native_UninstallEvent(const std::string & tag) {
        UninstallEvent(tag);
    }
    
    
    void Native_EmitEvent(const std::string & evt, Dynacoe::Entity::ID id) {
        EmitEvent(evt, id);
    }


    bool Native_CanHandleEvent(const std::string & evt) {
        return CanHandleEvent(evt);
    }
    
    void Native_InstallHook(const std::string & name, Sandboxe::Script::Runtime::Object * fn) {
        GetObjectSource()->SetNonNativeReference(fn, nonNativeIndex++);
        InstallHook(name, NativeHandler, fn);
    }
    
    
    void Native_UninstallHook(const std::string & name) {
        UninstallHook(name, NativeHandler);
    }
    
    void Native_InstallHandler(const std::string & name, Sandboxe::Script::Runtime::Object * fn){
        GetObjectSource()->SetNonNativeReference(fn, nonNativeIndex++);
        InstallHandler(name, NativeHandler, fn);
    }
    
    void Native_UninstallHandler(const std::string & name){
        UninstallHandler(name, NativeHandler);
    }
    
    
    
    std::vector<std::string> Native_GetKnownEvents(){
        return GetKnownEvents();
    }
    
    std::string Native_GetTag() {
        return GetTag();
    }
    
    std::string Native_GetInfo() {
        return info;
    }
    
    void Native_SetInfo(const std::string & str) {
        info = str;
    }

    void Native_SetDraw(bool b) {
        draw = b;
    }
    bool Native_GetDraw(){
        return draw;
    }
    void Native_SetStep(bool b){
        step = b;
    }
    bool Native_GetStep(){
        return step;
    }
    Dynacoe::Entity::ID Native_GetHostID() {
        return GetHostID();
    }
    
    void OnStep() {
        GetObjectSource()->CallMethod("onStep");
    }

    void OnDraw() {
        GetObjectSource()->CallMethod("onDraw");
    }
    
    void OnAttach() {
        GetObjectSource()->CallMethod("onAttach");
    }
    
    void * Native_GetParentPtr() {
        return (void*)this;
    }
    
    Dynacoe::Component * Native_GetDynacoeComponent() {
        return dynamic_cast<Dynacoe::Component*>(this);
    }
    
    
    uint32_t nonNativeIndex;
    std::string info;
    
    //////////////////////////////////////////
    //////////////////////////////////////


      
      

      
    Component(const std::string & tag, const std::string & info_) :
        Dynacoe::Component(tag),
        info(info_),
        nonNativeIndex(0)
    {}
    

    

    
    


};
    
}


#endif