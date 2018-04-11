#ifndef h_sandboxe_dynacoe_asset_id_included
#define h_sandboxe_dynacoe_asset_id_included

namespace Sandboxe {
class AssetID {
  public:
      
    AssetID(Sandboxe::Script::Runtime::Object * o) {
        object = o;
    }
    
    Dynacoe::AssetID id;
    Sandboxe::Script::Runtime::Object * object;
    
};
}
#endif