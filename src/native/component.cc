#include <sandboxe/native/entity.h>

DynacoeEvent(Sandboxe::ComponentAdaptor::NativeHandler) {
    EntityObjectID * selfRef = self.Valid() ? new EntityObjectID() : nullptr;
    EntityObjectID * sourceRef = source.Valid() ? new EntityObjectID() : nullptr;

    if (sourceRef) {sourceRef->id = source;}
    if (selfRef)   {selfRef->id   = self;}

    auto p = ((ComponentAdaptor*)functionData)->CallMethod(
      "", 
      {
          Script::Runtime::Primitive(dynamic_cast<Sandboxe::Script::Runtime::Object*>(component)),
          selfRef ? Script::Runtime::Primitive((Sandboxe::Script::Runtime::Object*)selfRef) : Script::Runtime::Primitive(),
          sourceRef ? Script::Runtime::Primitive((Sandboxe::Script::Runtime::Object*)sourceRef) : Script::Runtime::Primitive(),
      }
    ); 
    
    if (sourceRef) delete sourceRef;
    if (selfRef) delete selfRef;
    if (!p.IsDefined()) return true;
    reutrn (bool)p;
}
