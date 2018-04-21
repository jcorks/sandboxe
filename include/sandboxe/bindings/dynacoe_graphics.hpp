#ifndef H_sandboxe_bindings_dynacoe_graphics
#define H_sandboxe_bindings_dynacoe_graphics
#include <sandboxe/native/native.h>


/*
    Bindings for Dynacoe::Graphics
    
    Notes:
        - DrawString is not implemented
        


 */

namespace Sandboxe {
namespace Bindings {

SANDBOXE_NATIVE_DEF(__graphics_draw) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    auto object = (Sandboxe::Script::Runtime::Object*)arguments[0];
    Dynacoe::Render2D * r2d = nullptr;
    if ((r2d = dynamic_cast<Dynacoe::Render2D*>(object))) {
        Dynacoe::Graphics::Draw(*r2d);
    }
}

SANDBOXE_NATIVE_DEF(__graphics_commit) {
    Dynacoe::Graphics::Commit();
}

SANDBOXE_NATIVE_DEF(__graphics_get_draw_each_frame) {
    context.SetReturnValue(Dynacoe::Graphics::DrawEachFrame());
}

SANDBOXE_NATIVE_DEF(__graphics_set_draw_each_frame) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Graphics::DrawEachFrame(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__graphics_set_enable_filtering) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Graphics::EnableFiltering(arguments[0]);
}


SANDBOXE_NATIVE_DEF(__graphics_set_camera_2d) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, CameraEntityID);
    
    auto cam = ((CameraEntityID*)(Sandboxe::Script::Runtime::Object*)arguments[0])->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    Dynacoe::Graphics::SetCamera2D(*cam->Self());
}

SANDBOXE_NATIVE_DEF(__graphics_set_camera_3d) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, CameraEntityID);
    
    auto cam = ((CameraEntityID*)(Sandboxe::Script::Runtime::Object*)arguments[0])->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    Dynacoe::Graphics::SetCamera3D(*cam->Self());
}

SANDBOXE_NATIVE_DEF(__graphics_set_render_camera) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, CameraEntityID);
    
    auto cam = ((CameraEntityID*)(Sandboxe::Script::Runtime::Object*)arguments[0])->id.IdentifyAs<Sandboxe::Camera>();
    if (!cam) return;
    Dynacoe::Graphics::SetRenderCamera(*cam->Self());
}


SANDBOXE_NATIVE_DEF(__graphics_get_camera_3d) {    
    context.SetReturnValue(
        Dynacoe::Entity::ID(Dynacoe::Graphics::GetCamera3D().GetName()).IdentifyAs<Sandboxe::Camera>()->object
    );
}

SANDBOXE_NATIVE_DEF(__graphics_get_camera_2d) {    
    context.SetReturnValue(
        Dynacoe::Entity::ID(Dynacoe::Graphics::GetCamera2D().GetName()).IdentifyAs<Sandboxe::Camera>()->object
    );
}

SANDBOXE_NATIVE_DEF(__graphics_get_render_camera) {    
    context.SetReturnValue(
        Dynacoe::Entity::ID(Dynacoe::Graphics::GetRenderCamera().GetName()).IdentifyAs<Sandboxe::Camera>()->object
    );
}





void dynacoe_graphics(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    fns.push_back({"__graphics_commit", __graphics_commit});
    fns.push_back({"__graphics_set_enable_filtering", __graphics_set_enable_filtering});
    fns.push_back({"__graphics_draw", __graphics_draw});
    fns.push_back({"__graphics_set_draw_each_frame", __graphics_set_draw_each_frame});
    fns.push_back({"__graphics_get_draw_each_frame", __graphics_get_draw_each_frame});
    fns.push_back({"__graphics_set_camera_2d", __graphics_set_camera_2d});
    fns.push_back({"__graphics_set_camera_3d", __graphics_set_camera_3d});
    fns.push_back({"__graphics_set_render_camera", __graphics_set_render_camera});

    fns.push_back({"__graphics_get_camera_2d", __graphics_get_camera_2d});
    fns.push_back({"__graphics_get_camera_3d", __graphics_get_camera_3d});
    fns.push_back({"__graphics_get_render_camera", __graphics_get_render_camera});



}

}
}



#endif