#ifndef H_sandboxe_bindings_dynacoe_input
#define H_sandboxe_bindings_dynacoe_input
#include <sandboxe/native/native.h>
#include <sandboxe/native/inputListener.h>
#include <sandboxe/native/unicodeListener.h>

/*
    Dynacoe::Input Bindings
    
    notes:
        - Game pads have not been bound yet
        - Lock input has not been implemented. Seems superfluous.

*/

namespace Sandboxe {
namespace Bindings {

SANDBOXE_NATIVE_DEF(__input_mouse_x) {
    context.SetReturnValue(Dynacoe::Input::MouseX());
}

SANDBOXE_NATIVE_DEF(__input_mouse_y) {
    context.SetReturnValue(Dynacoe::Input::MouseY());
}

SANDBOXE_NATIVE_DEF(__input_mouse_x_delta) {
    context.SetReturnValue(Dynacoe::Input::MouseXDelta());
}

SANDBOXE_NATIVE_DEF(__input_mouse_y_delta) {
    context.SetReturnValue(Dynacoe::Input::MouseYDelta());
}

SANDBOXE_NATIVE_DEF(__input_mouse_wheel) {
    context.SetReturnValue(Dynacoe::Input::MouseWheel());
}

SANDBOXE_NATIVE_DEF(__input_key_listener_new) {
    auto listener = new Sandboxe::InputListenerObject;
    Dynacoe::Input::AddKeyboardListener(listener);
    context.SetReturnValue(listener);
}


SANDBOXE_NATIVE_DEF(__input_pointer_listener_new) {
    auto listener = new Sandboxe::InputListenerObject;
    Dynacoe::Input::AddMouseListener(listener);
    context.SetReturnValue(listener);
}

SANDBOXE_NATIVE_DEF(__input_pad_listener_new) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto listener = new Sandboxe::InputListenerObject;
    Dynacoe::Input::AddPadListener(listener, arguments[0]);
    context.SetReturnValue(listener);
}

SANDBOXE_NATIVE_DEF(__input_mapped_listener_new) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto listener = new Sandboxe::InputListenerObject;
    Dynacoe::Input::AddMappedListener(listener, arguments[0]);
    context.SetReturnValue(listener);
}

SANDBOXE_NATIVE_DEF(__input_unicode_listener_new) {
    auto listener = new Sandboxe::UnicodeListenerObject;
    Dynacoe::Input::AddUnicodeListener(listener);
    context.SetReturnValue(listener);
}

SANDBOXE_NATIVE_DEF(__input_set_deadzone) {
    SANDBOXE_ASSERT__ARG_COUNT(3);
    Dynacoe::Input::SetDeadzone(arguments[0], arguments[1], arguments[2]);
}

SANDBOXE_NATIVE_DEF(__input_get_state) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    // TODO: we need a switch for this!
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) {
        context.SetReturnValue(Dynacoe::Input::GetState(std::string(arguments[0])));            
    } else {

        if (arguments.size() == 2) {
            context.SetReturnValue(Dynacoe::Input::GetState(arguments[0], arguments[1]));
        } else {
            context.SetReturnValue(Dynacoe::Input::GetState((int)arguments[0]));
        }
    }

}

SANDBOXE_NATIVE_DEF(__input_query_pads) {
    std::vector<Sandboxe::Script::Runtime::Primitive> output;
    auto result = Dynacoe::Input::QueryPads();
    for(uint32_t i = 0; i < result.size(); ++i) {
        output.push_back(result[i]);
    }
    context.SetReturnArray(output);
}


SANDBOXE_NATIVE_DEF(__input_map_input) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) return;

    if (arguments.size() > 2) {
        Dynacoe::Input::MapInput(arguments[0], arguments[1], arguments[2]);
    } else {
        Dynacoe::Input::MapInput(arguments[0], arguments[1]);
    }

}

SANDBOXE_NATIVE_DEF(__input_unmap_input) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Input::UnmapInput(arguments[0]);
}


SANDBOXE_NATIVE_DEF(__input_remove_listener) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    Dynacoe::Input::RemoveListener(b);
    delete b;
}

SANDBOXE_NATIVE_DEF(__input_remove_unicode_listener) {
    auto b = (Sandboxe::UnicodeListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    Dynacoe::Input::RemoveUnicodeListener(b);
    delete b;
}

SANDBOXE_NATIVE_DEF(__input_get_last_unicode)  {
    context.SetReturnValue(Dynacoe::Input::GetLastUnicode());
}


SANDBOXE_NATIVE_DEF(__input_get_on_press) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onPress)
        context.SetReturnValue(b->onPress);
}


SANDBOXE_NATIVE_DEF(__input_get_on_change) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onChange)
        context.SetReturnValue(b->onChange);
}

SANDBOXE_NATIVE_DEF(__input_get_on_active) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onActive)
        context.SetReturnValue(b->onActive);
}

SANDBOXE_NATIVE_DEF(__input_get_on_release) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onRelease)
        context.SetReturnValue(b->onRelease);
}

SANDBOXE_NATIVE_DEF(__input_get_on_new_unicode) {
    auto b = (Sandboxe::UnicodeListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onNewUnicode)
        context.SetReturnValue(b->onNewUnicode);
}


SANDBOXE_NATIVE_DEF(__input_get_on_repeat_unicode) {
    auto b = (Sandboxe::UnicodeListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onRepeatUnicode)
        context.SetReturnValue(b->onRepeatUnicode);
}

SANDBOXE_NATIVE_DEF(__input_set_on_press) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onPress = arguments[0];
    if (b->onPress && !b->onPress->IsCallable()) {
        b->onPress = nullptr;
        return;
    }
    b->AddNonNativeReference(b->onPress);
}

SANDBOXE_NATIVE_DEF(__input_set_on_active) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onActive = arguments[0];
    if (b->onActive && !b->onActive->IsCallable()) {
        b->onActive = nullptr;
        return;
    }

    b->AddNonNativeReference(b->onActive);
}

SANDBOXE_NATIVE_DEF(__input_set_on_change) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onChange = arguments[0];
    if (b->onChange && !b->onChange->IsCallable()) {
        b->onChange = nullptr;
        return;
    }

    b->AddNonNativeReference(b->onChange);
}

 
SANDBOXE_NATIVE_DEF(__input_set_on_release) {
    auto b = (Sandboxe::InputListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onRelease = arguments[0];
    if (b->onRelease && !b->onRelease->IsCallable()) {
        b->onRelease = nullptr;
        return;
    }


    b->AddNonNativeReference(b->onRelease);
}

SANDBOXE_NATIVE_DEF(__input_set_on_new_unicode) {
    auto b = (Sandboxe::UnicodeListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onNewUnicode = arguments[0];
    if (b->onNewUnicode && !b->onNewUnicode->IsCallable()) {
        b->onNewUnicode = nullptr;
        return;
    }

    b->AddNonNativeReference(b->onNewUnicode);
}


SANDBOXE_NATIVE_DEF(__input_set_on_repeat_unicode) {
    auto b = (Sandboxe::UnicodeListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onRepeatUnicode = arguments[0];
    if (b->onRepeatUnicode && !b->onRepeatUnicode->IsCallable()) {
        b->onRepeatUnicode = nullptr;
        return;
    }

    b->AddNonNativeReference(b->onRepeatUnicode);
}


SANDBOXE_NATIVE_DEF(__input_show_virtual_keyboard) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    bool b = arguments[0];
    Dynacoe::Input::ShowVirtualKeyboard(b);
}


void dynacoe_input(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::InputListenerT,
        // users should populate:
        // 
        //  "onPress",
        //  "onActive",
        //  "onChange",
        //  "onRelease"

        // methods
        {
            {"remove", __input_remove_listener}
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"onPress", {__input_get_on_press, __input_set_on_press}},
            {"onActive", {__input_get_on_active, __input_set_on_active}},
            {"onRelease", {__input_get_on_release, __input_set_on_release}},
            {"onChange", {__input_get_on_change, __input_set_on_change}}


        }
    );
    
    
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::UnicodeListenerT,
        // users should populate:
        // 
        //  "onNewUnicode",

        // methods
        {
            {"remove", __input_remove_unicode_listener}
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"onNewUnicode", {__input_get_on_new_unicode, __input_set_on_new_unicode}},
            {"onRepeatUnicode", {__input_get_on_repeat_unicode, __input_set_on_repeat_unicode}},


        }
    );
    

    fns.push_back({"__input_key_listener_new", __input_key_listener_new});
    fns.push_back({"__input_pointer_listener_new", __input_pointer_listener_new});
    fns.push_back({"__input_pad_listener_new", __input_pad_listener_new});
    fns.push_back({"__input_mapped_listener_new", __input_mapped_listener_new});
    fns.push_back({"__input_unicode_listener_new", __input_unicode_listener_new});
    fns.push_back({"__input_set_deadzone",  __input_set_deadzone});
    fns.push_back({"__input_mouse_x", __input_mouse_x});
    fns.push_back({"__input_mouse_y", __input_mouse_y});
    fns.push_back({"__input_mouse_x_delta", __input_mouse_x_delta});
    fns.push_back({"__input_mouse_y_delta", __input_mouse_y_delta});
    fns.push_back({"__input_mouse_wheel", __input_mouse_wheel});
    fns.push_back({"__input_get_state", __input_get_state});
    fns.push_back({"__input_map_input", __input_map_input});
    fns.push_back({"__input_unmap_input", __input_unmap_input});
    fns.push_back({"__input_query_pads", __input_query_pads});
    fns.push_back({"__input_get_last_unicode", __input_get_last_unicode});
    fns.push_back({"__input_show_virtual_keyboard", __input_show_virtual_keyboard});
}

}
}



#endif
