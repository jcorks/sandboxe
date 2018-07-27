#ifndef h_dynacoe_sandboxe_Object2D_included
#define h_dynacoe_sandboxe_Object2D_included



namespace Sandboxe {


class Object2DObject : public Dynacoe::Object2D, public Sandboxe::ComponentAdaptor {
  public:
    
    Object2DObject() : Dynacoe::Object2D(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::Object2DT) {
        frictionX = 0.0;
        frictionY = 0.0;
        SetFrictionX(0.0);
        SetFrictionY(0.0);
    }
    
    ~Object2DObject() {    
    }
    
    
    
    double frictionX;
    double frictionY;
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
