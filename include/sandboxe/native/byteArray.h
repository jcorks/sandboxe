#ifndef h_sandboxe_byte_array_included
#define h_sandboxe_byte_array_included

#include <sandboxe/native/byteArray.h>

namespace Sandboxe {

class ByteArrayObject : public Sandboxe::Script::Runtime::Object {
  public:
    ByteArrayObject() :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ByteArrayT)
    {}
      
    std::vector<uint8_t> data;
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "ByteArray";
    }

};

}

#endif