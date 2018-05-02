#ifndef dynacoe_image_frame_sandboxe_binding_included
#define dynacoe_image_frame_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/image.h>
/*
    Bindings of Dynacoe::Image::Frame
    Nodes:
        - Alternative constructors are emulated using resize() and copyFrom()
        - Detilize is not bound
        - GetHandle() is not bound
*/


namespace Sandboxe {
namespace Bindings {
    

// managed properties

static Dynacoe::Image::Frame * __image_frame_retrieve(Sandboxe::Script::Runtime::Object * source) {
    auto obj = (Sandboxe::ImageFrameObject*)source;
    if (!obj->id.Valid()) return nullptr;
    auto image = &Dynacoe::Assets::Get<Dynacoe::Image>(obj->id);
    if (obj->frameIndex >= image->frames.size()) return nullptr;
    return &image->frames[obj->frameIndex];
}

SANDBOXE_NATIVE_DEF(__image_frame_resize) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto frame = __image_frame_retrieve(source);
    if (!frame) return;

    *frame = Dynacoe::Image::Frame(arguments[0], arguments[1]);
}

SANDBOXE_NATIVE_DEF(__image_frame_copy_from) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, ImageFrameObject);

    auto frame = __image_frame_retrieve(source);
    if (!frame) return;

    auto frameOther = __image_frame_retrieve(arguments[0]);
    if (!frameOther) return;

    *frame = *frameOther;
}


SANDBOXE_NATIVE_DEF(__image_frame_get_data) {
    auto frame = __image_frame_retrieve(source);
    if (!frame) return;

    auto src = frame->GetData();
    std::vector<Sandboxe::Script::Runtime::Primitive> data(src.size());

    for(uint32_t i = 0; i < src.size(); ++i) {
        data[i] = src[i];
    }
    context.SetReturnArray(data);
}

SANDBOXE_NATIVE_DEF(__image_frame_set_data) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto src = context.GetArrayArgument(0);
    if (!src) return;
    
    auto frame = __image_frame_retrieve(source);
    if (!frame) return;

    std::vector<uint8_t> data(src->size());

    for(uint32_t i = 0; i < src->size(); ++i) {
        data.push_back((int)(*src)[i]);
    }
    
    frame->SetData(data);
}


SANDBOXE_NATIVE_DEF(__image_frame_get_width) {
    auto frame = __image_frame_retrieve(source);
    if (!frame) return;

    context.SetReturnValue(frame->Width());
}

SANDBOXE_NATIVE_DEF(__image_frame_get_height) {
    auto frame = __image_frame_retrieve(source);
    if (!frame) return;

    context.SetReturnValue(frame->Height());
}


void dynacoe_image_frame(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int) Sandboxe::NativeType::ImageFrameT,
        // methods
        {
            {"resize", __image_frame_resize},
            {"copyFrom", __image_frame_copy_from},
            {"getData", __image_frame_get_data},
            {"setData", __image_frame_set_data}

        },

        // properties
        {
        },
        
        // managed properties,
        {
            {"width", {__image_frame_get_width, SANDBOXE_NATIVE_EMPTY}},
            {"height", {__image_frame_get_height, SANDBOXE_NATIVE_EMPTY}},
            

        } 
    );
      
}
    
    
    
}
}




#endif