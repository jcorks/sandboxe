#include <sandboxe/native/entity.h>
#include <sandboxe/native/node.h>


void Sandboxe::Entity::SetObjectSource(Sandboxe::Script::Runtime::Object * obj) {
    object = obj;
    if (!realNode) {
        auto nodeObject = Sandboxe::NativeObject::New(NativeType::NodeT);
        //realNode = dynamic_cast<Sandboxe::Node*>(Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(nodeObject));
        auto fake = Sandboxe::NativeObject::Get<Sandboxe::ComponentAdaptor>(nodeObject);
        realNode = dynamic_cast<Sandboxe::Node*>(fake);
        AddComponent(fake->Native_GetDynacoeComponent());
        
        
    

    }

    
}



void Sandboxe::Entity::OnDraw() {


    object->CallMethod("onDraw");
}