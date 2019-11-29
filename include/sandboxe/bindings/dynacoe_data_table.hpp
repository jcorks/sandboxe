#ifndef dynacoe_data_table_sandboxe_binding_included
#define dynacoe_data_table_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/dataTable.h>
#include <sandboxe/bindings/dynacoe_component.hpp>
/*

    Dynacoe::DataTable bindings 
    
    Notes:
        - as usual, native object inherets from ComponentAdaptor 
        - only reads/writes strings and byte vectors
        - all reads output the result
        - WriteState() is now "getState()" and returns a string of the hexified data
        - ReadState() is now "setState()"

*/


namespace Sandboxe {
namespace Bindings {




SANDBOXE_NATIVE_DEF(__data_table_read_byte_array) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto data = (Sandboxe::DataTableObject*)source;
    std::vector<uint8_t> out;
    data->Read(arguments[0], out);
    std::vector<Sandboxe::Script::Runtime::Primitive> converted(out.size());
    for(uint32_t i = 0; i < out.size(); ++i) {
        converted[i] = out[i];
    }
    context.SetReturnArray(converted);
}

SANDBOXE_NATIVE_DEF(__data_table_read_string) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto data = (Sandboxe::DataTableObject*)source;
    std::string out;
    data->Read(arguments[0], out);
    context.SetReturnValue(out);
}


SANDBOXE_NATIVE_DEF(__data_table_write_string) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto data = (Sandboxe::DataTableObject*)source;
    std::string out = arguments[1];
    data->Write(arguments[0], out);
}

SANDBOXE_NATIVE_DEF(__data_table_write_byte_array) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto input = context.GetArrayArgument(0);
    if (!input) return;
    auto data = (Sandboxe::DataTableObject*)source;
    std::vector<uint8_t> inputConverted(input->size());
    for(uint8_t i = 0; i < inputConverted.size(); ++i) {
        inputConverted[i] = (int)(*input)[i];
    }
    data->Write(arguments[0], inputConverted);
}

SANDBOXE_NATIVE_DEF(__data_table_query) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto data = (Sandboxe::DataTableObject*)source;
    context.SetReturnValue(data->Query(arguments[0]));
}

SANDBOXE_NATIVE_DEF(__data_table_remove) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto data = (Sandboxe::DataTableObject*)source;
    data->Remove(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__data_table_clear) {
    auto data = (Sandboxe::DataTableObject*)source;
    data->Clear();
}


const char * byte_to_hex(uint8_t val) {
    static char hex[2];
    switch(val/16) {
      case 0: hex[0] = '0'; break;
      case 1: hex[0] = '1'; break;
      case 2: hex[0] = '2'; break;
      case 3: hex[0] = '3'; break;
      case 4: hex[0] = '4'; break;
      case 5: hex[0] = '5'; break;
      case 6: hex[0] = '6'; break;
      case 7: hex[0] = '7'; break;
      case 8: hex[0] = '8'; break;
      case 9: hex[0] = '9'; break;
      case 10: hex[0] = 'a'; break;
      case 11: hex[0] = 'b'; break;
      case 12: hex[0] = 'c'; break;
      case 13: hex[0] = 'd'; break;
      case 14: hex[0] = 'e'; break;
      case 15: hex[0] = 'f'; break;
    }
    switch(val%16) {
      case 0: hex[1] = '0'; break;
      case 1: hex[1] = '1'; break;
      case 2: hex[1] = '2'; break;
      case 3: hex[1] = '3'; break;
      case 4: hex[1] = '4'; break;
      case 5: hex[1] = '5'; break;
      case 6: hex[1] = '6'; break;
      case 7: hex[1] = '7'; break;
      case 8: hex[1] = '8'; break;
      case 9: hex[1] = '9'; break;
      case 10: hex[1] = 'a'; break;
      case 11: hex[1] = 'b'; break;
      case 12: hex[1] = 'c'; break;
      case 13: hex[1] = 'd'; break;
      case 14: hex[1] = 'e'; break;
      case 15: hex[1] = 'f'; break;
    }
    return hex;
}

uint8_t hex_to_byte(const char * hex) {
    uint8_t val;
    switch(hex[0]) {
      case '0': val = 0; break;
      case '1': val = 16; break;
      case '2': val = 16*2; break;
      case '3': val = 16*3; break;
      case '4': val = 16*4; break;
      case '5': val = 16*5; break;
      case '6': val = 16*6; break;
      case '7': val = 16*7; break;
      case '8': val = 16*8; break;
      case '9': val = 16*9; break;

      case 'a': case 'A': val = 16*10; break;
      case 'b': case 'B': val = 16*11; break;
      case 'c': case 'C': val = 16*12; break;
      case 'd': case 'D': val = 16*13; break;
      case 'e': case 'E': val = 16*14; break;
      case 'f': case 'F': val = 16*15; break;
    }

    switch(hex[1]) {
      case '0': val += 0; break;
      case '1': val += 1; break;
      case '2': val += 2; break;
      case '3': val += 3; break;
      case '4': val += 4; break;
      case '5': val += 5; break;
      case '6': val += 6; break;
      case '7': val += 7; break;
      case '8': val += 8; break;
      case '9': val += 9; break;

      case 'a': case 'A': val += 10; break;
      case 'b': case 'B': val += 11; break;
      case 'c': case 'C': val += 12; break;
      case 'd': case 'D': val += 13; break;
      case 'e': case 'E': val += 14; break;
      case 'f': case 'F': val += 15; break;
    }
    return val;
}   


static const std::string & data_to_hex(const uint8_t * data, uint32_t size) {
    static std::string imm;
    imm.resize(size*2);
    const char * hex;
    for(uint32_t i = 0; i < size; ++i) {
        hex = byte_to_hex(data[i]);
        imm[i*2+0] = hex[0];
        imm[i*2+1] = hex[1];
    }
    return imm;
}

SANDBOXE_NATIVE_DEF(__data_table_write_state) {
    auto data = (Sandboxe::DataTableObject*)source;
    auto bytes = data->WriteState();
    context.SetReturnValue(data_to_hex(&bytes[0], bytes.size()));
}

SANDBOXE_NATIVE_DEF(__data_table_read_state) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto data = (Sandboxe::DataTableObject*)source;
    std::vector<uint8_t> bytes;
    const std::string & input = arguments[0];
    bytes.resize(input.size()/2);
    for(uint32_t i = 0; i < input.size()/2; ++i) {
        bytes[i] = hex_to_byte(&input[i*2]);
    }
    data->ReadState(bytes);
}






void dynacoe_data_table(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::DataTableT,
        {
            {"writeString",    __data_table_write_string},
            {"writeByteArray", __data_table_write_byte_array},

            {"readString",    __data_table_read_string},
            {"readByteArray", __data_table_read_byte_array},

            {"query", __data_table_query},
            {"remove", __data_table_remove},
            {"clear", __data_table_clear},
            
            {"getState", __data_table_write_state},
            {"setState", __data_table_read_state},

            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////
            {"step", __component_step},
            {"draw", __component_draw},

            {"installEvent", __component_install_event},
            {"uninstallEvent", __component_uninstall_event},
            
            {"emitEvent", __component_emit_event},
            {"canHandleEvent", __component_emit_event},
            {"installHook", __component_install_hook},
            {"uninstallHook", __component_uninstall_hook},
            {"installHandler", __component_install_handler},
            {"uninstallHandler", __component_uninstall_handler},
            {"getKnownEvents", __component_get_known_events}
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

        },

        // properties
        {
            
        },
        
        // native properties
        {
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

            {"tag", {__component_get_tag, __component_set_tag}},
            {"info", {__component_get_info, __component_set_info}},
            {"isStepping", {__component_get_step, __component_set_step}},
            {"isDrawing", {__component_get_draw, __component_set_draw}},
            {"host", {__component_get_host, __component_set_host}},
            {"onStep", {__component_get_on_step, __component_set_on_step}},
            {"onDraw", {__component_get_on_draw, __component_set_on_draw}}
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

            


        }
        
    );
    
}
    
    
    
}
}




#endif
