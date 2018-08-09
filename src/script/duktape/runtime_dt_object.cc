#include <sandboxe/script/runtime.h>
#include <sandboxe/script/duktape/runtime_dt_object.h>
#include <sandboxe/script/duktape/runtime_dt_context.h>

using namespace Sandboxe::Script::Runtime;


Object_Internal::Object_Internal(int typeID, Object * parent_) : parent(parent_) {
    type = typeID;
    heapIndex =  DTContext::Get()->CreateNewObject(typeID, parent);
}

Object_Internal::~Object_Internal() {
    //global->RemoveNewObject(heapIndex);
}


Object * Object_Internal::GetParent() {
    return parent;
}





Primitive Object_Internal::Get(const std::string & name) {
    return Primitive();
}
void Object_Internal::Set(const std::string & name, const Primitive &) {

}
Primitive Object_Internal::CallMethod(const std::string & name, const std::vector<Primitive> & args) {
    return Primitive();
}

bool Object_Internal::IsNative() const {
    return true;
}
int Object_Internal::GetTypeID() const {
    return type;
}


uint32_t Object_Internal::AddNonNativeReference(Object * ref) {
    return 0;
}
void Object_Internal::UpdateNonNativeReference(Object *, uint32_t index) {

}
Object * Object_Internal::GetNonNativeReference(uint32_t index) const {
    return nullptr;
}


