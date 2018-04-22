#ifndef h_sandboxe_shader_included 
#define h_sandboxe_shader_included 

namespace Sandboxe {
class ShaderObject : public Sandboxe::Script::Runtime::Object {
  public:
    
    ShaderObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ShaderT){}
    
    Dynacoe::Shader shader;


    void OnGarbageCollection(){}
    
    const char * GetObjectName() const {
        return "Shader";
    }
    
};    
}

#endif