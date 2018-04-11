#ifndef h_sandboxe_byte_array_included
#define h_sandboxe_byte_array_included

#include <sandboxe/native/byteArray.h>

namespace Sandboxe {

class ByteArray : public Dynacoe::ButtonListener {
  public:
    ByteArray(Sandboxe::Script::Runtime::Object * obj) {
        object = obj;
    }
      
    std::vector<uint8_t> data;
    Sandboxe::Script::Runtime::Object * object;
};

}

#endif