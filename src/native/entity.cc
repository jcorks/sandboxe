#include <sandboxe/native/entity.h>


Sandboxe::EntityObjectID::EntityObjectID(Sandboxe::NativeType t)  :
    Sandboxe::Script::Runtime::Object((int)t)
{
    id = Dynacoe::Entity::Create<Sandboxe::Entity>();
    id.IdentifyAs<Sandboxe::Entity>()->object = this;
}
