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
        - WriteState() is now "getState()" (returns an array)
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

SANDBOXE_NATIVE_DEF(__data_table_write_state) {
    auto data = (Sandboxe::DataTableObject*)source;
    auto bytes = data->WriteState();
    std::vector<Sandboxe::Script::Runtime::Primitive> out(bytes.size());
    for(uint32_t i = 0; i < bytes.size(); ++i) {
        out[i] = bytes[i];
    }
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__data_table_read_state) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto data = (Sandboxe::DataTableObject*)source;
    std::vector<uint8_t> bytes;
    data->ReadState(bytes);
    
    std::vector<Sandboxe::Script::Runtime::Primitive> out(bytes.size());
    for(uint32_t i = 0; i < bytes.size(); ++i) {
        out[i] = (int)bytes[i];
    }

    context.SetReturnArray(out);
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
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

            


        }
        
    );
    
}
    
    
    
}
}




#endif
