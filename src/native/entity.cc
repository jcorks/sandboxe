#include <sandboxe/native/entity.h>


Sandboxe::EntityObjectID::EntityObjectID()  :
    Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::EntityIDT)
{
    id = Dynacoe::Entity::Create<Sandboxe::Entity>();
    id.IdentifyAs<Sandboxe::Entity>()->object = this;
}
