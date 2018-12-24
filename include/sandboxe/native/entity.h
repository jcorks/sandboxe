#ifndef sandboxe_entity_included_h
#define sandboxe_entity_included_h

#include <sandboxe/native/native.h>
#include <sandboxe/native/transform.h>



namespace Sandboxe {

enum ComponentType {
    COMPONENT_TYPE__COMPONENT,
    COMPONENT_TYPE__CLOCK,
    COMPONENT_TYPE__DATA_TABLE,
    COMPONENT_TYPE__GUI,
    COMPONENT_TYPE__MUTATOR,
    COMPONENT_TYPE__OBJECT2D,
    COMPONENT_TYPE__RENDERLIGHT,
    COMPONENT_TYPE__RENDERMESH,
    COMPONENT_TYPE__SCHEDULER,
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

        onStepObject    = nullptr;
        onDrawObject    = nullptr;
        onEnterObject   = nullptr;
        onDepartObject  = nullptr;
        onRemoveObject  = nullptr;
        onPreStepObject = nullptr;
        onPreDrawObject = nullptr;
    
    }    
    
    ~Entity() {
        delete transform;        
    }
    EntityObjectID * object;



    Sandboxe::Script::Runtime::Object * onStepObject;
    Sandboxe::Script::Runtime::Object * onDrawObject;
    Sandboxe::Script::Runtime::Object * onEnterObject;
    Sandboxe::Script::Runtime::Object * onDepartObject;
    Sandboxe::Script::Runtime::Object * onRemoveObject;
    Sandboxe::Script::Runtime::Object * onPreStepObject;
    Sandboxe::Script::Runtime::Object * onPreDrawObject;   

    void OnEnter() {
        if (onEnterObject) {
            onEnterObject->CallMethod();
        }
    }
    void OnDepart() {
        if (onDepartObject) {
            onDepartObject->CallMethod();
        }
    }
    void OnRemove() {
        if (onRemoveObject) {
            onRemoveObject->CallMethod();
        }
    }
    void OnPreStep() {
        if (onPreStepObject) {
            onPreStepObject->CallMethod();
        }
    }
    void OnStep() {
        if (onStepObject) {
            onStepObject->CallMethod();
        }
    }
    void OnPreDraw() {
        if (onPreDrawObject) {
            onPreDrawObject->CallMethod();
        }
    }
    void OnDraw(){
        if (onDrawObject) {
            onDrawObject->CallMethod();
        }
    }

};






}



#endif
