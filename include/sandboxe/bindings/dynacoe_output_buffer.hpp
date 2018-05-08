#ifndef h_dynacoe_sandboxe_output_buffer_included
#define h_dynacoe_sandboxe_output_buffer_included



#include <sandboxe/native/native.h>
#include <sandboxe/native/iobuffer.h>

/*
    Dynacoe::OutputBuffer  class bindings.

    Notes:
        - size and position setting are condensed into 2 properties 
            - position r/w
            - size r-only

 */





namespace Sandboxe {
namespace Bindings {






// functions 


SANDBOXE_NATIVE_DEF(__output_buffer_commit) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    bool append = false;
    if (arguments.size() > 1)
        append = arguments[1];
    Sandboxe::OutputBufferObject * v = (Sandboxe::OutputBufferObject*)source;
    v->localIO.CommitToFile(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__output_buffer_write_string) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::OutputBufferObject * v = (Sandboxe::OutputBufferObject*)source;
    v->localIO.WriteString(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__output_buffer_write_bytes) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto input = context.GetArrayArgument(0);
    if (!input) return; 
    Sandboxe::OutputBufferObject * v = (Sandboxe::OutputBufferObject*)source;
    std::vector<uint8_t> bytes(input->size());
    for(uint8_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = (int)(*input)[i];
    }
    v->localIO.WriteBytes(bytes);
}




SANDBOXE_NATIVE_DEF(__output_buffer_write) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::OutputBufferObject * v = (Sandboxe::OutputBufferObject*)source;
    switch((int)arguments[0]) {
      case 0: v->localIO.Write<int>(arguments[0]); break;
      case 1: v->localIO.Write<float>(arguments[0]); break;
      case 2: v->localIO.Write<uint32_t>(arguments[0]); break;
      case 3: v->localIO.Write<uint8_t>((int)arguments[0]); break;
      default:;
    }
}

SANDBOXE_NATIVE_DEF(__output_buffer_clear) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::OutputBufferObject * v = (Sandboxe::OutputBufferObject*)source;
    v->localIO.Clear();
}


SANDBOXE_NATIVE_DEF(__output_buffer_get_data) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::OutputBufferObject * v = (Sandboxe::OutputBufferObject*)source;
    std::vector<uint8_t> bytes = v->localIO.GetData();
    std::vector<Sandboxe::Script::Runtime::Primitive> output(bytes.size());
    for(uint8_t i = 0; i < bytes.size(); ++i) {
        output[i] = (int)bytes[i];
    }
    context.SetReturnArray(output);
}

// properties 

SANDBOXE_NATIVE_DEF(__output_buffer_get_size) {
    Sandboxe::OutputBufferObject * v = (Sandboxe::OutputBufferObject*)source;
    context.SetReturnValue(v->localIO.Size());
}




/// global functions
SANDBOXE_NATIVE_DEF(__output_buffer_create) {
    context.SetReturnValue(new Sandboxe::OutputBufferObject);
}


void dynacoe_output_buffer(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::OutputBufferT,
        // methods
        {
            {"write",         __output_buffer_write},
            {"writeBytes",    __output_buffer_write_bytes},
            {"writeString",   __output_buffer_write_string},
            {"getData",       __output_buffer_get_data},
            {"clear",         __output_buffer_clear},
            {"commit",        __output_buffer_commit},

        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"size",     {__output_buffer_get_size, SANDBOXE_NATIVE_EMPTY}}
        }
    );
    
    fns.push_back({"__output_buffer_create", __output_buffer_create});    
}


}
}

#endif
