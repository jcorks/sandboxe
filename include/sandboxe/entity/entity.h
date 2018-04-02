#ifndef sandboxe_entity_included_h
#define sandboxe_entity_included_h

namespace Sandboxe {
class Entity : public Dynacoe::Entity {
  public:
    void SetObjectSource(Sandboxe::Script::Runtime::Object * obj) {
        object = obj;
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
    void OnDraw() {
        object->CallMethod("onDraw");
    }


  private:
      
    Sandboxe::Script::Runtime::Object * object;
};
}


#endif