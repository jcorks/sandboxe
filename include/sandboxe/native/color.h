#ifndef h_sandboxe_color_included
#define h_sandboxe_color_included

namespace Sandboxe {
    
class ColorObject : public Sandboxe::Script::Runtime::Object {
  public:
    ColorObject() : 
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::ColorT)
         {}
        
        
    Dynacoe::Color color;
    void OnGarbageCollection() {
        
    }
    
    const char * GetObjectName() const {
        return "Vector";
    }
        
};

}


#endif