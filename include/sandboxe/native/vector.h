#ifndef h_sandboxe_vector_included
#define h_sandboxe_vector_included

namespace Sandboxe {
    
class VectorObject : public Sandboxe::Script::Runtime::Object {
  public:
    VectorObject(const Dynacoe::Vector & v = {}) : 
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::VectorT),
        vector(v) {}
        
        
    Dynacoe::Vector vector;
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "Vector";
    }
        
};

}


#endif