#ifndef h_dynacoe_sandboxe_render_mesh_included
#define h_dynacoe_sandboxe_render_mesh_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/transform.h>



namespace Sandboxe {


class RenderMeshObject : public Dynacoe::RenderMesh, public Sandboxe::ComponentAdaptor {
  public:
    TransformObject * transform;
    
    RenderMeshObject() : Dynacoe::RenderMesh(new Sandboxe::NodeObject), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::RenderMeshT) {
        localMaterial = new Sandboxe::MaterialObject;        
        transfrom = new TransformObject;
        ReplaceTransform(&transform->transformReal);
    }
    
    Sandboxe::MaterialObject * localMaterial;
    std::vector<Sandboxe::MeshObject*> localObjects;

    
    void OnDraw() {        
        Material() = localMaterial->mat;        
        Dynacoe::RenderMesh::OnDraw();
    }
    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "RenderMesh";
    }

    
    #include "component_implementation_common"
    
    
    
};
    
    

    
}


#endif