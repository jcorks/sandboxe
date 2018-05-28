#ifndef h_dynacoe_sandboxe_material_included
#define h_dynacoe_sandboxe_material_included



#include <sandboxe/native/native.h>
#include <sandboxe/native/material.h>

/*
    Dynacoe::Material  class bindings.

    Notes:
        - SetProgram can accept either na int (core program enum) or a live reference to a shader instance 

 */





namespace Sandboxe {
namespace Bindings {






// functions 

SANDBOXE_NATIVE_DEF(__material_set_program) {
    auto mat = (Sandboxe::MaterialObject *)source;
    
    if (arguments[0].hint == Sandboxe::Script::Runtime::Primitive::TypeHint::ObjectReferenceT) {
        SANDBOXE_ASSERT__ARG_NATIVE(0, ShaderObject);
        ShaderObject * o = (ShaderObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
        mat->mat.SetProgram(o->shader.GetID());
    } else {
        int program = arguments[0];
        if (program > (int)Dynacoe::Material::CoreProgram::Lighting) return;
        mat->mat.SetProgram((Dynacoe::Material::CoreProgram)program);        
    }
}

SANDBOXE_NATIVE_DEF(__material_add_texture) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(1, AssetIDObject);
    auto mat = (Sandboxe::MaterialObject *)source;
    auto id = (AssetIDObject*)(Sandboxe::Script::Runtime::Object*)arguments[1];
    mat->mat.AddTexture(arguments[0], id->id);
}

SANDBOXE_NATIVE_DEF(__material_set_framebuffer) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, CameraEntityID);
    auto mat = (Sandboxe::MaterialObject *)source;
    auto id = (CameraEntityID*)(Sandboxe::Script::Runtime::Object*)arguments[1];
    if (!id->id.Valid()) return;
    mat->mat.SetFramebufferSource(*id->id.IdentifyAs<Sandboxe::Camera>()->realCamera.IdentifyAs<Dynacoe::Camera>());
}


SANDBOXE_NATIVE_DEF(__material_next_texture_frame) {
    auto mat = (Sandboxe::MaterialObject *)source;
    mat->mat.NextTextureFrame();
}


SANDBOXE_NATIVE_DEF(__material_get_ambient) {
    auto mat = (Sandboxe::MaterialObject *)source;
    context.SetReturnValue(mat->localAmbient);
}

SANDBOXE_NATIVE_DEF(__material_get_diffuse) {
    auto mat = (Sandboxe::MaterialObject *)source;
    context.SetReturnValue(mat->localDiffuse);
}

SANDBOXE_NATIVE_DEF(__material_get_specular) {
    auto mat = (Sandboxe::MaterialObject *)source;
    context.SetReturnValue(mat->localSpecular);
}

SANDBOXE_NATIVE_DEF(__material_get_shininess) {
    auto mat = (Sandboxe::MaterialObject *)source;
    context.SetReturnValue(mat->mat.state.shininess);
}

SANDBOXE_NATIVE_DEF(__material_get_diffuse_amount) {
    auto mat = (Sandboxe::MaterialObject *)source;
    context.SetReturnValue(mat->mat.state.diffuseAmount);
}

SANDBOXE_NATIVE_DEF(__material_get_specular_amount) {
    auto mat = (Sandboxe::MaterialObject *)source;
    context.SetReturnValue(mat->mat.state.specularAmount);
}

SANDBOXE_NATIVE_DEF(__material_get_user_data) {
    auto mat = (Sandboxe::MaterialObject *)source;
    std::vector<Sandboxe::Script::Runtime::Primitive> primitives;
    primitives.resize(32);
    for(uint32_t i = 0; i < 32; ++i) {
        primitives[i] = mat->mat.state.userData[i];
    }
    context.SetReturnArray(primitives);
}



SANDBOXE_NATIVE_DEF(__material_set_ambient) {
    auto mat = (Sandboxe::MaterialObject *)source;
    argument_to_color_object(mat->localAmbient->color, arguments[0]);
    mat->localAmbient->delta.Changed(mat->localAmbient);
}

SANDBOXE_NATIVE_DEF(__material_set_specular) {
    auto mat = (Sandboxe::MaterialObject *)source;
    argument_to_color_object(mat->localSpecular->color, arguments[0]);
    mat->localSpecular->delta.Changed(mat->localSpecular);
}

SANDBOXE_NATIVE_DEF(__material_set_diffuse) {
    auto mat = (Sandboxe::MaterialObject *)source;
    argument_to_color_object(mat->localDiffuse->color, arguments[0]);
    mat->localDiffuse->delta.Changed(mat->localDiffuse);
}

SANDBOXE_NATIVE_DEF(__material_set_shininess) {
    auto mat = (Sandboxe::MaterialObject *)source;
    mat->mat.state.shininess = arguments[0];
}

SANDBOXE_NATIVE_DEF(__material_set_specular_amount) {
    auto mat = (Sandboxe::MaterialObject *)source;
    mat->mat.state.specularAmount = arguments[0];
}

SANDBOXE_NATIVE_DEF(__material_set_diffuse_amount) {
    auto mat = (Sandboxe::MaterialObject *)source;
    mat->mat.state.diffuseAmount = arguments[0];
}

SANDBOXE_NATIVE_DEF(__material_set_user_data) {
    auto mat = (Sandboxe::MaterialObject *)source;
    auto input = context.GetArrayArgument(0);
    if (!input) return;
    for(uint32_t i = 0; i < input->size() && i < 32; ++i) {
        mat->mat.state.userData[i] = (*input)[i];
    }
}


/// global functions
SANDBOXE_NATIVE_DEF(__material_create) {
    context.SetReturnValue(new Sandboxe::MaterialObject);
}


void dynacoe_material(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::MaterialT,
        // methods
        {
            {"addTexture", __material_add_texture},
            {"setFramebufferSource", __material_set_framebuffer},
            {"nextTextureFrame", __material_next_texture_frame},
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"ambient", {__material_get_ambient, __material_set_ambient}}, 
            {"diffuse", {__material_get_diffuse, __material_set_diffuse}}, 
            {"specular", {__material_get_specular, __material_set_specular}}, 

            {"specularAmount", {__material_get_specular_amount, __material_set_specular_amount}}, 
            {"diffuseAmount", {__material_get_diffuse_amount, __material_set_diffuse_amount}}, 
            {"shininess", {__material_get_shininess, __material_set_shininess}}, 
            {"program", {SANDBOXE_NATIVE_EMPTY, __material_set_program}},

            {"userData", {__material_get_user_data, __material_set_user_data}}
        }
    );
    
    fns.push_back({"__material_create", __material_create});    
}


}
}

#endif
