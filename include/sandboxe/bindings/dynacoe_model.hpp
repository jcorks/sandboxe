#ifndef dynacoe_model_sandboxe_binding_included
#define dynacoe_model_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/model.h>
#include <Dynacoe/Model.h>
/*
    Bindings of Dynacoe::Model
    
    
*/


namespace Sandboxe {
namespace Bindings {
    

static Dynacoe::Model * __model_retrieve(Sandboxe::Script::Runtime::Object * source) {
    auto obj = (Sandboxe::ModelObject*)source;
    if (!obj->id.Valid()) return nullptr;
    return &Dynacoe::Assets::Get<Dynacoe::Model>(obj->id);
}
// managed properties

SANDBOXE_NATIVE_DEF(__model_get_section_mesh) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;

    int section = arguments[0];
    if (section >= model->GetSectionCount()) return;
    
    auto out = new Sandboxe::MeshObject();
    out->mesh = model->SectionMesh(section); // TODO : shallow?
    context.SetReturnValue(out);
}

SANDBOXE_NATIVE_DEF(__model_get_section_material) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;

    int section = arguments[0];
    if (section >= model->GetSectionCount()) return;
    
    auto out = new Sandboxe::MaterialObject();
    out->mat = model->SectionMaterial(section); // TODO : shallow?
    context.SetReturnValue(out);
}


SANDBOXE_NATIVE_DEF(__model_set_section_mesh) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;

    int section = arguments[0];
    if (section >= model->GetSectionCount()) return;
    

    
    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(1, MeshObject);
    auto mesh = (Sandboxe::MeshObject*)(Sandboxe::Script::Runtime::Object*)arguments[1];
    model->SectionMesh(section) = mesh->mesh;
}

SANDBOXE_NATIVE_DEF(__model_set_section_material) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;

    int section = arguments[0];
    if (section >= model->GetSectionCount()) return;

    SANDBOXE_ASSERT__ARG_TYPE(1, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(1, MaterialObject);
    auto mat = (Sandboxe::MaterialObject*)(Sandboxe::Script::Runtime::Object*)arguments[1];

    model->SectionMaterial(section) = mat->mat;

}

SANDBOXE_NATIVE_DEF(__model_clear) {
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;
    model->Clear();
}

SANDBOXE_NATIVE_DEF(__model_add_section) {
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;
    model->AddSection();    
}

SANDBOXE_NATIVE_DEF(__model_create) {
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;

    auto id = model->Create();
    if (!id.Valid()) return;
    
    auto ent = new Sandboxe::EntityObjectID();
    ent->id.Identify()->Attach(id);
    context.SetReturnValue(ent);
}

SANDBOXE_NATIVE_DEF(__model_get_section_count) {
    auto obj = (Sandboxe::ModelObject*)source;
    auto model = __model_retrieve(source);
    if(!model) return;
    
    context.SetReturnValue(model->GetSectionCount());
}

void dynacoe_model(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::ModelT,
        // methods
        {
            {"getSectionMesh", __model_get_section_mesh},
            {"getSectionMaterial", __model_get_section_material},
            {"setSectionMesh", __model_set_section_mesh},
            {"setSectionMaterial", __model_set_section_material},

            {"clear", __model_clear},
            {"addSection", __model_add_section},
            {"create", __model_create}

        },

        // properties
        {
        },
        
        // managed properties,
        {
            {"sectionCount", {__model_get_section_count, SANDBOXE_NATIVE_EMPTY}}

        } 
    );
      
}
    
    
    
}
}




#endif