#ifndef h_sandboxe_input_buffer_included
#define h_sandboxe_input_buffer_included
#include <cassert>
#include <sandboxe/native/delta.h>
namespace Sandboxe {
    
class InputBufferObject : public Sandboxe::Script::Runtime::Object {
  public:
    InputBufferObject() : 
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::InputBufferT) {}
        
    Dynacoe::InputBuffer localIO;
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "InputBuffer";
    }
        
};



class OutputBufferObject : public Sandboxe::Script::Runtime::Object {
  public:
    OutputBufferObject() : 
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::OutputBufferT) {}
        
    Dynacoe::OutputBuffer localIO;
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "OutputBuffer";
    }
        
};


}


#endif