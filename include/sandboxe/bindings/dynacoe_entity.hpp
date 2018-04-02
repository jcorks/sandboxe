#ifndef H_sandboxe_bindings_entity
#define H_sandboxe_bindings_entity

#include "binding_helpers.h"
#include <sandboxe/entity/entity.h>


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

    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;

    
    Dynacoe::Entity::ID other((uint64_t)((Sandboxe::Script::Runtime::Object*)arguments[0])->GetNativeAddress(Index_EntityID));
    e->Attach(other);
}

SANDBOXE_NATIVE_DEF(__entity_detach) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);

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



SANDBOXE_NATIVE_DEF(__entity_create_default) {
    Sandboxe::Script::Runtime::Object * object = new Sandboxe::Script::Runtime::Object("entity");
    Dynacoe::Entity::ID id = Dynacoe::Entity::Create<Sandboxe::Entity>(); // todo: replace with special draw/run/mapped
    id.IdentifyAs<Sandboxe::Entity>()->SetObjectSource(object);
    id.Identify()->SetName("SANDBOXE");
    object->SetNativeAddress((void*)id.Value());
    context.SetReturnValue(object);
}




void dynacoe_entity(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        "entity",
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
            {"getChildren", __entity_get_children}
        },
        // properties
        {
            
        },
        
        // managed properties,
        {
            {"isStepping", {__entity_get_step, __entity_set_step}},
            {"isDrawing", {__entity_get_draw, __entity_set_draw}},
            {"id", {__entity_get_id, __entity_set_id}}
        }
    );
    
    fns.push_back({"__entity_create_default", __entity_create_default});    
}
    
}
}





#endif