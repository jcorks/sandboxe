#include <sandboxe/native/entity.h>

DynacoeEvent(Sandboxe::ComponentAdaptor::NativeHandler) {
    auto selfRef = self.IdentifyAs<Sandboxe::Entity>();
    auto sourceRef = source.IdentifyAs<Sandboxe::Entity>();

    auto p = ((Sandboxe::Script::Runtime::Object*)functionData)->CallMethod(
      "", 
      {
          Script::Runtime::Primitive(dynamic_cast<Sandboxe::Script::Runtime::Object*>(component)),
          selfRef ? Script::Runtime::Primitive(selfRef->object) : Script::Runtime::Primitive(),
          sourceRef ? Script::Runtime::Primitive(sourceRef->object) : Script::Runtime::Primitive(),
      }
    ); 
    
    if (!p.IsDefined()) return true;
    return (bool)p;
}
