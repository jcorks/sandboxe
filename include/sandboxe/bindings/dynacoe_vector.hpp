#ifndef h_dynacoe_sandboxe_vector_included
#define h_dynacoe_sandboxe_vector_included



#include <sandboxe/native/native.h>


/*
    Dynacoe::Vector  class bindings.

    Notes:
        - All functions edit the vector itself
        - added "clone()" to generate a copy

 */





namespace Sandboxe {
namespace Bindings {






// functions 

SANDBOXE_NATIVE_DEF(__vector_length) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(v->Length());
}

SANDBOXE_NATIVE_DEF(__vector_clone) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::VectorT);
    *Sandboxe::NativeObject::Get<Dynacoe::Vector>(object) = *v;
    context.SetReturnValue(object); 
}

SANDBOXE_NATIVE_DEF(__vector_to_string) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(
       std::string(Dynacoe::Chain() << "{" << v->x << ", " << v->y << ", " << v->z << "}")
    );    
}

SANDBOXE_NATIVE_DEF(__vector_distance) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->Distance(*src));
}


SANDBOXE_NATIVE_DEF(__vector_normalize) {    
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    v->SetToNormalize();
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_dot) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->Dot(*src));
}

SANDBOXE_NATIVE_DEF(__vector_cross_2D) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->CrossFlat(*src));
}

SANDBOXE_NATIVE_DEF(__vector_cross) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::VectorT);
    *Sandboxe::NativeObject::Get<Dynacoe::Vector>(object) = v->Cross(*src);
    context.SetReturnValue(object);
}


SANDBOXE_NATIVE_DEF(__vector_rotation_x_diff) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->RotationXDiff(*src));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_x_diff_relative) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->RotationXDiffRelative(*src));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_x) {    
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(v->RotationX());
}



SANDBOXE_NATIVE_DEF(__vector_rotation_y_diff) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->RotationYDiff(*src));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_y_diff_relative) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->RotationYDiffRelative(*src));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_y) {    
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(v->RotationY());
}


SANDBOXE_NATIVE_DEF(__vector_rotation_z_diff) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->RotationZDiff(*src));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_z_diff_relative) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();
    context.SetReturnValue(v->RotationZDiffRelative(*src));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_z) {    
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(v->RotationZ());
}



SANDBOXE_NATIVE_DEF(__vector_rotate_x) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    *v = v->RotateX(arguments[0]);
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_rotate_y) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    *v = v->RotateY(arguments[0]);
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_rotate_z) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    *v = v->RotateZ(arguments[0]);
    context.SetReturnValue(source);
}



SANDBOXE_NATIVE_DEF(__vector_rotate_x_from) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);

    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();

    *v = v->RotateXFrom(*src, arguments[1]);
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_rotate_y_from) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);

    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();

    *v = v->RotateYFrom(*src, arguments[1]);
    context.SetReturnValue(source);
}


SANDBOXE_NATIVE_DEF(__vector_rotate_z_from) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(0, VectorT);

    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    Dynacoe::Vector * src = (Dynacoe::Vector *)obj->GetNativeAddress();

    *v = v->RotateZFrom(*src, arguments[1]);
    context.SetReturnValue(source);
}



// managed properties

SANDBOXE_NATIVE_DEF(__vector_x_get) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(v->x);
}

SANDBOXE_NATIVE_DEF(__vector_x_set) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    v->x = arguments[0];
}



SANDBOXE_NATIVE_DEF(__vector_y_get) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(v->y);
}

SANDBOXE_NATIVE_DEF(__vector_y_set) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    v->y = arguments[0];
}


SANDBOXE_NATIVE_DEF(__vector_z_get) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    context.SetReturnValue(v->z);
}

SANDBOXE_NATIVE_DEF(__vector_z_set) {
    Dynacoe::Vector * v = (Dynacoe::Vector *)source->GetNativeAddress();
    v->z = arguments[0];
}






/// global functions
SANDBOXE_NATIVE_DEF(__vector_create_default) {
    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::VectorT);
    context.SetReturnValue(object);
    Dynacoe::Vector * v = Sandboxe::NativeObject::Get<Dynacoe::Vector>(object);
    
    if (arguments.size() == 1) {
        *v = Dynacoe::Vector(arguments[0]);
    } else if (arguments.size() == 2) {
        *v = Dynacoe::Vector(arguments[0], arguments[1]);
    } else if (arguments.size() == 3) {
        *v = Dynacoe::Vector(arguments[0], arguments[1], arguments[2]);
    }
}


void dynacoe_vector(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        Sandboxe::NativeTypeToString(Sandboxe::NativeType::VectorT),
        // methods
        {
            {"length", __vector_length},
            {"clone", __vector_clone},
            {"toString", __vector_to_string},
            {"distance", __vector_distance},
            {"normalize", __vector_normalize}, //< edits current
            {"dot", __vector_dot},
            {"cross2D", __vector_cross_2D},
            {"cross", __vector_cross},
            
            {"rotationXDiff", __vector_rotation_x_diff},
            {"rotationXDiffRelative", __vector_rotation_x_diff_relative},
            {"rotationX", __vector_rotation_x},
            
            {"rotationYDiff", __vector_rotation_y_diff},
            {"rotationYDiffRelative", __vector_rotation_y_diff_relative},
            {"rotationY", __vector_rotation_y},
            
            {"rotationZDiff", __vector_rotation_z_diff},
            {"rotationZDiffRelative", __vector_rotation_z_diff_relative},
            {"rotationZ", __vector_rotation_z},
            
            {"rotateX", __vector_rotate_x},
            {"rotateY", __vector_rotate_y},
            {"rotateZ", __vector_rotate_z},

            {"rotateXFrom", __vector_rotate_x_from},
            {"rotateYFrom", __vector_rotate_y_from},
            {"rotateZFrom", __vector_rotate_z_from},


        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"x", {__vector_x_get, __vector_x_set}},
            {"y", {__vector_y_get, __vector_y_set}},
            {"z", {__vector_z_get, __vector_z_set}}
        }
    );
    
    fns.push_back({"__vector_create_new", __vector_create_default});    
}


}
}

#endif