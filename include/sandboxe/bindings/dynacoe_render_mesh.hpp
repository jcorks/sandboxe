#ifndef dynacoe_render_mesh_sandboxe_binding_included
#define dynacoe_render_mesh_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/renderMesh.h>
#include <sandboxe/bindings/dynacoe_component.hpp>

/*

    Dynacoe::RenderMesh bindings 
    
    Notes:
        - The convenience form of AddMesh() is not bound
        - Set/GetRenderPrimitive() are usable through the r/w property "primitive"
        - GetMeshCount() is usable as a read-only property "meshCount"


*/


namespace Sandboxe {
namespace Bindings {




SANDBOXE_NATIVE_DEF(__render_mesh_add_mesh) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, MeshObject);
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    auto in = (Sandboxe::MeshObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    mesh->localObjects.push_back(in);
    mesh->AddMesh(in->mesh);
}

SANDBOXE_NATIVE_DEF(__render_mesh_get_mesh) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    int index = arguments[0];
    if (index < 0 || index >= mesh->localObjects.size()) {
        return;
    }
    context.SetReturnValue(mesh->localObjects[index]);
}

SANDBOXE_NATIVE_DEF(__render_mesh_clear) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    mesh->Clear();
    mesh->localObjects.clear();
}


SANDBOXE_NATIVE_DEF(__render_mesh_get_primitive) {
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    int i = (int)mesh->GetRenderPrimitive();
    context.SetReturnValue(i);
}

SANDBOXE_NATIVE_DEF(__render_mesh_set_primitive) {
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    int type = arguments[0];
    if (type < 0 || type > (int)Dynacoe::Renderer::Polygon::Line) return;
    mesh->SetRenderPrimitive((Dynacoe::Renderer::Polygon)type);
}


SANDBOXE_NATIVE_DEF(__render_mesh_get_mesh_count) {
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    context.SetReturnValue(mesh->localObjects.size());
}

SANDBOXE_NATIVE_DEF(__render_mesh_get_material) {
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    context.SetReturnValue(mesh->localMaterial);
}

SANDBOXE_NATIVE_DEF(__render_mesh_set_material) {
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, MaterialObject);
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    auto mat = (Sandboxe::MaterialObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    mesh->Material() = mat->mat;
}




SANDBOXE_NATIVE_DEF(__render_mesh_node_get) {
    auto mesh = (Sandboxe::RenderMeshObject*)source;
    context.SetReturnValue(mesh->transform);
}


/// global functions
SANDBOXE_NATIVE_DEF(__render_mesh_create) {
    context.SetReturnValue(new Sandboxe::RenderMeshObject);
}


void dynacoe_render_mesh(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::RenderMeshT,
        {
            {"addMesh", __render_mesh_add_mesh},
            {"getMesh", __render_mesh_get_mesh},
            {"clear", __render_mesh_clear},

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
            
            ////////////////////////////////////////////////////////
            //////////////////// imported from component ///////////

            {"primitive", {__render_mesh_get_primitive, __render_mesh_set_primitive}},
            {"material", {__render_mesh_get_material, __render_mesh_set_material}},
            {"node", {__render_mesh_node_get, SANDBOXE_NATIVE_EMPTY}},
            {"meshCount", {__render_mesh_get_mesh_count, SANDBOXE_NATIVE_EMPTY}}


        }
        
    );
    
    fns.push_back({"__render_mesh_create", __render_mesh_create});    
}
    
    
    
}
}




#endif