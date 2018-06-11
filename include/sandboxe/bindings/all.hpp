#ifndef h_sandboxe_bindings_all_included
#define h_sandboxe_bindings_all_included

// all includes
#include <sandboxe/native/delta.h>
#include "dynacoe_vector.hpp"
#include "dynacoe_component.hpp"
#include "dynacoe_console.hpp"
#include "dynacoe_entity.hpp"
#include "dynacoe_component.hpp"
#include "dynacoe_node_transform.hpp"
#include "dynacoe_node.hpp"
#include "dynacoe_engine.hpp"
#include "dynacoe_input.hpp"
#include "dynacoe_assets.hpp"
#include "dynacoe_color.hpp"
#include "dynacoe_clock.hpp"
#include "dynacoe_shape2d.hpp"
#include "dynacoe_text2d.hpp"
#include "dynacoe_data_table.hpp"
#include "dynacoe_gui.hpp"
#include "dynacoe_mutator.hpp"
#include "dynacoe_object2d.hpp"
#include "dynacoe_camera.hpp"
#include "dynacoe_graphics.hpp"
#include "dynacoe_render_light.hpp"
#include "dynacoe_mesh.hpp"
#include "dynacoe_shader.hpp"
#include "dynacoe_material.hpp"
#include "dynacoe_render_mesh.hpp"
#include "dynacoe_scheduler.hpp"
#include "dynacoe_state_control.hpp"
#include "dynacoe_display.hpp"
#include "dynacoe_active_sound.hpp"
#include "dynacoe_sound.hpp"
#include "dynacoe_audio_block.hpp"
#include "dynacoe_image.hpp"
#include "dynacoe_image_frame.hpp"
#include "dynacoe_particle_emitter_2d.hpp"
#include "dynacoe_input_buffer.hpp"
#include "dynacoe_output_buffer.hpp"
#include "dynacoe_model.hpp"
#include "sandboxe_trunk.hpp"


namespace Sandboxe {
namespace Script {

std::vector<std::pair<std::string, Runtime::Function>> GatherNativeBindings() {
    std::vector<std::pair<std::string, Runtime::Function>> out;
    Bindings::dynacoe_vector(out);
    Bindings::dynacoe_component(out);
    Bindings::dynacoe_console(out);
    Bindings::dynacoe_entity(out);
    Bindings::dynacoe_node_transform(out);
    Bindings::dynacoe_node(out);
    Bindings::dynacoe_engine(out);
    Bindings::dynacoe_input(out);
    Bindings::dynacoe_assets(out);
    Bindings::dynacoe_color(out);
    Bindings::dynacoe_clock(out);
    Bindings::dynacoe_shape2d(out);
    Bindings::dynacoe_text2d(out);
    Bindings::dynacoe_data_table(out);
    Bindings::dynacoe_gui(out);
    Bindings::dynacoe_mutator(out);
    Bindings::dynacoe_object2d(out);
    Bindings::dynacoe_camera(out);
    Bindings::dynacoe_graphics(out);
    Bindings::dynacoe_render_light(out);
    Bindings::dynacoe_mesh(out);
    Bindings::dynacoe_shader(out);
    Bindings::dynacoe_material(out);
    Bindings::dynacoe_render_mesh(out);
    Bindings::dynacoe_scheduler(out);
    Bindings::dynacoe_state_control(out);
    Bindings::dynacoe_display(out);
    Bindings::dynacoe_active_sound(out);
    Bindings::dynacoe_sound(out);
    Bindings::dynacoe_audio_block(out);
    Bindings::dynacoe_image(out);
    Bindings::dynacoe_image_frame(out);
    Bindings::dynacoe_particle_emitter_2d(out);
    Bindings::dynacoe_input_buffer(out);
    Bindings::dynacoe_output_buffer(out);
    Bindings::dynacoe_model(out);


    
    

    Bindings::sandboxe_trunk(out);
    return out;
}   


void ApplyPostBindings() {
    Dynacoe::Graphics::GetCamera2D().Remove();
    Dynacoe::Graphics::GetCamera3D().Remove();
    Dynacoe::Graphics::GetRenderCamera().Remove();
    
    auto c2d = new Sandboxe::CameraEntityID();
    auto c3d = new Sandboxe::CameraEntityID();

    c2d->id.IdentifyAs<Sandboxe::Camera>()->Self()->SetType(Dynacoe::Camera::Type::Orthographic2D);
    c3d->id.IdentifyAs<Sandboxe::Camera>()->Self()->SetType(Dynacoe::Camera::Type::Perspective3D);
    c3d->id.IdentifyAs<Sandboxe::Camera>()->Self()->BindTransformBuffers(
        Dynacoe::Graphics::GetRenderer()->GetStaticViewingMatrixID(),
        Dynacoe::Graphics::GetRenderer()->GetStaticProjectionMatrixID()
    );
    
    Dynacoe::Graphics::SetCamera3D(*c3d->id.IdentifyAs<Sandboxe::Camera>()->Self());
    Dynacoe::Graphics::SetCamera2D(*c2d->id.IdentifyAs<Sandboxe::Camera>()->Self());
    Dynacoe::Graphics::SetRenderCamera(*c2d->id.IdentifyAs<Sandboxe::Camera>()->Self());
    
    c2d->id.IdentifyAs<Sandboxe::Camera>()->Self()->node.local.reverse = true;
    c2d->id.IdentifyAs<Sandboxe::Camera>()->Self()->SetRenderResolution(640, 480);
    Dynacoe::Engine::AttachManager(c2d->id);
    Dynacoe::Engine::AttachManager(c3d->id);

}


 
}
}

namespace Sandboxe {
namespace Bindings {
SANDBOXE_NATIVE_DEF(__entity_add) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    const Dynacoe::Entity::ID & id = ((EntityObjectID*)source)->id;
    Dynacoe::Entity * e = id.Identify();    
    if (!e) return;
    
    std::string name = arguments[0];
    auto updateClass = Dynacoe::Entity::UpdateClass::Before;
    if (arguments.size() > 1) {
        updateClass = (Dynacoe::Entity::UpdateClass)(int)arguments[1];
    }
    
    static std::map<std::string, Sandboxe::NativeType> * name2id = nullptr;
    if (!name2id) {
        name2id = new std::map<std::string, Sandboxe::NativeType>();
        (*name2id)["stateControl"] = Sandboxe::NativeType::StateControlT;
        (*name2id)["scheduler"]    = Sandboxe::NativeType::SchedulerT;
        (*name2id)["renderMesh"]   = Sandboxe::NativeType::RenderMeshT;
        (*name2id)["renderLight"]  = Sandboxe::NativeType::RenderLightT;
        (*name2id)["object2d"]     = Sandboxe::NativeType::Object2DT;
        (*name2id)["mutator"]      = Sandboxe::NativeType::MutatorT;
        (*name2id)["gui"]          = Sandboxe::NativeType::GUIT;
        (*name2id)["dataTable"]    = Sandboxe::NativeType::DataTableT;
        (*name2id)["text2d"]       = Sandboxe::NativeType::Text2DT;
        (*name2id)["clock"]        = Sandboxe::NativeType::ClockT;
        (*name2id)["shape2d"]      = Sandboxe::NativeType::Shape2DT;
    }
    
    Sandboxe::ComponentAdaptor * component = nullptr;
    switch((*name2id)[name]) {
      case Sandboxe::NativeType::StateControlT: component = new Sandboxe::StateControlObject; break;
      case Sandboxe::NativeType::SchedulerT:    component = new Sandboxe::SchedulerObject; break;
      case Sandboxe::NativeType::RenderMeshT:   component = new Sandboxe::RenderMeshObject; break;
      case Sandboxe::NativeType::RenderLightT:  component = new Sandboxe::RenderLightObject; break;
      case Sandboxe::NativeType::Object2DT:     component = new Sandboxe::Object2DObject; break;
      case Sandboxe::NativeType::MutatorT:      component = new Sandboxe::MutatorObject; break;
      case Sandboxe::NativeType::GUIT:          component = new Sandboxe::GUIObject; break;
      case Sandboxe::NativeType::DataTableT:    component = new Sandboxe::DataTableObject; break;
      case Sandboxe::NativeType::Text2DT:       component = new Sandboxe::Text2DObject; break;
      case Sandboxe::NativeType::ClockT:        component = new Sandboxe::ClockObject; break;
      case Sandboxe::NativeType::Shape2DT:      component = new Sandboxe::Shape2DObject; break;
      default:;
    }
    
    e->AddComponent(component->Native_GetDynacoeComponent(), updateClass);
    context.SetReturnValue(component);
    
}
}
}

#endif
