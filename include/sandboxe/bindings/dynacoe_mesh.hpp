#ifndef dynacoe_mesh_sandboxe_binding_included
#define dynacoe_mesh_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/mesh.h>

/*
    Dynacoe::Mesh bindings:
    Notes:
        - SetVertexCount() / NumVertices() are replaced by "vertexCount" property (r/w)
        - All returned vectors / recevied vectors are arrays of 3 members.
        - DefineVerticesState is not implemented.
        - MeshObjects arent implemented and are, instead, arrays of integers (face list)
        - No bindings for the shallow/unique behavior were implemented.
*/

namespace Sandboxe {
namespace Bindings {
    

// managed properties



SANDBOXE_NATIVE_DEF(__mesh_define_vertices) {
    auto mesh = (Sandboxe::MeshObject*)source;
    SANDBOXE_ASSERT__ARG_COUNT(2);
    int type = arguments[0];
    if (type < 0 || type > (int)Dynacoe::Mesh::VertexAttribute::UserData) return;
    auto args = context.GetArrayArgument(1);
    if (!args) return;

    std::vector<Dynacoe::Vector> in;
    if (type != 2) {
        for(uint32_t i = 0; i < args->size()/3; ++i) {
            in.push_back(
                Dynacoe::Vector(
                    (*args)[i*3+0],
                    (*args)[i*3+1],
                    (*args)[i*3+2]
                )
            );
        }
    } else {
        for(uint32_t i = 0; i < args->size()/2; ++i) {
            in.push_back(
                Dynacoe::Vector(
                    (*args)[i*2+0],
                    (*args)[i*2+1]
                )
            );
        }
        
    }

    mesh->mesh.DefineVertices(
        (Dynacoe::Mesh::VertexAttribute)type,
        in
    );
    
    
}

SANDBOXE_NATIVE_DEF(__mesh_get_vertex) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto mesh = (Sandboxe::MeshObject*)source;
    int type = arguments[1];
    if (type < 0 || type > (int)Dynacoe::Mesh::VertexAttribute::UserData) return;
    auto v = mesh->mesh.GetVertex(arguments[0], (Dynacoe::Mesh::VertexAttribute)type);
    if (type == 2) {
        context.SetReturnArray({
            v.x,
            v.y
        });
    } else {
        context.SetReturnArray({
            v.x,
            v.y,
            v.z
        });
    }
}

SANDBOXE_NATIVE_DEF(__mesh_set_vertex) {
    SANDBOXE_ASSERT__ARG_COUNT(3);
    auto mesh = (Sandboxe::MeshObject*)source;
    int type = arguments[1];
    if (type < 0 || type > (int)Dynacoe::Mesh::VertexAttribute::UserData) return;

    auto args = context.GetArrayArgument(2);
    
    Dynacoe::Vector v;
    if (type == 2) {
        if (args->size() < 2) return;
        v.x = (*args)[0];
        v.y = (*args)[1];
    } else {
        if (args->size() < 2) return;
        v.x = (*args)[0];
        v.y = (*args)[1];
        v.z = (*args)[2];
    }
    mesh->mesh.SetVertex(
        arguments[0], 
        (Dynacoe::Mesh::VertexAttribute)type,
        v
    );
}


SANDBOXE_NATIVE_DEF(__mesh_add_object) {
    auto mesh = (Sandboxe::MeshObject*)source;

    if (arguments.size() > 0) {
        auto args = context.GetArrayArgument(0);
        if (!args) return;
        Dynacoe::Mesh::MeshObject obj;
        for(uint32_t i = 0; i < args->size(); ++i) {
            obj.faceList.push_back((*args)[i]);            
        }
        mesh->mesh.AddObject(obj);
    } else {
        mesh->mesh.AddObject();
    }
}

SANDBOXE_NATIVE_DEF(__mesh_get_object) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto mesh = (Sandboxe::MeshObject*)source;
    auto out = mesh->mesh.Get(arguments[0]);
    if (!out) return;
    std::vector<Sandboxe::Script::Runtime::Primitive> vec;
    for(uint32_t i = 0; i < out->faceList.size(); ++i) {
        vec.push_back(out->faceList[i]);
    }
    context.SetReturnArray(vec);
}

SANDBOXE_NATIVE_DEF(__mesh_remove_object) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto mesh = (Sandboxe::MeshObject*)source;
    mesh->mesh.RemoveObject(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__mesh_num_objects) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto mesh = (Sandboxe::MeshObject*)source;
    context.SetReturnValue(mesh->mesh.NumObjects());
}



SANDBOXE_NATIVE_DEF(__mesh_set_vertex_count) {
    auto mesh = (Sandboxe::MeshObject*)source;
    mesh->mesh.SetVertexCount(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__mesh_get_vertex_count) {
    auto mesh = (Sandboxe::MeshObject*)source;
    context.SetReturnValue(mesh->mesh.NumVertices());
}



/// global functions
SANDBOXE_NATIVE_DEF(__mesh_create) {
    context.SetReturnValue(new Sandboxe::MeshObject);
}

SANDBOXE_NATIVE_DEF(__mesh_create_cube) {
    auto mesh = new Sandboxe::MeshObject;
    mesh->mesh = Dynacoe::Mesh::Basic_Cube();
    context.SetReturnValue(mesh);
}

SANDBOXE_NATIVE_DEF(__mesh_create_square) {
    auto mesh = new Sandboxe::MeshObject;
    mesh->mesh = Dynacoe::Mesh::Basic_Square();
    context.SetReturnValue(mesh);
}



void dynacoe_mesh(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::MeshT,
        // methods
        {
            {"defineVertices", __mesh_define_vertices},
            {"getVertex", __mesh_get_vertex},
            {"setVertex", __mesh_set_vertex},
            
            
            {"addObject", __mesh_add_object},
            {"getObject", __mesh_get_object},
            {"removeObject", __mesh_remove_object},
            {"numObjects", __mesh_num_objects},
            
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"vertexCount", {__mesh_get_vertex_count, __mesh_set_vertex_count}},

        } 
    );
    
    fns.push_back({"__mesh_create", __mesh_create});    
    fns.push_back({"__mesh_create_cube", __mesh_create_cube});    
    fns.push_back({"__mesh_create_square", __mesh_create_square});    

}
    
    
    
}
}




#endif