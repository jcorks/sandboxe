#include <sandboxe/script/runtime.h>
#include <sandboxe/native/native.h>


#include <sandboxe/native/entity.h>
#include <sandboxe/native/component.h>
#include <sandboxe/native/vector.h>
#include <sandboxe/native/node.h>
#include <sandboxe/native/buttonListener.h>
#include <sandboxe/native/assetID.h>
#include <sandboxe/native/shape2d.h>

#include <sandboxe/native/byteArray.h>
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
          v = (void*) dynamic_cast<Sandboxe::ComponentAdaptor*>(component);
          break;
      }


      case NativeType::VectorT: {
          v = (void*) new Dynacoe::Vector();
          break;
      }
      
      case NativeType::Node_TransformT: {
          v = (void*) new Sandboxe::Node_Transform(object);
          break;
      }
      
      case NativeType::NodeT: {
          auto ref = new Sandboxe::Node(object);
          v = (void*) dynamic_cast<Sandboxe::ComponentAdaptor*>(ref);
          break;
      }

      case NativeType::ButtonListenerT: {
          auto ref = new Sandboxe::ButtonListener(object);
          v = (void*) ref;
          break;
      }
      
      case NativeType::AssetIDT: {
          auto ref = new Sandboxe::AssetID(object);
          v = (void*) ref;
          break;
      }
      
      case NativeType::ByteArrayT: {
          auto ref = new Sandboxe::ByteArray(object);
          v = (void*) ref;
          break;
      }
    
    
      case NativeType::ColorT: {
        v = (void*) new Dynacoe::Color();
        break;
      }
      
      case NativeType::Shape2DT: {
          auto ref = new Sandboxe::Shape2D(object);
          v = (void*) dynamic_cast<Sandboxe::ComponentAdaptor*>(ref);
        break;
      }

    }
    
    object->SetNativeAddress((void*)v);
    object->SetNativeAddress((void*)type, 1);
    return object;
}



const char * Sandboxe::NativeTypeToString(NativeType type) {
  switch(type) {
    case NativeType::EntityIDT: return "Entity";
    case NativeType::ComponentT: return "Component";
    case NativeType::VectorT: return "Vector";
    case NativeType::Node_TransformT: return "Node::Transform";
    case NativeType::NodeT: return "Node";
    case NativeType::ButtonListenerT: return "ButtonListener";
    case NativeType::AssetIDT: return "AssetID";
    case NativeType::ByteArrayT: return "ByteArray";
    case NativeType::ColorT: return "Color";
    case NativeType::Shape2DT: return "Shape2D";

    default: return "Unknown";
  }        
}

NativeType NativeObject::Type(const Sandboxe::Script::Runtime::Object * object) {
    return (NativeType)(uint64_t)object->GetNativeAddress(1);
}


