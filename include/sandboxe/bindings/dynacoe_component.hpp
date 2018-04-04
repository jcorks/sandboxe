#ifndef dynacoe_component_binding_sandboxe_included
#define dynacoe_component_binding_sandboxe_included

#include <sandboxe/bindings/binding_helpers.h>
#include <sandboxe/component/component.h>
#include <sandboxe/entity/entity.h>
namespace Sandboxe {
namespace Bindings {


// helpers 
static Sandboxe::Component * __component_new(const std::string & tag, const std::string & info) {
    Sandboxe::Script::Runtime::Object * object = new Sandboxe::Script::Runtime::Object("component");
    Sandboxe::Component * component = new Sandboxe::Component(tag, info); 
    component->SetObjectSource(object);
    object->SetNativeAddress(component);
    return component;
}

// native functions 

SANDBOXE_NATIVE_DEF(__component_draw) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->Draw();
}

SANDBOXE_NATIVE_DEF(__component_step) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->Step();
}


SANDBOXE_NATIVE_DEF(__component_install_event) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceNonNativeT);

    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->InstallEvent_Sandboxe(
        arguments[0],
        arguments[1]
    );
}

SANDBOXE_NATIVE_DEF(__component_uninstall_event) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->UninstallEvent_Sandboxe(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__component_emit_event) {
    SANDBOXE_ASSERT__ARG_COUNT(2);

    // TODO: allow undefined
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceT);
    Dynacoe::Entity::ID other((uint64_t)((Sandboxe::Script::Runtime::Object*)arguments[1])->GetNativeAddress());
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->EmitEvent(
        arguments[0],
        other
    );
    
}


SANDBOXE_NATIVE_DEF(__component_can_handle_event) {
    SANDBOXE_ASSERT__ARG_COUNT(1);

    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    context.SetReturnValue(component->CanHandleEvent(
        arguments[0]
    ));
    
}



SANDBOXE_NATIVE_DEF(__component_install_hook) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceNonNativeT);

    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->InstallHook_Sandboxe(
        arguments[0],
        arguments[1]
    );
}

SANDBOXE_NATIVE_DEF(__component_uninstall_hook) {
    SANDBOXE_ASSERT__ARG_COUNT(1);

    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->UninstallHook(
        arguments[0],
        Sandboxe::Component::NativeHandler
    );
}



SANDBOXE_NATIVE_DEF(__component_install_handler) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceNonNativeT);

    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->InstallHandler_Sandboxe(
        arguments[0],
        arguments[1]
    );
}

SANDBOXE_NATIVE_DEF(__component_uninstall_handler) {
    SANDBOXE_ASSERT__ARG_COUNT(1);

    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->UninstallHandler(
        arguments[0],
        Sandboxe::Component::NativeHandler
    );
}

SANDBOXE_NATIVE_DEF(__component_get_known_events) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    auto list = component->GetKnownEvents();
    for(uint32_t i = 0; i < list.size(); ++i) {
        out.push_back(list[i]);
    }
    context.SetReturnArray(out);
}


// native properties 

SANDBOXE_NATIVE_DEF(__component_set_tag) {}
SANDBOXE_NATIVE_DEF(__component_get_tag) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    context.SetReturnValue(component->GetTag());
}


SANDBOXE_NATIVE_DEF(__component_set_info) {}
SANDBOXE_NATIVE_DEF(__component_get_info) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    context.SetReturnValue(component->GetInfo());    
}

SANDBOXE_NATIVE_DEF(__component_set_draw) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->draw = arguments[0];
}
SANDBOXE_NATIVE_DEF(__component_get_draw) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    context.SetReturnValue(component->draw);    
}

SANDBOXE_NATIVE_DEF(__component_set_step) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    component->step = arguments[0];
}
SANDBOXE_NATIVE_DEF(__component_get_step) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    context.SetReturnValue(component->step);    
}

// host cannot be set manually. It needs to be added to an entity using 
// entity.addComponent
SANDBOXE_NATIVE_DEF(__component_set_host) {}
SANDBOXE_NATIVE_DEF(__component_get_host) {
    Sandboxe::Component * component = (Sandboxe::Component *)source->GetNativeAddress();
    Dynacoe::Entity::ID id = component->GetHostID();
    Sandboxe::Entity * ent = id.IdentifyAs<Sandboxe::Entity>();
    
    if (!ent) return;
    context.SetReturnValue(
        ent->GetObjectSource()
    );    
}




//// global functions 
SANDBOXE_NATIVE_DEF(__component_create) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    context.SetReturnValue(
        __component_new(
            arguments[0],
            arguments[1]        
        )->GetObjectSource()
    );
}


void dynacoe_component(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        "component",
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
    
    fns.push_back({"__component_create", __component_create});
}


}
}



#endif