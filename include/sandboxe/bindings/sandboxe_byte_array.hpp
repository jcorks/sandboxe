#ifndef dynacoe_byte_array_sandboxe_binding_included
#define dynacoe_byte_array_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/byteArray.h>


namespace Sandboxe {
namespace Bindings {
    

// managed properties



SANDBOXE_NATIVE_DEF(__byte_array_get) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    uint32_t i = arguments[0];
    auto t = (Sandboxe::ByteArrayObject*)source;
    if (i >= t->data.size()) return;
    context.SetReturnValue(t->data[i]);
}

SANDBOXE_NATIVE_DEF(__byte_array_set) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    uint32_t i = arguments[0];
    auto t = (Sandboxe::ByteArrayObject*)source;
    if (i >= t->data.size()) return;
    uint8_t element = (int)arguments[1];    
    context.SetReturnValue(t->data[i] = element);
}


SANDBOXE_NATIVE_DEF(__byte_array_set_size) {
    auto t = (Sandboxe::ByteArrayObject*)source;
    t->data.resize(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__byte_array_get_size) {
    auto t = (Sandboxe::ByteArrayObject*)source;
    context.SetReturnValue(t->data.size());
}







/// global functions
SANDBOXE_NATIVE_DEF(__byte_array_create) {
    context.SetReturnValue(new Sandboxe::ByteArrayObject);
}


void sandboxe_byte_array(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::ByteArrayT,
        // methods
        {
            {"get", __byte_array_get},
            {"set", __byte_array_set}
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"size", {__byte_array_get_size, __byte_array_set_size}},

        } 
    );
    
    fns.push_back({"__byte_array_create", __byte_array_create});    
}
    
    
    
}
}




#endif