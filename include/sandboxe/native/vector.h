#ifndef h_sandboxe_vector_included
#define h_sandboxe_vector_included
#include <cassert>
#include <sandboxe/native/delta.h>
namespace Sandboxe {
    
class VectorObject : public Sandboxe::Script::Runtime::Object {
  public:
    VectorObject(const Dynacoe::Vector & v = {}) : 
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::VectorT)
         {
        owned = true;
        expired = true;
        vector = new Dynacoe::Vector();
        *vector = v;
    }
    
    VectorObject(Dynacoe::Vector * v) :
    Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::VectorT)
    {
        vector = v;
        owned = false;
        expired = false;
        
    }
    
    ~VectorObject() {
        if (owned) delete vector;
    }
        
        
    Dynacoe::Vector * vector;
    Delta<VectorObject> delta;
    bool expired;
    bool owned;
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "Vector";
    }
        
};

}


#endif