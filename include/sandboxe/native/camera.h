#ifndef h_sandboxe_camera_included
#define h_sandboxe_camera_included

#include <sandboxe/native/entity.h>


namespace Sandboxe {

class Camera : public Sandboxe::Entity {
  public:
    Dynacoe::Entity::ID realCamera;
    Camera() {
        realCamera = Dynacoe::Entity::Create<Dynacoe::Camera>();
        realCamera.Identify()->SetName(GetID().String());
        onStepObject_Camera = nullptr;
    }
    
    Dynacoe::Camera * Self() {
        return realCamera.IdentifyAs<Dynacoe::Camera>();
    }
    
    ~Camera() {
        realCamera.Identify()->Remove();
    }

    Sandboxe::Script::Runtime::Object * onStepObject_Camera;
    
    void OnStep() {
        auto i = realCamera.Identify();
        i->Node().Position() = Node().GetPosition();
        i->Node().Scale() = Node().GetScale();
        i->Node().Rotation() = Node().GetRotation();
        realCamera.Identify()->Step();
        if (onStepObject_Camera) {
            onStepObject_Camera->CallMethod();
        }
    }
};
    
    
class CameraEntityID : public Sandboxe::EntityObjectID {
  public: 
    CameraEntityID() : EntityObjectID(Sandboxe::NativeType::Camera_EntityIDT) {
        id.Identify()->Remove();
        id = Dynacoe::Entity::Create<Sandboxe::Camera>();
        id.IdentifyAs<Sandboxe::Camera>()->object = this;

    }
    

    

    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "Camera";
    }
    
    
};

}

#endif
