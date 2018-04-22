#ifndef h_include_sandboxe_material
#define h_include_sandboxe_material


namespace Sandboxe {

class MaterialObject : public Sandboxe::Script::Runtime::Object {
  public:

    static void OnChange_Ambient(ColorObject * color, void * self) {
        MaterialObject * m = (MaterialObject*)self;
        m->mat.state.ambient = color->color;
    }

    static void OnChange_Diffuse(ColorObject * color, void * self) {
        MaterialObject * m = (MaterialObject*)self;
        m->mat.state.diffuse = color->color;
    }

    static void OnChange_Specular(ColorObject * color, void * self) {
        MaterialObject * m = (MaterialObject*)self;
        m->mat.state.specular = color->color;
    }



    MaterialObject() : Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::MaterialT) {
        localAmbient = new ColorObject;
        localDiffuse = new ColorObject;
        localSpecular = new ColorObject;
        
        localAmbient->delta.Set(OnChange_Ambient, (void*)this);
        localDiffuse->delta.Set(OnChange_Diffuse, (void*)this);
        localSpecular->delta.Set(OnChange_Specular, (void*)this);


        
    }
    
    Dynacoe::Material mat;
    ColorObject * localAmbient;
    ColorObject * localDiffuse;
    ColorObject * localSpecular;

    
    const char * GetObjectName() const {
        return "Material";
    }
    
    void OnGarbageCollection(){        
    }
        
};

}


#endif