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
    if (!e) SANDBOXE_NORETURN;
    e->Step();
    SANDBOXE_NORETURN;
}

SANDBOXE_NATIVE_DEF(__entity_draw) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) SANDBOXE_NORETURN;
    e->Draw();

    SANDBOXE_NORETURN;
}






// native properties
    
SANDBOXE_NATIVE_DEF(__entity_get_step) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) SANDBOXE_NORETURN;
    return e->step;
}

SANDBOXE_NATIVE_DEF(__entity_set_step) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e)
        SANDBOXE_NORETURN;
    e->step = arguments[0];
    SANDBOXE_NORETURN;
}

SANDBOXE_NATIVE_DEF(__entity_get_draw) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) 
        SANDBOXE_NORETURN;
            
    return e->draw;
    SANDBOXE_NORETURN;
}

SANDBOXE_NATIVE_DEF(__entity_set_draw) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e)
        SANDBOXE_NORETURN;
            
    e->draw = arguments[0];
    SANDBOXE_NORETURN;
}    

SANDBOXE_NATIVE_DEF(__entity_create_default) {
    Sandboxe::Script::Runtime::Object * object = new Sandboxe::Script::Runtime::Object("entity");
    Dynacoe::Entity::ID id = Dynacoe::Entity::Create<Sandboxe::Entity>(); // todo: replace with special draw/run/mapped
    id.IdentifyAs<Sandboxe::Entity>()->SetObjectSource(object);
    id.Identify()->SetName("SANDBOXE");
    object->SetNativeAddress((void*)id.Value());
    context.SetReturnObject(object);
    SANDBOXE_NORETURN;
}




void dynacoe_entity(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        "entity",
        // methods
        {
            {"draw", __entity_draw},
            {"step", __entity_step},
        },
        // properties
        {

        },
        
        // managed properties,
        {
            {"isStepping", {__entity_get_step, __entity_set_step}},
            {"isDrawing", {__entity_get_draw, __entity_set_draw}}
        }
    );
    
    fns.push_back({"__entity_create_default", __entity_create_default});    
}
    
}
}





#endif