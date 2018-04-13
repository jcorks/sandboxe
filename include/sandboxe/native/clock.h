#ifndef h_dynacoe_sandboxe_clock_included
#define h_dynacoe_sandboxe_clock_included


#include <sandboxe/native/component.h>



namespace Sandboxe {




class Clock : public Dynacoe::Clock, public Sandboxe::ComponentAdaptor {
  public:
    
    Clock(Sandboxe::Script::Runtime::Object * o) : Dynacoe::Clock(), nonNativeIndex(0) {
        SetObjectSource(o);

    }

    
    

    
    
    
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
        return GetInfo();
    }
    
    void Native_SetInfo(const std::string & str) {
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
    
    
    
};
    
    

    
}


#endif