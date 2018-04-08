#include <sandboxe/native/entity.h>
#include <sandboxe/native/node.h>


void Sandboxe::Entity::SetObjectSource(Sandboxe::Script::Runtime::Object * obj) {
    object = obj;
    if (!realNode) {
        auto nodeObject = Sandboxe::NativeObject::New(NativeType::NodeT);
        realNode = dynamic_cast<Sandboxe::Node*>(Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(nodeObject));
        
        object->Set("node", nodeObject);
        AddComponent(realNode->Native_GetDynacoeComponent());
    }

    
}