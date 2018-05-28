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
    Entity() {
        RemoveComponent(&node);
        realNode = new Sandboxe::NodeObject();
        //realNode = dynamic_cast<Sandboxe::Node*>(Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(nodeObject));
        AddComponent(realNode);
        object = nullptr;
        node.local.scale = Dynacoe::Vector(0, 0, 0);
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

    Sandboxe::NodeObject * realNode;
};






}



#endif