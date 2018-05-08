#ifndef h_dynacoe_sandboxe_input_buffer_included
#define h_dynacoe_sandboxe_input_buffer_included



#include <sandboxe/native/native.h>
#include <sandboxe/native/iobuffer.h>

/*
    Dynacoe::InputBuffer  class bindings.

    Notes:
        - size and position setting are condensed into 2 properties 
            - position r/w
            - size r-only

 */





namespace Sandboxe {
namespace Bindings {






// functions 

SANDBOXE_NATIVE_DEF(__input_buffer_open_buffer) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto input = context.GetArrayArgument(0);
    if (!input) return; 
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    std::vector<uint8_t> bytes(input->size());
    for(uint8_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = (int)(*input)[i];
    }
    v->localIO.OpenBuffer(bytes);
}

SANDBOXE_NATIVE_DEF(__input_buffer_open) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    v->localIO.Open(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__input_buffer_read_string) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    context.SetReturnValue(v->localIO.ReadString(arguments[0]));
}

SANDBOXE_NATIVE_DEF(__input_buffer_read_bytes) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    std::vector<uint8_t> bytes = v->localIO.ReadBytes(arguments[0]);
    std::vector<Sandboxe::Script::Runtime::Primitive> output(bytes.size());
    for(uint8_t i = 0; i < bytes.size(); ++i) {
        output[i] = (int)bytes[i];
    }
    context.SetReturnArray(output);
}

SANDBOXE_NATIVE_DEF(__input_buffer_read) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    switch((int)arguments[0]) {
      case 0: context.SetReturnValue(v->localIO.Read<int>()); break;
      case 1: context.SetReturnValue(v->localIO.Read<float>()); break;
      case 2: context.SetReturnValue(v->localIO.Read<uint32_t>()); break;
      case 3: context.SetReturnValue(v->localIO.Read<uint8_t>()); break;
      default:;
    }
}





// properties 

SANDBOXE_NATIVE_DEF(__input_buffer_get_size) {
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    context.SetReturnValue(v->localIO.Size());
}

SANDBOXE_NATIVE_DEF(__input_buffer_get_position) {
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    context.SetReturnValue(v->localIO.Size() - v->localIO.BytesLeft());
}

SANDBOXE_NATIVE_DEF(__input_buffer_set_position) {
    Sandboxe::InputBufferObject * v = (Sandboxe::InputBufferObject*)source;
    v->localIO.GoToByte(arguments[0]);
}



/// global functions
SANDBOXE_NATIVE_DEF(__input_buffer_create) {
    context.SetReturnValue(new Sandboxe::InputBufferObject);
}


void dynacoe_input_buffer(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::InputBufferT,
        // methods
        {
            {"openBuffer", __input_buffer_open_buffer},
            {"open",       __input_buffer_open},
            {"readString", __input_buffer_read_string},
            {"readBytes",  __input_buffer_read_bytes},
            {"read",       __input_buffer_read}
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"position", {__input_buffer_get_position, __input_buffer_set_position}},
            {"size",     {__input_buffer_get_size, SANDBOXE_NATIVE_EMPTY}}
        }
    );
    
    fns.push_back({"__input_buffer_create", __input_buffer_create});    
}


}
}

#endif
