#ifndef dynacoe_image_sandboxe_binding_included
#define dynacoe_image_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/image.h>
#include <Dynacoe/Image.h>
/*
    Bindings of Dynacoe::Image
    Nodes:
        - the frames std::vector as been bound as a r/w size controller and 
          a retrieval fn.

*/


namespace Sandboxe {
namespace Bindings {
    

static Dynacoe::Image * __image_retrieve(Sandboxe::Script::Runtime::Object * source) {
    auto obj = (Sandboxe::ImageObject*)source;
    if (!obj->id.Valid()) return nullptr;
    return &Dynacoe::Assets::Get<Dynacoe::Image>(obj->id);
}
// managed properties

SANDBOXE_NATIVE_DEF(__image_get_frame) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto obj = (Sandboxe::ImageObject*)source;
    
    auto out = new Sandboxe::ImageFrameObject();
    out->id = obj->id;
    out->frameIndex = arguments[0];
}

SANDBOXE_NATIVE_DEF(__image_get_frame_count) {
    auto obj = (Sandboxe::ImageObject*)source;
    auto image = __image_retrieve(source);
    if (!image) return;    
    
    context.SetReturnValue(image->frames.size());
}

SANDBOXE_NATIVE_DEF(__image_set_frame_count) {
    auto obj = (Sandboxe::ImageObject*)source;
    auto image = __image_retrieve(source);
    if (!image) return;    
    
    image->frames.resize(arguments[0]);
}



void dynacoe_image(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::ImageT,
        // methods
        {
            {"getFrame", __image_get_frame}
        },

        // properties
        {
        },
        
        // managed properties,
        {
            {"frameCount", {__image_get_frame_count, __image_set_frame_count}}

        } 
    );
      
}
    
    
    
}
}




#endif