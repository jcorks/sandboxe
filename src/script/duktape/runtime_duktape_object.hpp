using Sandboxe::Script::Runtime::Object;

class Object_Internal {
  public:
    Object_Internal(int typeID, Object * parent_) : parent(parent_) {
        type = typeID;
        heapIndex = global->CreateNewObject(typeID, parent);
    }
    
    ~Object_Internal() {
        //global->RemoveNewObject(heapIndex);
    }
    
    
    Object * GetParent() {
        return parent;
    }
    
    int GetTypeID() const {
        return type;
    }
  private:
    int type;
    uint32_t heapIndex;
    Object * parent;
};

Object::Object(int typeID) {
    data = new Object_Internal(typeID, this);    
}

Object::~Object() {
    delete data;
} 

Object::Object(Object_Internal & n) {
    // pass ownership, internal only
    data = &n;
}


Primitive Object::Get(const std::string & name) {
    return Primitive();
}


void Object::Set(const std::string & name, const Primitive & value) {

}


Primitive Object::CallMethod(const std::string & name, const std::vector<Primitive> & args) {
    return Primitive();
}


bool Object::IsNative() const {
    return true;
}



int Object::GetTypeID() const {
    return data->GetTypeID();
}


uint32_t Object::AddNonNativeReference(Object * ref) {
    return 0;
}


void Object::UpdateNonNativeReference(Object * ref, uint32_t index) {

}




Object * Object::GetNonNativeReference(uint32_t index) const {
    return nullptr;
}
