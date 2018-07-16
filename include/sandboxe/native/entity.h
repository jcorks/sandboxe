#ifndef sandboxe_entity_included_h
#define sandboxe_entity_included_h

#include <sandboxe/native/native.h>
#include <sandboxe/native/node.h>



namespace Sandboxe {

class EntityObjectID : public Sandboxe::Script::Runtime::Object {
  public:
    EntityObjectID(Sandboxe::NativeType t = Sandboxe::NativeType::EntityIDT);
    Dynacoe::Entity::ID id;
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "Entity";
    }
    
    
    
};


class Entity : public Dynacoe::Entity {
  public:
    Entity() : Dynacoe::Entity(new Sandboxe::NodeObject()) {
        object = nullptr;
    }    
    
    ~Entity() {
        auto comps = GetComponents();
        for(uint32_t i = 0; i < comps.size(); ++i) {
            RemoveComponent(comps[i]);
        }
        
    }
    EntityObjectID * object;

    
    void OnEnter() {
        object->CallMethod("onEnter");
    }
    void OnDepart() {
        object->CallMethod("onDepart");
    }
    void OnRemove() {
        object->CallMethod("onRemove");
    }
    void OnPreStep() {
        object->CallMethod("onPreStep");
    }
    void OnStep() {
        object->CallMethod("onStep");
    }
    void OnPreDraw() {
        object->CallMethod("onPreDraw");
    }
    void OnDraw(){
        object->CallMethod("onDraw");
    }

};






}



#endif