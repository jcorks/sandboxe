#include <sandboxe/script/runtime.h>
#include <sandboxe/script/duktape/runtime_dt_object.h>
#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <sandboxe/script/duktape/runtime_dt_context.h>
#include <cassert>
using namespace Sandboxe::Script::Runtime;

static std::vector<Object_Internal*> temporary;
Object_Internal::Object_Internal(int typeID, Object * parent_) : parent(parent_) {
    type = typeID;
    heapIndex = 0;
}

Object_Internal::Object_Internal() {
    parent = nullptr;
    heapIndex = 0;
    type = -1;
}

void Object_Internal::AssignHeapEntry() {
    heapIndex =  DTContext::Get()->CreateHeapEntryFromObject(parent);
}

uint32_t Object_Internal::GetHeapStoreIndex() const {
    return heapIndex;
}

Object * Object_Internal::CreateTemporaryObjectFromStackTop() {
    Object_Internal * out = new Object_Internal();
    out->type = -1;
    out->parent = new Object(*out); // a little weird, but accurate
    out->heapIndex = DTContext::Get()->CreateHeapEntryFromDTStack(out->parent);
    temporary.push_back(out);
    return out->parent;
}

void Object_Internal::SweepTemporaryObjects() {
    
    for(uint32_t i = 0; i < temporary.size(); ++i) {
        // queue for removal
        DTContext::Get()->RemoveHeapEntry(temporary[i]->heapIndex);
        temporary[i]->heapIndex = 0;
    }
    temporary.clear();
}

Object_Internal::~Object_Internal() {
    // since this owner will no longer exist, return the temporary status 
    // of the object once more.
    for(uint32_t i = 0; i < ownedTemps.size(); ++i) {
        temporary.push_back(ownedTemps[i]->GetNative());
    }
    
    if (heapIndex) {    
        // we need to also remove the finalizer
        auto source = DTContext::Get()->GetCTX();
        int size = duk_get_top(source);
        DTContext::Get()->PushHeapEntryToDTTop(heapIndex);
        duk_push_undefined(source);
        duk_set_finalizer(source, -2);
        duk_pop(source);
        assert(size == duk_get_top(source));
        DTContext::Get()->RemoveHeapEntry(heapIndex);
    }
        
    printf("Deleted %p (heap tag %d)\n", parent, heapIndex);
}


Object * Object_Internal::GetParent() {
    return parent;
}





Primitive Object_Internal::Get(const std::string & name) {
    DTContext::Get()->PushHeapEntryToDTTop(heapIndex);
    TObject object(DTContext::Get()->GetCTX());
    auto out = object.GetAsPrimitive(name);
    duk_pop(DTContext::Get()->GetCTX());
}
void Object_Internal::Set(const std::string & name, const Primitive & data) {
    DTContext::Get()->PushHeapEntryToDTTop(heapIndex);
    TObject object(DTContext::Get()->GetCTX());
    object.Set(name, data);
    duk_pop(DTContext::Get()->GetCTX());
}
Primitive Object_Internal::CallMethod(const std::string & name, const std::vector<Primitive> & args) {
    DTContext::Get()->PushHeapEntryToDTTop(heapIndex);
    TObject object(DTContext::Get()->GetCTX());
    auto out = object.CallMethod(name, args);    
    duk_pop(DTContext::Get()->GetCTX());
    return out;
}

bool Object_Internal::IsNative() const {
    return true;
}
int Object_Internal::GetTypeID() const {
    return type;
}


uint32_t Object_Internal::AddNonNativeReference(Object * ref) {
    // first erase from temporary sweep
    for(uint32_t i = 0; i < temporary.size(); ++i) {
        if (temporary[i] == ref->GetNative()) {
            temporary.erase(temporary.begin()+i);
            break;
        }
    }
    
    // next add the object reference to this object to keep its ref count
    ownedTemps.push_back(ref);
    
    return 0;
}
void Object_Internal::UpdateNonNativeReference(Object * obj, uint32_t index) {
    if (index >= ownedTemps.size()) return;
    ownedTemps[index] = obj;
}
Object * Object_Internal::GetNonNativeReference(uint32_t index) const {
    if (index >= ownedTemps.size()) return nullptr;
    return ownedTemps[index];
}


