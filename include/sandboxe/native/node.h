#ifndef h_dynacoe_sandboxe_node_included
#define h_dynacoe_sandboxe_node_included


#include <sandboxe/native/component.h>



namespace Sandboxe {

class Node_Transform {
  public:
    Node_Transform(Sandboxe::Script::Runtime::Object * o) {
        object = o;
        auto positionO = NativeObject::New(NativeType::VectorT);
        auto scaleO = NativeObject::New(NativeType::VectorT);
        auto rotationO = NativeObject::New(NativeType::VectorT);
        
        position = Sandboxe::NativeObject::Get<Dynacoe::Vector>(positionO);
        scale = Sandboxe::NativeObject::Get<Dynacoe::Vector>(scaleO);
        rotation = Sandboxe::NativeObject::Get<Dynacoe::Vector>(rotationO);
        
        object->Set("position", positionO);
        object->Set("scale", scaleO);
        object->Set("rotation", rotationO);
        reverse = false;
    }
      
    Dynacoe::Vector * position;
    Dynacoe::Vector * scale;
    Dynacoe::Vector * rotation;
    Sandboxe::Script::Runtime::Object * object;
    bool reverse;
};


class Node : public Dynacoe::Node, public Sandboxe::ComponentAdaptor {
  public:
    
    Node(Sandboxe::Script::Runtime::Object * o) : Dynacoe::Node() {
        object = o;
        
        auto temp = Sandboxe::NativeObject::New(Sandboxe::NativeType::Node_TransformT);
        localTransform = Sandboxe::NativeObject::Get<Sandboxe::Node_Transform>(temp);        
        object->Set("local", localTransform->object);
        
        
        temp = Sandboxe::NativeObject::New(Sandboxe::NativeType::Node_TransformT);
        globalTransform = Sandboxe::NativeObject::Get<Sandboxe::Node_Transform>(temp);
        object->Set("global", globalTransform->object);
        
        SetObjectSource(o);

    }

    
    Sandboxe::Node_Transform * localTransform;
    Sandboxe::Node_Transform * globalTransform;
    Sandboxe::Script::Runtime::Object * object;

    

    void OnStep() {

        local.position = *localTransform->position;
        local.scale = *localTransform->scale;
        local.rotation = *localTransform->rotation;
        local.reverse = localTransform->reverse;
        
        Dynacoe::Node::OnStep();
    }
    
    
    void OnTransformUpdate() {
        *globalTransform->position = global.position;
        *globalTransform->scale = global.scale;
        *globalTransform->rotation = global.rotation;
        globalTransform->reverse = global.reverse;
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