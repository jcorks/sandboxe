#ifndef H_sandboxe_bindings_dynacoe_input
#define H_sandboxe_bindings_dynacoe_input
#include <sandboxe/native/native.h>
#include <sandboxe/native/buttonListener.h>
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

SANDBOXE_NATIVE_DEF(__input_button_listener_new) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto listener = new Sandboxe::ButtonListenerObject;
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) {
        Dynacoe::Input::AddListener(listener, std::string(arguments[0]));            
    } else { // else mapped
        int input = arguments[0];
        if (input < 93) {
            Dynacoe::Input::AddListener(listener, (Dynacoe::Keyboard)input);
        } else if (input < 96) {
            Dynacoe::Input::AddListener(listener, (Dynacoe::MouseButtons)(input-93));
        }
    }
    context.SetReturnValue(listener);
}

SANDBOXE_NATIVE_DEF(__input_unicode_listener_new) {
    auto listener = new Sandboxe::UnicodeListenerObject;
    Dynacoe::Input::AddUnicodeListener(listener);
    context.SetReturnValue(listener);
}


SANDBOXE_NATIVE_DEF(__input_get_state) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    // TODO: we need a switch for this!
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) {
        context.SetReturnValue(Dynacoe::Input::GetState(std::string(arguments[0])));            
    } else {
        int input = arguments[0];

        if (input < 93) {
            context.SetReturnValue(Dynacoe::Input::GetState((Dynacoe::Keyboard)input));
        } else if (input < 96) {
            context.SetReturnValue(Dynacoe::Input::GetState((Dynacoe::MouseButtons)(input-93)));
        } else {
            // invalid input
            context.SetReturnValue(false);
        }
    }

}


SANDBOXE_NATIVE_DEF(__input_is_pressed) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    // TODO: we need a switch for this!
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) {
        context.SetReturnValue(Dynacoe::Input::IsPressed(std::string(arguments[0])));            
    } else {
        int input = arguments[0];

        if (input < 93) {
            context.SetReturnValue(Dynacoe::Input::IsPressed((Dynacoe::Keyboard)input));
        } else if (input < 96) {
            context.SetReturnValue(Dynacoe::Input::IsPressed((Dynacoe::MouseButtons)(input-93)));
        } else {
            // invalid input
            context.SetReturnValue(false);
        }
    }

}

SANDBOXE_NATIVE_DEF(__input_is_held) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    // TODO: we need a switch for this!
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) {
        context.SetReturnValue(Dynacoe::Input::IsHeld(std::string(arguments[0])));            
    } else {
        int input = arguments[0];

        if (input < 93) {
            context.SetReturnValue(Dynacoe::Input::IsHeld((Dynacoe::Keyboard)input));
        } else if (input < 96) {
            context.SetReturnValue(Dynacoe::Input::IsHeld((Dynacoe::MouseButtons)(input-93)));
        } else {
            // invalid input
            context.SetReturnValue(false);
        }
    }
  
}

SANDBOXE_NATIVE_DEF(__input_is_released) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    // TODO: we need a switch for this!
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) {
        context.SetReturnValue(Dynacoe::Input::IsReleased(std::string(arguments[0])));            
    } else {
        int input = arguments[0];

        if (input < 93) {
            context.SetReturnValue(Dynacoe::Input::IsReleased((Dynacoe::Keyboard)input));
        } else if (input < 96) {
            context.SetReturnValue(Dynacoe::Input::IsReleased((Dynacoe::MouseButtons)(input-93)));
        } else {
            // invalid input
            context.SetReturnValue(false);
        }
    }

}

SANDBOXE_NATIVE_DEF(__input_map_input) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    if (arguments[1].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) return;
    int input = arguments[1];
    if (input < 93) {
        Dynacoe::Input::MapInput(arguments[0], (Dynacoe::Keyboard)input);
    } else if (input < 96) {
        Dynacoe::Input::MapInput(arguments[0], (Dynacoe::MouseButtons)(input-93));
    } 
}

SANDBOXE_NATIVE_DEF(__input_unmap_input) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Input::UnmapInput(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__input_add_listener) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, ButtonListenerObject);
    
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];

    if (arguments[1].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::StringT) {
        Dynacoe::Input::AddListener(b, std::string(arguments[1]));            
    } else {
        int input = arguments[1];
        if (input < 93) {
            Dynacoe::Input::AddListener(b, (Dynacoe::Keyboard)input);
        } else if (input < 96) {
            Dynacoe::Input::AddListener(b, (Dynacoe::MouseButtons)(input-93));
        }
    }    
}

SANDBOXE_NATIVE_DEF(__input_remove_listener) {
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
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
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onPress)
        context.SetReturnValue(b->onPress);
}


SANDBOXE_NATIVE_DEF(__input_get_on_hold) {
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    if (b->onHold)
        context.SetReturnValue(b->onHold);
}

SANDBOXE_NATIVE_DEF(__input_get_on_release) {
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
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
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onPress = arguments[0];
    if (b->onPress && !b->onPress->IsCallable()) {
        b->onPress = nullptr;
        return;
    }
    b->AddNonNativeReference(b->onPress);
}

SANDBOXE_NATIVE_DEF(__input_set_on_hold) {
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceNonNativeT);
    b->onHold = arguments[0];
    if (b->onHold && !b->onHold->IsCallable()) {
        b->onHold = nullptr;
        return;
    }

    b->AddNonNativeReference(b->onHold);
}
 
SANDBOXE_NATIVE_DEF(__input_set_on_release) {
    auto b = (Sandboxe::ButtonListenerObject*)(Sandboxe::Script::Runtime::Object*)source;
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
        (int)Sandboxe::NativeType::ButtonListenerT,
        // users should populate:
        // 
        //  "onPress",
        //  "onHold",
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
            {"onHold", {__input_get_on_hold, __input_set_on_hold}},
            {"onRelease", {__input_get_on_release, __input_set_on_release}}


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
    

    fns.push_back({"__input_button_listener_new", __input_button_listener_new});
    fns.push_back({"__input_unicode_listener_new", __input_unicode_listener_new});
    fns.push_back({"__input_mouse_x", __input_mouse_x});
    fns.push_back({"__input_mouse_y", __input_mouse_y});
    fns.push_back({"__input_mouse_x_delta", __input_mouse_x_delta});
    fns.push_back({"__input_mouse_y_delta", __input_mouse_y_delta});
    fns.push_back({"__input_mouse_wheel", __input_mouse_wheel});
    fns.push_back({"__input_is_pressed", __input_is_pressed});
    fns.push_back({"__input_get_state", __input_get_state});
    fns.push_back({"__input_is_held", __input_is_held});
    fns.push_back({"__input_is_released", __input_is_released});
    fns.push_back({"__input_map_input", __input_map_input});
    fns.push_back({"__input_unmap_input", __input_unmap_input});
    //fns.push_back({"__input_add_listener", __input_add_listener});
    //fns.push_back({"__input_remove_listener", __input_remove_listener});
    fns.push_back({"__input_get_last_unicode", __input_get_last_unicode});
    fns.push_back({"__input_show_virtual_keyboard", __input_show_virtual_keyboard});
}

}
}



#endif
