#ifndef sandboxe_entity_included_h
#define sandboxe_entity_included_h

#include <sandboxe/native/native.h>
#include <sandboxe/native/transform.h>



namespace Sandboxe {

enum ComponentType {
    COMPONENT_TYPE__CLOCK,
    COMPONENT_TYPE__DATA_TABLE,
    COMPONENT_TYPE__GUI,
    COMPONENT_TYPE__MUTATOR,
    COMPONENT_TYPE__OBJECT2D,
    COMPONENT_TYPE__RENDERLIGHT,
    COMPONENT_TYPE__RENDERMESH,
    COMPONENT_TYPE__SCHEDULER,
    COMPONENT_TYPE__SEQUENCER,
    COMPONENT_TYPE__SHAPE2D,
    COMPONENT_TYPE__STATE_CONTROL,
    COMPONENT_TYPE__TEXT2D    
};


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
    TransformObject * transform;
    Entity() : Dynacoe::Entity() {
        object = nullptr;
        transform = new TransformObject;
        ReplaceTransform(&transform->transformReal);
    }    
    
    ~Entity() {
        auto comps = GetComponents();
        for(uint32_t i = 0; i < comps.size(); ++i) {
            RemoveComponent(comps[i]);
        }
        delete transform;
        
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