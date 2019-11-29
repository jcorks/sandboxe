#ifndef dynacoe_object2d_sandboxe_binding_included
#define dynacoe_object2d_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/object2d.h>
#include <sandboxe/bindings/dynacoe_component.hpp>

/*

    Dynacoe::Object2D bindings 

    Notes:
        - GetSetSpeed() are now just the speed property
        - Friction is a public property
        - Only one contact poly allowed per through setContactPoly()/setContactBox() 
        - not yet implementing GetContactPoly
    

*/


namespace Sandboxe {
namespace Bindings {








    

// managed properties

SANDBOXE_NATIVE_DEF(__object2d_add_velocity) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto o2d = (Sandboxe::Object2DObject*)source; 
	assert(o2d->GetHostID().Valid());
    o2d->AddVelocity(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__object2d_add_velocity_towards) {
    if (arguments.size() < 2) 
        SANDBOXE_ASSERT__ARG_COUNT(2);
    Dynacoe::Vector v;
    argument_to_vector_object(v, arguments[1]);    
    auto o2d = (Sandboxe::Object2DObject*)source;         
    o2d->AddVelocityTowards(arguments[0], v, arguments.size() > 2 ? (float)arguments[2] : 0.f);
}


SANDBOXE_NATIVE_DEF(__object2d_set_velocity) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->SetVelocity(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__object2d_set_velocity_towards) {
    if (arguments.size() < 2) 
        SANDBOXE_ASSERT__ARG_COUNT(2);
    Dynacoe::Vector v;
    argument_to_vector_object(v, arguments[1]);    
    auto o2d = (Sandboxe::Object2DObject*)source;         
    o2d->SetVelocityTowards(arguments[0], v, arguments.size() > 2 ? (float)arguments[2] : 0.f);
}


SANDBOXE_NATIVE_DEF(__object2d_set_collider) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    auto args = context.GetArrayArgument(0);
    if (!args) {
        Sandboxe::Script::Runtime::ScriptError("Expected array of numbers for collider polygon x,y position pairs.");
        return; 
    }

    std::vector<Dynacoe::Vector> pts;
    o2d->colliderData.clear();
    for(uint32_t i = 0; i < args->size()/2; ++i) {
        Dynacoe::Vector next;
        next.x = (*args)[i*2];
        next.y = (*args)[i*2+1];
        pts.push_back(next);
        o2d->colliderData.push_back(next.x);
        o2d->colliderData.push_back(next.y);

    }

    o2d->collider = (pts);
}

SANDBOXE_NATIVE_DEF(__object2d_get_collider) {
    auto o2d = (Sandboxe::Object2DObject*)source;
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < o2d->colliderData.size(); ++i) {
        out.push_back(o2d->colliderData[i]);        
    }
    context.SetReturnArray(out);
}





//// manged propertiess

SANDBOXE_NATIVE_DEF(__object2d_get_friction_x) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    context.SetReturnValue(o2d->frictionX);
}

SANDBOXE_NATIVE_DEF(__object2d_set_friction_x) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->frictionX = arguments[0];
    o2d->SetFrictionX(o2d->frictionX);
}


SANDBOXE_NATIVE_DEF(__object2d_get_friction_y) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    context.SetReturnValue(o2d->frictionY);
}

SANDBOXE_NATIVE_DEF(__object2d_set_friction_y) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->frictionY = arguments[0];
    o2d->SetFrictionY(o2d->frictionY);
}

SANDBOXE_NATIVE_DEF(__object2d_get_speed) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    context.SetReturnValue(o2d->GetSpeed());
}

SANDBOXE_NATIVE_DEF(__object2d_set_speed) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->SetSpeed(arguments[0]);    
}

SANDBOXE_NATIVE_DEF(__object2d_get_direction) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    context.SetReturnValue(o2d->GetDirection());
}

SANDBOXE_NATIVE_DEF(__object2d_halt) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->Halt();
}


SANDBOXE_NATIVE_DEF(__object2d_reset_motion) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->ResetMotion();
}

SANDBOXE_NATIVE_DEF(__object2d_egi_group) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->EnableGroupInteraction(
        (Dynacoe::Object2D::Group)(int)arguments[0],
        (Dynacoe::Object2D::Group)(int)arguments[1]
    );
}

SANDBOXE_NATIVE_DEF(__object2d_dgi_group) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->DisableGroupInteraction(
        (Dynacoe::Object2D::Group)(int)arguments[0],
        (Dynacoe::Object2D::Group)(int)arguments[1]
    );
}


SANDBOXE_NATIVE_DEF(__object2d_get_velocity_x) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    context.SetReturnValue(o2d->GetVelocityX());
}

SANDBOXE_NATIVE_DEF(__object2d_get_velocity_y) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    context.SetReturnValue(o2d->GetVelocityY());
}


SANDBOXE_NATIVE_DEF(__object2d_set_velocity_x) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->SetVelocityX(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__object2d_set_velocity_y) {
    auto o2d = (Sandboxe::Object2DObject*)source;    
    o2d->SetVelocityY(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__object2d_get_last_collided) {
    auto o2d = (Sandboxe::Object2DObject*)source;        
    auto a = o2d->collider.lastCollided.IdentifyAs<Sandboxe::Entity>();
    if (!a) return;
    context.SetReturnValue(a);
}

SANDBOXE_NATIVE_DEF(__object2d_get_next_position) {
    auto o2d = (Sandboxe::Object2DObject*)source;        
    context.SetReturnValue(new Sandboxe::VectorObject(o2d->GetNextPosition()));
}

SANDBOXE_NATIVE_DEF(__object2d_get_last_position) {
    auto o2d = (Sandboxe::Object2DObject*)source;        
    context.SetReturnValue(new Sandboxe::VectorObject(o2d->GetLastPosition()));
}



SANDBOXE_NATIVE_DEF(__object2d_get_group) {
    auto o2d = (Sandboxe::Object2DObject*)source;        
    context.SetReturnValue((int)o2d->GetGroup());
}


SANDBOXE_NATIVE_DEF(__object2d_set_group) {
    auto o2d = (Sandboxe::Object2DObject*)source; 
    int group = (int)arguments[0];
    if (group < 0 || group > (int)Dynacoe::Object2D::Group::ID_Z) return;
    o2d->SetGroup(Dynacoe::Object2D::Group(group));
}






void dynacoe_object2d(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::Object2DT,
        {
            {"addVelocity", __object2d_add_velocity},
            {"addVelocityTowards", __object2d_add_velocity_towards},
            {"setVelocity", __object2d_set_velocity},
            {"setVelocityTowards", __object2d_set_velocity_towards},

            {"halt", __object2d_halt},
            {"resetMotion", __object2d_reset_motion},
            {"enableGroupInteraction", __object2d_egi_group},
            {"disableGroupInteraction", __object2d_dgi_group},


            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////
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
    
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

        },

        // properties
        {
            
        },
        
        // native properties
        {
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

            {"tag", {__component_get_tag, __component_set_tag}},
            {"info", {__component_get_info, __component_set_info}},
            {"isStepping", {__component_get_step, __component_set_step}},
            {"isDrawing", {__component_get_draw, __component_set_draw}},
            {"host", {__component_get_host, __component_set_host}},
            {"onStep", {__component_get_on_step, __component_set_on_step}},
            {"onDraw", {__component_get_on_draw, __component_set_on_draw}},
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////
            {"frictionX", {__object2d_get_friction_x, __object2d_set_friction_x}},
            {"frictionY", {__object2d_get_friction_y, __object2d_set_friction_y}},
            {"speed", {__object2d_get_speed, __object2d_set_speed}},
            {"direction", {__object2d_get_direction, SANDBOXE_NATIVE_EMPTY}},
            {"velocityX", {__object2d_get_velocity_x, __object2d_set_velocity_x}},
            {"velocityY", {__object2d_get_velocity_y, __object2d_set_velocity_y}},
            {"collider", {__object2d_get_collider, __object2d_set_collider}},
            {"lastCollided", {__object2d_get_last_collided, SANDBOXE_NATIVE_EMPTY}},
            {"nextPosition", {__object2d_get_next_position, SANDBOXE_NATIVE_EMPTY}},
            {"lastPosition", {__object2d_get_next_position, SANDBOXE_NATIVE_EMPTY}},
            {"group", {__object2d_get_group, __object2d_set_group}},

        }
        
    );
    


  
}
    
    
    
}
}




#endif
