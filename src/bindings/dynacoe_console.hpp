#ifndef H_sandboxe_bindings_dynacoe_console
#define H_sandboxe_bindings_dynacoe_console


#include "binding_helpers.h"


namespace Sandboxe {
namespace Bindings {

SANDBOXE_BIND_DEF(__console_is_visible) {
    SANDBOXE_SCOPE;
    return SANDBOXE_VALUE(Dynacoe::Chain() << Dynacoe::Console::IsVisible());
}
SANDBOXE_BIND_DEF(__console_show) {
    SANDBOXE_SCOPE;
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Console::Show((Dynacoe::Chain() << SANDBOXE_ARG(0)).AsInt());
    SANDBOXE_NORETURN;
}
SANDBOXE_BIND_DEF(__console_is_locked) {
    SANDBOXE_SCOPE;
    return SANDBOXE_VALUE(Dynacoe::Chain() << Dynacoe::Console::IsLocked());
}
SANDBOXE_BIND_DEF(__console_lock) {
    SANDBOXE_SCOPE;
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Console::Lock((Dynacoe::Chain() << SANDBOXE_ARG(0)).AsInt());
    SANDBOXE_NORETURN;
}    

SANDBOXE_BIND_DEF(__console_get_num_lines) {
    SANDBOXE_SCOPE;
    return SANDBOXE_VALUE(Dynacoe::Chain() << Dynacoe::Console::GetNumLines());
}    

SANDBOXE_BIND_DEF(__console_get_line) {
    SANDBOXE_SCOPE;
    SANDBOXE_ASSERT__ARG_COUNT(1);
    return SANDBOXE_VALUE(
        Dynacoe::Chain() << Dynacoe::Console::GetLine(
            (Dynacoe::Chain() << SANDBOXE_ARG(0)).AsInt()
        )
    );
}

SANDBOXE_BIND_DEF(__console_clear) {
    SANDBOXE_SCOPE;
    Dynacoe::Console::Clear();
    SANDBOXE_NORETURN;
}

SANDBOXE_BIND_DEF(__console_overlay_message_mode) {
    SANDBOXE_SCOPE;
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Console::OverlayMessageMode(
        (Dynacoe::Console::MessageMode)
        (Dynacoe::Chain() << SANDBOXE_ARG(0)).AsInt()
    );
    
    SANDBOXE_NORETURN;
}

SANDBOXE_BIND_DEF(__console_get_overlay_message_mode) {
    SANDBOXE_SCOPE;
    return SANDBOXE_VALUE(
        (Dynacoe::Chain() << (int)Dynacoe::Console::GetOverlayMessageMode())
    );
}

SANDBOXE_BIND_DEF(__console_stream_system) {
    SANDBOXE_SCOPE;
    for(uint32_t i = 0; i < SANDBOXE_ARG_COUNT; ++i)
        Dynacoe::Console::System() << SANDBOXE_ARG(i);
    SANDBOXE_NORETURN;
}


SANDBOXE_BIND_DEF(__console_stream_info) {
    SANDBOXE_SCOPE;
    for(uint32_t i = 0; i < SANDBOXE_ARG_COUNT; ++i)
        Dynacoe::Console::Info() << SANDBOXE_ARG(i);
    SANDBOXE_NORETURN;
}

SANDBOXE_BIND_DEF(__console_stream_error) {
    SANDBOXE_SCOPE;
    for(uint32_t i = 0; i < SANDBOXE_ARG_COUNT; ++i)
        Dynacoe::Console::Error() << SANDBOXE_ARG(i);
    SANDBOXE_NORETURN;
}

SANDBOXE_BIND_DEF(__console_stream_warning) {
    SANDBOXE_SCOPE;
    for(uint32_t i = 0; i < SANDBOXE_ARG_COUNT; ++i)
        Dynacoe::Console::Warning() << SANDBOXE_ARG(i);
    SANDBOXE_NORETURN;
}


    
SANDBOXE_BINDSET_DEF(definitions__console) {
    SANDBOXE_BIND_CALL("__console_is_visible", __console_is_visible);
    SANDBOXE_BIND_CALL("__console_show", __console_show);
    SANDBOXE_BIND_CALL("__console_is_locked", __console_is_locked);
    SANDBOXE_BIND_CALL("__console_lock", __console_lock);
    SANDBOXE_BIND_CALL("__console_get_num_lines", __console_get_num_lines);
    SANDBOXE_BIND_CALL("__console_get_line", __console_get_line);
    SANDBOXE_BIND_CALL("__console_clear", __console_clear);
    SANDBOXE_BIND_CALL("__console_overlay_message_mode", __console_overlay_message_mode);
    SANDBOXE_BIND_CALL("__console_get_overlay_message_mode", __console_get_overlay_message_mode);

    SANDBOXE_BIND_CALL("__console_stream_system",  __console_stream_system);
    SANDBOXE_BIND_CALL("__console_stream_info",    __console_stream_info);
    SANDBOXE_BIND_CALL("__console_stream_error",   __console_stream_error);
    SANDBOXE_BIND_CALL("__console_stream_warning", __console_stream_warning);

}



}
}



#endif