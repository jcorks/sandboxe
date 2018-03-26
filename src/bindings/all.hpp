#ifndef h_sandboxe_bindings_all_included
#define h_sandboxe_bindings_all_included

// all includes
#include "binding_helpers.h"
#include "dynacoe_console.hpp"
#include "dynacoe_entity.hpp"


namespace Sandboxe {
namespace Script {
void BindAll(v8::Handle<v8::ObjectTemplate> & context) {
    SANDBOXE_BINDSET_CALL(Sandboxe::Bindings::definitions__console);
    SANDBOXE_BINDSET_CALL(Sandboxe::Bindings::definitions__entity);
}    
}
}

#endif