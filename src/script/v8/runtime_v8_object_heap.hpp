


class ObjectHeap {
  public:
    ObjectHeap(v8::Persistent<v8::Context> context) {
        heap = v8::Persistent<v8::Object>::New(v8::Object::New());        
        context->Global()->Set(v8::String::New("SANDBOXE_ObjectHeap"), heap, v8::PropertyAttribute::DontDelete);

        index = 1;
        
        
    }
    
    std::vector<uint32_t> PushArguments(const v8::Arguments & args) {
        std::vector<uint32_t> objs;
        for(uint32_t i = 0; i < args.Length(); ++i) {
            objs.push_back(Add(args[i]));
        }
        return objs;
    }
    
    void PopArguments(const std::vector<uint32_t> & data) {
        for(uint32_t i = 0; i < data.size(); ++i) {
            Remove(data[i]);
        }
    }
    
    
    

    uint32_t Add(const v8::Handle<v8::Value> & val) {
        uint32_t next;
        if (dead.empty()) {
            next = index++;
        } else {
            next = dead.top(); dead.pop();
        }
        heap->Set(next, val);
        return next;
    }

    void Remove(uint32_t i) {
        heap->Set(i, v8::Null());
        dead.push(i);
    }

    v8::Local<v8::Value> Get(uint32_t i) {
        v8::HandleScope scope;
        if (i == 0) return scope.Close(v8::Local<v8::Value>::New(v8::Null()));
        return scope.Close(heap->Get(i));
    }

    

    Sandboxe::Script::Runtime::Primitive GetAsPrimitive(uint32_t i) {
        v8::HandleScope scope;
        v8::Local<v8::Value> source = Get(i);
        if (!(!source.IsEmpty() && !source->IsUndefined() && !source->IsNull())) {
            return Primitive();
        }
        
        if (source->IsObject()) {
            v8::Local<v8::Object> object = source->ToObject();//(source)->ToObject()->Clone();
            if (object->InternalFieldCount()) { //< - Native object
                return
                    (
                        (Object_Internal*)object->GetPointerFromInternalField(0)
                    )->parent;
                
            } else if (object->IsString()) { //<- non-native object
                return *v8::String::Utf8Value(object) ? Primitive(std::string(*v8::String::Utf8Value(object))) : Primitive();

                
            } else {
                // eligible for cleanup
                return CreateObjectFromV8Internal(i);
        
            }
        } else {
            return *v8::String::Utf8Value(source) ? Primitive(std::string(*v8::String::Utf8Value(source))) : Primitive();
        }
    }
    
    std::vector<Sandboxe::Script::Runtime::Primitive> GetAsPrimitiveArray(uint32_t i) {
        v8::HandleScope scope;
        v8::Local<v8::Value> source = Get(i);
        if (!(!source.IsEmpty() && !source->IsUndefined() && !source->IsNull())) {
            return {};
        }
        if (!source->IsArray()) return {};

        std::vector<Sandboxe::Script::Runtime::Primitive> out;
        uint32_t len = v8::Array::Cast(*source)->Length();
        v8::Local<v8::Object> array = source->ToObject();
        for(uint32_t i = 0; i < len; ++i) {
            auto item = array->Get(i);
            out.push_back(GetAsPrimitive(Add(item)));
        }
        return out;
    }

    uint32_t GetSize() const {
        return index - dead.size();
    }

  private:
    uint32_t index;
    std::stack<uint32_t> dead;
    
    v8::Persistent<v8::Object> heap;

    Sandboxe::Script::Runtime::Object * CreateObjectFromV8Internal(uint32_t val) {
        Object_Internal * ref = new Object_Internal;
        ref->isNative = false;
        ref->typeData = nullptr;
        ref->parent = nullptr;
        
        // here's the magic: we get our own copy of the object and hold it captive 
        // even if it already exists as a temporary
        ref->heapAddress = global->storage->Add(global->storage->Get(val)->ToObject()->Clone());
        global->storage->Get(ref->heapAddress)->ToObject()->SetPointerInInternalField(0, ref);

        Object * temp = new Object(*ref);

        // gets cleaned up next cycle
        Object_Internal::temporary.push_back(temp);
        return temp;
    }

};