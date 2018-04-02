#ifndef H_sandboxe_bindings_entity_id
#define H_sandboxe_bindings_entity_id

#include "binding_helpers.h"



namespace Sandboxe {
namespace Bindings {
    
#define Index_EntityID 0
    
SANDBOXE_NATIVE_DEF(__entity_get_step) {
    Dynacoe::Entity::ID id((uint64_t)source->GetNativeAddress(Index_EntityID));
    Dynacoe::Entity * e = id.Identify();
    if (!e) SANDBOXE_NORETURN;
    return e->step;
}





void dynacoe_entity_id(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        "entityid",
        {
            {"value",    __entity_id_value},
            {"identify", __entity_id_identify},
            {"string",   __entity_id_string},
            {"valid",    __entity_id_value}
        },
        // properties
        {
            
        },
        
        // managed properties,
        {

        }
    );
    
    fns.push_back({"__entity_create_default", __entity_create_default});    
}
    
}
}





#endif