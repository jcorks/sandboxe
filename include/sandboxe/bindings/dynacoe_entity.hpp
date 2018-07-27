#ifndef H_sandboxe_bindings_entity
#define H_sandboxe_bindings_entity

#include <sandboxe/native/native.h>
#include <sandboxe/native/entity.h>
#include <sandboxe/native/component.h>
#include <sandboxe/native/transform.h>

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
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    e->Step();
}

SANDBOXE_NATIVE_DEF(__entity_draw) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    e->Draw();

}

SANDBOXE_NATIVE_DEF(__entity_valid) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    context.SetReturnValue(id.Valid());
}

SANDBOXE_NATIVE_DEF(__entity_remove) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;
    e->Remove();
}

SANDBOXE_NATIVE_DEF(__entity_attach) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, EntityObjectID);

    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    
    const Dynacoe::Entity::ID & other = ((EntityObjectID*)((Sandboxe::Script::Runtime::Object*)arguments[0]))->id;
    e->Attach(other);
}

SANDBOXE_NATIVE_DEF(__entity_detach) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, EntityObjectID);


    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;
    
    const Dynacoe::Entity::ID & other = ((EntityObjectID*)((Sandboxe::Script::Runtime::Object*)arguments[0]))->id;
    e->Detach(other);
}

SANDBOXE_NATIVE_DEF(__entity_get_num_children) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto list = e->GetChildren();
    uint32_t realCount = 0;
    for(uint32_t i = 0; i < list.size(); ++i) {
        auto child = list[i].IdentifyAs<Sandboxe::Entity>();
        if (!child) continue; // hidden
        realCount++;
    }

    context.SetReturnValue(realCount);
}

SANDBOXE_NATIVE_DEF(__entity_contains) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, EntityObjectID);

    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;
    
    const Dynacoe::Entity::ID & other = ((EntityObjectID*)((Sandboxe::Script::Runtime::Object*)arguments[0]))->id;
    context.SetReturnValue(e->Contains(other));
}

SANDBOXE_NATIVE_DEF(__entity_get_children) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto list = e->GetChildren();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < list.size(); ++i) {
        auto child = list[i].IdentifyAs<Sandboxe::Entity>();
        if (!child) continue; // hidden
        out.push_back(child->object);
    }
    
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__entity_get_all_sub_entities) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto list = e->GetAllSubEntities();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < list.size(); ++i) {
        auto child = list[i].IdentifyAs<Sandboxe::Entity>();
        if (!child) continue; //hidden
        out.push_back(child->object);
    }
    
    context.SetReturnArray(out);
}


SANDBOXE_NATIVE_DEF(__entity_find_child_by_name) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto list = e->FindChildByName(arguments[0]);
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < list.size(); ++i) {
        auto ent = list[i].IdentifyAs<Sandboxe::Entity>();
        if (!ent) continue;
        out.push_back(ent->object);
    }
    
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__entity_create_child) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    auto object = new Sandboxe::EntityObjectID();
    Sandboxe::Entity * child = object->id.IdentifyAs<Sandboxe::Entity>();


    e->Attach(child->GetID());
    context.SetReturnValue(
        object
    );
}



SANDBOXE_NATIVE_DEF(__entity_draw_duration) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue(e->DrawDuration());
}

SANDBOXE_NATIVE_DEF(__entity_step_duration) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue(e->StepDuration());
}

SANDBOXE_NATIVE_DEF(__entity_set_priority) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->SetPriority((int)arguments[0]);
}

SANDBOXE_NATIVE_DEF(__entity_get_priority) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue((int)e->GetPriority());
}

SANDBOXE_NATIVE_DEF(__entity_set_priority_last) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->SetPriorityLast();
}

SANDBOXE_NATIVE_DEF(__entity_set_priority_first) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->SetPriorityFirst();
}


SANDBOXE_NATIVE_DEF(__entity_get_parent) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    if (!e->HasParent()) return;
    context.SetReturnValue(
        dynamic_cast<Sandboxe::Entity*>(&e->GetParent())->object
    );
}


SANDBOXE_NATIVE_DEF(__entity_has_parent) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    context.SetReturnValue(e->HasParent());
}

SANDBOXE_NATIVE_DEF(__entity_add_component) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    if (arguments.size() < 1) {
        SANDBOXE_ASSERT__ARG_COUNT(2);        
    }

    Dynacoe::Entity::UpdateClass when = Dynacoe::Entity::UpdateClass::Before;
    if (arguments.size() >= 2) {
        when = (Dynacoe::Entity::UpdateClass)(int)arguments[1];
    }
    //SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    //SANDBOXE_ASSERT__ARG_NATIVE(0, ComponentAdaptor);
    //auto component = dynamic_cast<Sandboxe::ComponentAdaptor *>((Sandboxe::Script::Runtime::Object*)arguments[0]);

    Sandboxe::ComponentAdaptor * out = nullptr;
    Sandboxe::ComponentType type = (Sandboxe::ComponentType)(int)arguments[0]);
    switch(type) {
      case COMPONENT_TYPE__CLOCK:      out = e->AddComponent<Sandboxe::ClockObject>(when); break;
      case COMPONENT_TYPE__DATA_TABLE: out = e->AddComponent<Sandboxe::DataTableObject>(when); break;
      case COMPONENT_TYPE__GUI:        out = e->AddComponent<Sandboxe::GUIObject>(when); break;
      case COMPONENT_TYPE__MUTATOR:    out = e->AddComponent<Sandboxe::MutatorObject>(when); break;
      case COMPONENT_TYPE__OBJECT2D:   out = e->AddComponent<Sandboxe::Object2DObject>(when); break;
      case COMPONENT_TYPE__RENDERLIGHT:out = e->AddComponent<Sandboxe::RenderLightObject>(when); break;
      case COMPONENT_TYPE__RENDERMESH :out = e->AddComponent<Sandboxe::RenderMeshObject>(when); break;
      case COMPONENT_TYPE__SCHEDULER:  out = e->AddComponent<Sandboxe::SchedulerObject>(when); break;
    }
    

    if (arguments.size() >= 2) {
        e->AddComponent(component->Native_GetDynacoeComponent(), ]);
    } else {        
        e->AddComponent(component->Native_GetDynacoeComponent());
    }    
}


SANDBOXE_NATIVE_DEF(__entity_add);

SANDBOXE_NATIVE_DEF(__entity_query_component) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    std::string t = arguments[0];
    auto list = e->GetComponents();
    for(uint32_t i = 0; i < list.size(); ++i) {
        if (list[i]->GetTag() == t) {
            context.SetReturnValue(dynamic_cast<ComponentAdaptor*>(list[i]));
        }
    }
}


SANDBOXE_NATIVE_DEF(__entity_get_components) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    std::vector<Sandboxe::Script::Runtime::Primitive> list;
    auto components = e->GetComponents();
    for(uint32_t i = 0; i < components.size(); ++i) {
        list.push_back(dynamic_cast<Sandboxe::ComponentAdaptor*>(components[i]));
    }
    
    context.SetReturnArray(list);
}

SANDBOXE_NATIVE_DEF(__entity_remove_component) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    e->RemoveComponent(std::string(arguments[0]));
}











// native properties
    
SANDBOXE_NATIVE_DEF(__entity_get_step) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    context.SetReturnValue(e->step);
}

SANDBOXE_NATIVE_DEF(__entity_set_step) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;
    e->step = arguments[0];
}

SANDBOXE_NATIVE_DEF(__entity_get_draw) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    context.SetReturnValue(e->draw);
}

SANDBOXE_NATIVE_DEF(__entity_set_draw) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    e->draw = arguments[0];
}    


SANDBOXE_NATIVE_DEF(__entity_get_id) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    context.SetReturnValue(id.Value());
}

SANDBOXE_NATIVE_DEF(__entity_set_id) {}


SANDBOXE_NATIVE_DEF(__entity_get_node) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    auto * e = id.IdentifyAs<Sandboxe::Entity>();
    if (!e) return;            
    context.SetReturnValue(e->transform);
}

SANDBOXE_NATIVE_DEF(__entity_set_node) {}


SANDBOXE_NATIVE_DEF(__entity_get_name) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    context.SetReturnValue(e->GetName());
}

SANDBOXE_NATIVE_DEF(__entity_set_name) {
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();
    if (!e) return;            
    e->SetName(arguments[0]);
}



/// global functions

SANDBOXE_NATIVE_DEF(__entity_create_default) {
    context.SetReturnValue(new Sandboxe::EntityObjectID);
}

SANDBOXE_NATIVE_DEF(__entity_get_all) {
    auto list = Dynacoe::Entity::GetAll();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    Sandboxe::Entity * e;
    for(uint32_t i = 0; i < list.size(); ++i) {
        e = list[i].IdentifyAs<Sandboxe::Entity>();
        if (!e) continue; // hidden
        out.push_back(e->object);
    }
    context.SetReturnArray(out);
}





void dynacoe_entity(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::EntityIDT,
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
            {"add", __entity_add},

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
            {"name", {__entity_get_name, __entity_set_name}},
            {"node", {__entity_get_node, __entity_set_node}}
        }
    );
    
    fns.push_back({"__entity_create_default", __entity_create_default});    
    fns.push_back({"__entity_get_all", __entity_get_all});    

}
    
}
}





#endif