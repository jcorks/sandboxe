#ifndef h_dynacoe_sandboxe_Object2D_included
#define h_dynacoe_sandboxe_Object2D_included



namespace Sandboxe {


class Object2DObject : public Dynacoe::Object2D, public Sandboxe::ComponentAdaptor {
  public:
    
    Object2DObject() : Dynacoe::Object2D(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::Object2DT) {
        frictionX = 0.0;
        frictionY = 0.0;
        rate = 1.f;
    }
    
    ~Object2DObject() {    
    }
    
    
    
    float frictionX;
    float frictionY;
    float rate;
    std::vector<float> colliderData;

    void OnGarbageCollection() {
        
    }
    
    void OnStep() {
        Object2D::OnStep();
    }
    
    const char * GetObjectName() const {
        return "Object2D";
    }

    
    #include "component_implementation_common"
    
    
    
};
    
    

    
}


#endif
