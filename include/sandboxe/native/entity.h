#ifndef sandboxe_entity_included_h
#define sandboxe_entity_included_h

#include <sandboxe/native/native.h>




namespace Sandboxe {
class Node;
class Entity : public Dynacoe::Entity {
  public:
// helpers 
      
    ~Entity() {
        auto components = GetComponents();
        for(uint32_t i = 0; i < components.size(); ++i) {
            delete(components[i]);
        }
    }
    
    Entity() {
        object = nullptr;
        RemoveComponent(&node);
        realNode = nullptr;
        

    }
    void SetObjectSource(Sandboxe::Script::Runtime::Object * obj);
    
    
    Sandboxe::Script::Runtime::Object * GetObjectSource() const {
        return object;
    }
    
    
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
    void OnDraw();

    Sandboxe::Node * realNode;

  private:
      
    Sandboxe::Script::Runtime::Object * object;
};
}


#endif