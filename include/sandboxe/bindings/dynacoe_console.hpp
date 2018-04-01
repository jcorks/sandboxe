#ifndef H_sandboxe_bindings_dynacoe_console
#define H_sandboxe_bindings_dynacoe_console
#include "binding_helpers.h"

namespace Sandboxe {
namespace Bindings {

SANDBOXE_NATIVE_DEF(__console_is_visible) {
    return Dynacoe::Console::IsVisible();
}

SANDBOXE_NATIVE_DEF(__console_show) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Console::Show(arguments[0]);
    SANDBOXE_NORETURN;
}


SANDBOXE_NATIVE_DEF(__console_is_locked) {
    return Dynacoe::Console::IsLocked();
}

SANDBOXE_NATIVE_DEF(__console_lock) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Console::Lock(arguments[0]);
    SANDBOXE_NORETURN;
}    

SANDBOXE_NATIVE_DEF(__console_get_num_lines) {
    return Dynacoe::Console::GetNumLines();
}    

SANDBOXE_NATIVE_DEF(__console_get_line) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    return Dynacoe::Console::GetLine(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__console_clear) {
    Dynacoe::Console::Clear();
    SANDBOXE_NORETURN;
}

SANDBOXE_NATIVE_DEF(__console_overlay_message_mode) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Console::OverlayMessageMode((Dynacoe::Console::MessageMode) (int)arguments[0]);
    SANDBOXE_NORETURN;
}

SANDBOXE_NATIVE_DEF(__console_get_overlay_message_mode) {
    return (int)Dynacoe::Console::GetOverlayMessageMode();
}

SANDBOXE_NATIVE_DEF(__console_stream_system) {
    for(uint32_t i = 0; i < arguments.size(); ++i)
        Dynacoe::Console::System() << std::string(arguments[i]);
    SANDBOXE_NORETURN;
}


SANDBOXE_NATIVE_DEF(__console_stream_info) {
    for(uint32_t i = 0; i < arguments.size(); ++i)
        Dynacoe::Console::Info() << std::string(arguments[i]);
    SANDBOXE_NORETURN;
}

SANDBOXE_NATIVE_DEF(__console_stream_error) {
    for(uint32_t i = 0; i < arguments.size(); ++i)
        Dynacoe::Console::Error() << std::string(arguments[i]);
    SANDBOXE_NORETURN;
}

SANDBOXE_NATIVE_DEF(__console_stream_warning) {
    for(uint32_t i = 0; i < arguments.size(); ++i)
        Dynacoe::Console::Warning() << std::string(arguments[i]);
    SANDBOXE_NORETURN;
}





void dynacoe_console(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    fns.push_back({"__console_is_visible", __console_is_visible});
    fns.push_back({"__console_show", __console_show});
    fns.push_back({"__console_is_locked", __console_is_locked});
    fns.push_back({"__console_lock", __console_lock});
    fns.push_back({"__console_get_num_lines", __console_get_num_lines});
    fns.push_back({"__console_get_line", __console_get_line});
    fns.push_back({"__console_clear", __console_clear});
    fns.push_back({"__console_overlay_message_mode", __console_overlay_message_mode});
    fns.push_back({"__console_get_overlay_message_mode", __console_get_overlay_message_mode});

    fns.push_back({"__console_stream_system",  __console_stream_system});
    fns.push_back({"__console_stream_info",    __console_stream_info});
    fns.push_back({"__console_stream_error",   __console_stream_error});
    fns.push_back({"__console_stream_warning", __console_stream_warning});
}

}
}



#endif