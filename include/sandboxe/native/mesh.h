#ifndef h_sandboxe_mesh_included
#define h_sandboxe_mesh_included

namespace Sandboxe {
class MeshObject : public Sandboxe::Script::Runtime::Object {
  public:    
    MeshObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::MeshT){}
    Dynacoe::Mesh mesh;
    
    void OnGarbageCollection(){}
    const char * GetObjectName() const {
        return "Mesh";
    }
};    
}


#endif