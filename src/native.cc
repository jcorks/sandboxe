#include <sandboxe/script/runtime.h>
#include <sandboxe/native/native.h>


#include <sandboxe/native/entity.h>
#include <sandboxe/native/component.h>
#include <sandboxe/native/vector.h>

#include <cassert>

using namespace Sandboxe;




Sandboxe::Script::Runtime::Object * NativeObject::New(NativeType type, const std::vector<Sandboxe::Script::Runtime::Primitive> & args) {
    Sandboxe::Script::Runtime::Object * object = new Sandboxe::Script::Runtime::Object(NativeTypeToString(type));
    void * v = nullptr;
    switch(type) {
      case NativeType::EntityIDT: {
        Dynacoe::Entity::ID id = Dynacoe::Entity::Create<Sandboxe::Entity>(); // todo: replace with special draw/run/mapped
        Sandboxe::Entity * e = id.IdentifyAs<Sandboxe::Entity>();
        e->SetObjectSource(object);
        v = (void*)id.Value();
        break;
      } 
      
      case NativeType::ComponentT: {
          assert(args.size() >= 2);
          Sandboxe::Component * component = new Sandboxe::Component(args[0], args[1]);
          component->SetObjectSource(object);
          v = (void*) component;
          break;
      }


      case NativeType::VectorT: {
          v = (void*) new Dynacoe::Vector();
          break;
      }
      
      case NativeType::Node_TransformT: {
          v = (void*) new Dynacoe::Node::Transform();
          break;
      }


    }
    
    object->SetNativeAddress((void*)v);
    object->SetNativeAddress((void*)type, 1);
    return object;
}



const char * NativeTypeToString(NativeType type) {
  switch(type) {
    case NativeType::EntityIDT: return "Entity";
    case NativeType::ComponentT: return "Component";
    case NativeType::VectorT: return "Vector";
    case NativeType::Node_TransformT: return "Node::Transform";
    default: return "Unknown";
  }        
}

NativeType NativeObject::Type(const Sandboxe::Script::Runtime::Object * object) {
    return (NativeType)(uint64_t)object->GetNativeAddress(1);
}


