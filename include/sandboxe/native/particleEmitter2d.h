#ifndef h_sandboxe_particle_emitter_2d_included
#define h_sandboxe_particle_emitter_2d_included

#include <sandboxe/native/entity.h>


namespace Sandboxe {

class ParticleEmitter2D : public Sandboxe::Entity {
  public:
    Dynacoe::Entity::ID realEmitter;
    ParticleEmitter2D() {
        realEmitter = Dynacoe::Entity::Create<Dynacoe::ParticleEmitter2D>();
        realEmitter.Identify()->SetName(GetID().String());
        localFiltered = true;
        localTransluscent = true;

    }
    
    Dynacoe::ParticleEmitter2D * Self() {
        return realEmitter.IdentifyAs<Dynacoe::ParticleEmitter2D>();
    }
    
    ~ParticleEmitter2D() {
        realEmitter.Identify()->Remove();
    }
    
    void OnStep() {
        auto i = realEmitter.Identify();
        i->node.local.position = realNode->localTransform->position->vector;
        i->node.local.scale = realNode->localTransform->scale->vector;
        i->node.local.rotation = realNode->localTransform->rotation->vector;
        i->node.local.reverse = realNode->local.reverse;
        realEmitter.Identify()->Step();
        object->CallMethod("onStep");
    }
    
    bool localFiltered;
    bool localTransluscent;

};
    
    
class ParticleEmitter2DEntityID : public Sandboxe::EntityObjectID {
  public: 
    ParticleEmitter2DEntityID() : EntityObjectID(Sandboxe::NativeType::ParticleEmitter2D_EntityIDT) {
        id.Identify()->Remove();
        id = Dynacoe::Entity::Create<Sandboxe::ParticleEmitter2D>();
        id.IdentifyAs<Sandboxe::ParticleEmitter2D>()->object = this;

    }
    

    

    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "ParticleEmitter2D";
    }
    
    
};

}

#endif