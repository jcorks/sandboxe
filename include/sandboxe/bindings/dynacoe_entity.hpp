#ifndef H_sandboxe_bindings_entity
#define H_sandboxe_bindings_entity

#include <sandboxe/native/native.h>
#include <sandboxe/native/entity.h>
#include <sandboxe/native/component.h>

/*
    Dynacoe::Entity class bindings.
    Notes:
        - Entity::ID and Entity are one object in scripting
        - The variable interface is currently not supported
        - QueryComponent instead gets the component of the given tag


 */





namespace Sandboxe {
namespace Bindings {
    
#define Index_EntityID 0






// methods 

SANDBOXE_NATIVE_DEF(__entity_step) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    e->Step();
}

SANDBOXE_NATIVE_DEF(__entity_draw) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    e->Draw();

}

SANDBOXE_NATIVE_DEF(__entity_valid) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    context.SetReturnValue(id.Valid());
}

SANDBOXE_NATIVE_DEF(__entity_remove) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;
    e->Remove();
}

SANDBOXE_NATIVE_DEF(__entity_attach) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, EntityIDT);

    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    
    Dynacoe::Entity::ID other((uint64_t)((Sandboxe::Script::Runtime::Object*)arguments[0])->GetNativeAddress(Index_EntityID));
    e->Attach(other);
}

SANDBOXE_NATIVE_DEF(__entity_detach) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, EntityIDT);


    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;
    
    Dynacoe::Entity::ID other((uint64_t)((Sandboxe::Script::Runtime::Object*)arguments[0])->GetNativeAddress(Index_EntityID));
    e->Detach(other);
}

SANDBOXE_NATIVE_DEF(__entity_get_num_children) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue(e->GetNumChildren());
}

SANDBOXE_NATIVE_DEF(__entity_contains) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, EntityIDT);

    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;
    
    Dynacoe::Entity::ID other((uint64_t)((Sandboxe::Script::Runtime::Object*)arguments[0])->GetNativeAddress(Index_EntityID));
    context.SetReturnValue(e->Contains(other));
}

SANDBOXE_NATIVE_DEF(__entity_get_children) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto list = e->GetChildren();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < list.size(); ++i) {
        out.push_back(list[i].IdentifyAs<Sandboxe::Entity>()->GetObjectSource());
    }
    
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__entity_get_all_sub_entities) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto list = e->GetAllSubEntities();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < list.size(); ++i) {
        out.push_back(list[i].IdentifyAs<Sandboxe::Entity>()->GetObjectSource());
    }
    
    context.SetReturnArray(out);
}


SANDBOXE_NATIVE_DEF(__entity_find_child_by_name) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto list = e->FindChildByName(arguments[0]);
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < list.size(); ++i) {
        out.push_back(list[i].IdentifyAs<Sandboxe::Entity>()->GetObjectSource());
    }
    
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__entity_create_child) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::EntityIDT);
    Sandboxe::Entity * child = Dynacoe::Entity::ID((uint64_t)Sandboxe::NativeObject::Get<void>(object)).IdentifyAs<Sandboxe::Entity>();


    e->Attach(child->GetID());
    context.SetReturnValue(
        object
    );
}



SANDBOXE_NATIVE_DEF(__entity_draw_duration) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue(e->DrawDuration());
}

SANDBOXE_NATIVE_DEF(__entity_step_duration) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue(e->StepDuration());
}

SANDBOXE_NATIVE_DEF(__entity_set_priority) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->SetPriority((int)arguments[0]);
}

SANDBOXE_NATIVE_DEF(__entity_get_priority) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue((int)e->GetPriority());
}

SANDBOXE_NATIVE_DEF(__entity_set_priority_last) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->SetPriorityLast();
}

SANDBOXE_NATIVE_DEF(__entity_set_priority_first) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->SetPriorityFirst();
}


SANDBOXE_NATIVE_DEF(__entity_get_parent) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    if (!e->HasParent()) return;
    context.SetReturnValue(
        dynamic_cast<Sandboxe::Entity*>(&e->GetParent())->GetObjectSource()
    );
}


SANDBOXE_NATIVE_DEF(__entity_has_parent) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue(e->HasParent());
}

SANDBOXE_NATIVE_DEF(__entity_add_component) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;


    if (arguments.size() < 1) {
        SANDBOXE_ASSERT__ARG_COUNT(2);        
    }
    
    Sandboxe::ComponentAdaptor * component;
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    component = (Sandboxe::ComponentAdaptor *)((Sandboxe::Script::Runtime::Object*)arguments[0])->GetNativeAddress();

    if (arguments.size() >= 2) {
        e->AddComponent(component->Native_GetDynacoeComponent(), (Dynacoe::Entity::UpdateClass)(int)arguments[1]);
    } else {        
        e->AddComponent(component->Native_GetDynacoeComponent());
    }    
}

SANDBOXE_NATIVE_DEF(__entity_query_component) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    std::string t = arguments[0];
    auto list = e->GetComponents();
    for(uint32_t i = 0; i < list.size(); ++i) {
        if (list[i]->GetTag() == t) {
            context.SetReturnValue(((Sandboxe::ComponentAdaptor*)list[i])->GetObjectSource());
        }
    }
}


SANDBOXE_NATIVE_DEF(__entity_get_components) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    std::vector<Sandboxe::Script::Runtime::Primitive> list;
    auto components = e->GetComponents();
    for(uint32_t i = 0; i < components.size(); ++i) {
        list.push_back((dynamic_cast<Sandboxe::ComponentAdaptor*>(components[i]))->GetObjectSource());
    }
    
    context.SetReturnArray(list);
}

SANDBOXE_NATIVE_DEF(__entity_remove_component) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->RemoveComponent(std::string(arguments[0]));
}











// native properties
    
SANDBOXE_NATIVE_DEF(__entity_get_step) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    context.SetReturnValue(e->step);
}

SANDBOXE_NATIVE_DEF(__entity_set_step) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    e->step = arguments[0];
}

SANDBOXE_NATIVE_DEF(__entity_get_draw) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    context.SetReturnValue(e->draw);
}

SANDBOXE_NATIVE_DEF(__entity_set_draw) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    e->draw = arguments[0];
}    


SANDBOXE_NATIVE_DEF(__entity_get_id) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    context.SetReturnValue(id.Value());
}

SANDBOXE_NATIVE_DEF(__entity_set_id) {}


SANDBOXE_NATIVE_DEF(__entity_get_name) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    context.SetReturnValue(e->GetName());
}

SANDBOXE_NATIVE_DEF(__entity_set_name) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    e->SetName(arguments[0]);
}



/// global functions

SANDBOXE_NATIVE_DEF(__entity_create_default) {
    context.SetReturnValue(Sandboxe::NativeObject::New(Sandboxe::NativeType::EntityIDT));
}

SANDBOXE_NATIVE_DEF(__entity_get_all) {
    auto list = Dynacoe::Entity::GetAll();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    Sandboxe::Entity * e;
    for(uint32_t i = 0; i < list.size(); ++i) {
        e = list[i].IdentifyAs<Sandboxe::Entity>();
        if (!e) continue;
        out.push_back(e->GetObjectSource());
    }
    context.SetReturnArray(out);
}





void dynacoe_entity(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        Sandboxe::NativeTypeToString(Sandboxe::NativeType::EntityIDT),
        // methods
        {
            {"draw", __entity_draw},
            {"step", __entity_step},
            {"valid", __entity_valid},
            {"remove", __entity_remove},

            {"attach", __entity_attach},
            {"detach", __entity_detach},

            {"getNumChildren", __entity_get_num_children},
            {"contains", __entity_contains},
            {"getChildren", __entity_get_children},
            {"getAllSubEntities", __entity_get_all_sub_entities},
            {"findChildByName", __entity_find_child_by_name},
            {"createChild", __entity_create_child},

            {"stepDuration", __entity_step_duration},
            {"drawDuration", __entity_draw_duration},

            {"setPriority", __entity_set_priority},
            {"setPriorityLast", __entity_set_priority_last},
            {"setPriorityFirst", __entity_set_priority_first},
            {"getPriority", __entity_get_priority},
            
            {"getParent", __entity_get_parent},
            {"hasParent", __entity_has_parent},
            
            {"addComponent", __entity_add_component},
            {"queryComponent", __entity_query_component},
            {"getComponents", __entity_get_components},
            {"removeComponent", __entity_remove_component}
            
        },
        // properties
        {

        },
        
        // managed properties,
        {
            {"isStepping", {__entity_get_step, __entity_set_step}},
            {"isDrawing", {__entity_get_draw, __entity_set_draw}},
            {"id", {__entity_get_id, __entity_set_id}},
            {"name", {__entity_get_name, __entity_set_name}}
        }
    );
    
    fns.push_back({"__entity_create_default", __entity_create_default});    
    fns.push_back({"__entity_get_all", __entity_get_all});    

}
    
}
}





#endif