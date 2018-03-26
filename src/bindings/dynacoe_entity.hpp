#ifndef H_sandboxe_bindings_entity
#define H_sandboxe_bindings_entity

#include "binding_helpers.h"



namespace Sandboxe {
namespace Bindings {
    
SANDBOXE_OBJECT_GET_DEF(__entity_get_step) {
    SANDBOXE_SCOPE;
    SANDBOXE_OBJECT_RETRIEVE(ent);
    Dynacoe::Entity * e = Dynacoe::Entity::ID(SANDBOXE_OBJECT_GET(ent, "__ref")).Identify();
    if (!e) 
        SANDBOXE_NORETURN;
            
    return SANDBOXE_VALUE(Dynacoe::Chain() << e->step);
}
    

SANDBOXE_BIND_DEF(__entity_create_default) {
    SANDBOXE_SCOPE;
    
    SANDBOXE_OBJECT_CREATE(ent);
    Dynacoe::Entity::ID id = Dynacoe::Entity::Create();
    SANDBOXE_OBJECT_BIND_ATTRIBUTE(ent, "step", __entity_get_step, 0);//__entity_set_step);
    SANDBOXE_OBJECT_SET(ent, "__ref", id.String().c_str());

    return ent->NewInstance();
}




SANDBOXE_BINDSET_DEF(definitions__entity) {
    SANDBOXE_BIND_CALL("__entity_create_default", __entity_create_default);
    
    
}
    
}
}





#endif