#ifndef h_sandboxe_dynacoe_asset_id_included
#define h_sandboxe_dynacoe_asset_id_included

namespace Sandboxe {
class AssetIDObject : public Sandboxe::Script::Runtime::Object{
  public:
    
    AssetIDObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::AssetIDT){

    }
    
    
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "AssetID";
    }
    
    Dynacoe::AssetID id;
    
};
}
#endif