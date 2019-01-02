#ifndef H_sandboxe_bindings_particle_emitter_2d
#define H_sandboxe_bindings_particle_emitter_2d

#include <sandboxe/native/native.h>
#include <sandboxe/native/particleEmitter2d.h>
#include <sandboxe/native/component.h>

/*
    Dynacoe::ParticleEmitter2D class bindings.
    
    Notes:
        - enable* are now r/w booleans 
            - 

 */





namespace Sandboxe {
namespace Bindings {
    




// methods 
SANDBOXE_NATIVE_DEF(__particle_emitter_2d_emit_particle) {   
    if (!arguments.size()) return;
    int n = 1;
    if (arguments.size() > 1) {
        n = arguments[1];
    }
    
    
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, AssetIDObject);
    
     
    auto pe = ((ParticleEmitter2DEntityID*)source)->id.IdentifyAs<Sandboxe::ParticleEmitter2D>();
    if (!pe) return;
    Sandboxe::AssetIDObject * id = (Sandboxe::AssetIDObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    if (!id) return;
    
    auto real = pe->realEmitter.IdentifyAs<Dynacoe::ParticleEmitter2D>();
    real->EmitParticle(id->id, n);

}






// properties

SANDBOXE_NATIVE_DEF(__particle_emitter_2d_get_filtered) {
    auto pe = ((ParticleEmitter2DEntityID*)source)->id.IdentifyAs<Sandboxe::ParticleEmitter2D>();
    if (!pe) return;
    context.SetReturnValue(pe->localFiltered);
}

SANDBOXE_NATIVE_DEF(__particle_emitter_2d_get_translucent) {
    auto pe = ((ParticleEmitter2DEntityID*)source)->id.IdentifyAs<Sandboxe::ParticleEmitter2D>();
    if (!pe) return;
    context.SetReturnValue(pe->localTransluscent);
}

SANDBOXE_NATIVE_DEF(__particle_emitter_2d_set_filtered) {
    auto pe = ((ParticleEmitter2DEntityID*)source)->id.IdentifyAs<Sandboxe::ParticleEmitter2D>();
    if (!pe) return;
    pe->localFiltered = arguments[0];
    auto self = pe->Self();
    if (!self) return;
    self->EnableFiltering(pe->localFiltered);
}

SANDBOXE_NATIVE_DEF(__particle_emitter_2d_set_translucent) {
    auto pe = ((ParticleEmitter2DEntityID*)source)->id.IdentifyAs<Sandboxe::ParticleEmitter2D>();
    if (!pe) return;
    pe->localTransluscent = arguments[0];
    auto self = pe->Self();
    if (!self) return;
    self->EnableTranslucency(pe->localTransluscent);
}


SANDBOXE_NATIVE_DEF(__particle_emitter_2d_create) {
    context.SetReturnValue(new Sandboxe::ParticleEmitter2DEntityID());
}





void dynacoe_particle_emitter_2d(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::ParticleEmitter2D_EntityIDT,
        // methods
        {
            {"emitParticle", __particle_emitter_2d_emit_particle},

            //////// inherited from entity
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
            ////////// inherited from entity
            
        },
        // properties
        {

        },
        
        // managed properties,
        {
            {"filtered", {__particle_emitter_2d_get_filtered, __particle_emitter_2d_set_filtered}},
            {"translucent", {__particle_emitter_2d_get_translucent, __particle_emitter_2d_set_translucent}},

            //////// inherited from entity
            {"isStepping", {__entity_get_step, __entity_set_step}},
            {"isDrawing", {__entity_get_draw, __entity_set_draw}},
            {"id", {__entity_get_id, __entity_set_id}},
            {"name", {__entity_get_name, __entity_set_name}},
            {"node", {__entity_get_node, __entity_set_node}}

            ///////// inherited from entity
        }
    );
    fns.push_back({"__particle_emitter_2d_create", __particle_emitter_2d_create});

}
    
}
}





#endif
