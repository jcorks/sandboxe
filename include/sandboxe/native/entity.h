#ifndef sandboxe_entity_included_h
#define sandboxe_entity_included_h

#include <sandboxe/native/native.h>
#include <sandboxe/native/node.h>



namespace Sandboxe {

class EntityObjectID : public Sandboxe::Script::Runtime::Object {
  public:
    EntityObjectID();
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


EntityObjectID::EntityObjectID()  :
    Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::EntityIDT)
{
    id = Dynacoe::Entity::Create<Sandboxe::Entity>();
    id.IdentifyAs<Sandboxe::Entity>()->object = this;
}




}



#endif