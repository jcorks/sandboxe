#ifndef h_dynacoe_sandboxe_render_mesh_included
#define h_dynacoe_sandboxe_render_mesh_included


#include <sandboxe/native/component.h>
#include <sandboxe/native/node.h>


namespace Sandboxe {


class RenderMeshObject : public Dynacoe::RenderMesh, public Sandboxe::ComponentAdaptor {
  public:
    
    RenderMeshObject() : Dynacoe::RenderMesh(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::RenderMeshT) {
        
        localMaterial = new Sandboxe::MaterialObject;        
        localNode = new Sandboxe::NodeObject;


    }
    
    Sandboxe::MaterialObject * localMaterial;
    Sandboxe::NodeObject * localNode;
    std::vector<Sandboxe::MeshObject*> localObjects;

    
    void OnDraw() {
        node.local.position = localNode->localTransform->position->vector;
        node.local.rotation = localNode->localTransform->rotation->vector;
        node.local.scale    = localNode->localTransform->scale->vector;
        node.local.reverse = localNode->local.reverse;
        
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