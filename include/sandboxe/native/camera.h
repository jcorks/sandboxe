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
    }
    
    Dynacoe::Camera * Self() {
        return realCamera.IdentifyAs<Dynacoe::Camera>();
    }
    
    ~Camera() {
        realCamera.Identify()->Remove();
    }
    
    void OnStep() {
        auto i = realCamera.Identify();
        i->node.local.position = realNode->localTransform->position->vector;
        i->node.local.scale = realNode->localTransform->scale->vector;
        i->node.local.rotation = realNode->localTransform->rotation->vector;
        i->node.local.reverse = realNode->local.reverse;
        realCamera.Identify()->Step();
        object->CallMethod("onStep");
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