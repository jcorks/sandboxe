#ifndef dynacoe_component_binding_sandboxe_included
#define dynacoe_component_binding_sandboxe_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/component.h>
#include <sandboxe/native/entity.h>
namespace Sandboxe {
namespace Bindings {




// native functions 

SANDBOXE_NATIVE_DEF(__component_draw) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_Draw();
}

SANDBOXE_NATIVE_DEF(__component_step) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_Step();
}


SANDBOXE_NATIVE_DEF(__component_install_event) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceNonNativeT);

    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_InstallEvent(
        arguments[0],
        arguments[1]
    );
}

SANDBOXE_NATIVE_DEF(__component_uninstall_event) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_UninstallEvent(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__component_emit_event) {
    Dynacoe::Entity::ID other;
    
    if (arguments.size() >= 2) {
        SANDBOXE_ASSERT__ARG_COUNT(2);
        SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceT);
        SANDBOXE_ASSERT__ARG_NATIVE(1, EntityObjectID);

        other = ((EntityObjectID*)((Sandboxe::Script::Runtime::Object*)arguments[1]))->id;

    } else if (arguments.size() < 1) {
        return;
    }
        
    // TODO: allow undefined
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_EmitEvent(
        arguments[0],
        other
    );
    
}


SANDBOXE_NATIVE_DEF(__component_can_handle_event) {
    SANDBOXE_ASSERT__ARG_COUNT(1);

    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    context.SetReturnValue(component->Native_CanHandleEvent(
        arguments[0]
    ));
    
}



SANDBOXE_NATIVE_DEF(__component_install_hook) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceNonNativeT);


    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_InstallHook(
        arguments[0],
        arguments[1]
    );
}

SANDBOXE_NATIVE_DEF(__component_uninstall_hook) {
    SANDBOXE_ASSERT__ARG_COUNT(1);

    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_UninstallHook(
        arguments[0]
    );
}



SANDBOXE_NATIVE_DEF(__component_install_handler) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceNonNativeT);

    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_InstallHandler(
        arguments[0],
        arguments[1]
    );
}

SANDBOXE_NATIVE_DEF(__component_uninstall_handler) {
    SANDBOXE_ASSERT__ARG_COUNT(1);

    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_UninstallHandler(
        arguments[0]
    );
}

SANDBOXE_NATIVE_DEF(__component_get_known_events) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    auto list = component->Native_GetKnownEvents();
    for(uint32_t i = 0; i < list.size(); ++i) {
        out.push_back(list[i]);
    }
    context.SetReturnArray(out);
}


// native properties 

SANDBOXE_NATIVE_DEF(__component_set_tag) {}
SANDBOXE_NATIVE_DEF(__component_get_tag) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    context.SetReturnValue(component->Native_GetTag());
}


SANDBOXE_NATIVE_DEF(__component_set_info) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_SetInfo(arguments[0]);
}
SANDBOXE_NATIVE_DEF(__component_get_info) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    context.SetReturnValue(component->Native_GetInfo());    
}

SANDBOXE_NATIVE_DEF(__component_set_draw) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_SetDraw(arguments[0]);
}
SANDBOXE_NATIVE_DEF(__component_get_draw) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    context.SetReturnValue(component->Native_GetDraw());    
}

SANDBOXE_NATIVE_DEF(__component_set_step) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    component->Native_SetStep(arguments[0]);
}
SANDBOXE_NATIVE_DEF(__component_get_step) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    context.SetReturnValue(component->Native_GetStep());    
}

// host cannot be set manually. It needs to be added to an entity using 
// entity.addComponent
SANDBOXE_NATIVE_DEF(__component_set_host) {}
SANDBOXE_NATIVE_DEF(__component_get_host) {
    auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>(source);
    Dynacoe::Entity::ID id = component->Native_GetHostID();
    Sandboxe::Entity * ent = id.IdentifyAs<Sandboxe::Entity>();
    
    if (!ent) return;
    context.SetReturnValue(
        ent
    );    
}







void dynacoe_component(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::ComponentT,

        // Functions
        {
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
        },

        // properties
        {
            
        },
        
        // native properties
        {
            {"tag", {__component_get_tag, __component_set_tag}},
            {"info", {__component_get_info, __component_set_info}},
            {"isStepping", {__component_get_step, __component_set_step}},
            {"isDrawing", {__component_get_draw, __component_set_draw}},
            {"host", {__component_get_host, __component_set_host}}
        }
    );

}


}
}



#endif
