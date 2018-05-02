#ifndef h_image_sandboxe_dynacoe_included 
#define h_image_sandboxe_dynacoe_included




namespace Sandboxe {
class ImageObject : public Sandboxe::Script::Runtime::Object {
  public:    
    ImageObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ImageT){}
    
    Dynacoe::AssetID id;

    void OnGarbageCollection(){}

    

    const char * GetObjectName() const {
        return "Image";
    }
};



class ImageFrameObject : public Sandboxe::Script::Runtime::Object {
  public:    
    ImageFrameObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ImageFrameT){}
    
    Dynacoe::AssetID id;
    uint32_t frameIndex;

    void OnGarbageCollection(){}

    

    const char * GetObjectName() const {
        return "ImageFrame";
    }
};
}


#endif