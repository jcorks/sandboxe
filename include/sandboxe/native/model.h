#ifndef h_model_sandboxe_dynacoe_included 
#define h_model_sandboxe_dynacoe_included




namespace Sandboxe {
class ModelObject : public Sandboxe::Script::Runtime::Object {
  public:    
    ModelObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ModelT){}
    
    Dynacoe::AssetID id;

    void OnGarbageCollection(){}

    

    const char * GetObjectName() const {
        return "Model";
    }
};
}

#endif