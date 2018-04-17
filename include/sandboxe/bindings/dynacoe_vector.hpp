#ifndef h_dynacoe_sandboxe_vector_included
#define h_dynacoe_sandboxe_vector_included



#include <sandboxe/native/native.h>
#include <sandboxe/native/vector.h>

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
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    context.SetReturnValue(v->vector.Length());
}

SANDBOXE_NATIVE_DEF(__vector_clone) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    auto object = new Sandboxe::VectorObject(v->vector);
    context.SetReturnValue(object); 
}

static char vecStringBuffer[1024];
SANDBOXE_NATIVE_DEF(__vector_to_string) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    vecStringBuffer[0] = 0;
    sprintf(vecStringBuffer, "{%f, %f, %f}",
        v->vector.x,
        v->vector.y,
        v->vector.z
    );

    context.SetReturnValue(std::string(vecStringBuffer));    
}

SANDBOXE_NATIVE_DEF(__vector_distance) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);
    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.Distance(src->vector));
}


SANDBOXE_NATIVE_DEF(__vector_normalize) {    
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    v->vector.SetToNormalize();
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_dot) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

        
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.Dot(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_cross_2D) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.CrossFlat(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_cross) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    auto object = new Sandboxe::VectorObject();

    v->vector = v->vector.Cross(src->vector);
    context.SetReturnValue(object);
}


SANDBOXE_NATIVE_DEF(__vector_rotation_x_diff) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.RotationXDiff(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_x_diff_relative) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.RotationXDiffRelative(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_x) {    
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    context.SetReturnValue(v->vector.RotationX());
}



SANDBOXE_NATIVE_DEF(__vector_rotation_y_diff) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.RotationYDiff(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_y_diff_relative) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.RotationYDiffRelative(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_y) {    
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    context.SetReturnValue(v->vector.RotationY());
}


SANDBOXE_NATIVE_DEF(__vector_rotation_z_diff) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.RotationZDiff(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_z_diff_relative) {
    SANDBOXE_ASSERT__ARG_COUNT(1)
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;
    context.SetReturnValue(v->vector.RotationZDiffRelative(src->vector));
}

SANDBOXE_NATIVE_DEF(__vector_rotation_z) {    
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    context.SetReturnValue(v->vector.RotationZ());
}



SANDBOXE_NATIVE_DEF(__vector_rotate_x) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    v->vector = v->vector.RotateX(arguments[0]);
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_rotate_y) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    v->vector = v->vector.RotateY(arguments[0]);
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_rotate_z) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    v->vector = v->vector.RotateZ(arguments[0]);
    context.SetReturnValue(source);
}



SANDBOXE_NATIVE_DEF(__vector_rotate_x_from) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;

    v->vector = v->vector.RotateXFrom(src->vector, arguments[1]);
    context.SetReturnValue(source);
}

SANDBOXE_NATIVE_DEF(__vector_rotate_y_from) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;

    v->vector = v->vector.RotateYFrom(src->vector, arguments[1]);
    context.SetReturnValue(source);
}


SANDBOXE_NATIVE_DEF(__vector_rotate_z_from) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, VectorObject);

    
    Sandboxe::Script::Runtime::Object * obj = arguments[0];
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    Sandboxe::VectorObject * src = (Sandboxe::VectorObject*)obj;

    v->vector = v->vector.RotateZFrom(src->vector, arguments[1]);
    context.SetReturnValue(source);
}



// managed properties

SANDBOXE_NATIVE_DEF(__vector_x_get) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    context.SetReturnValue(v->vector.x);
}

SANDBOXE_NATIVE_DEF(__vector_x_set) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    v->vector.x = arguments[0];
}



SANDBOXE_NATIVE_DEF(__vector_y_get) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    context.SetReturnValue(v->vector.y);
}

SANDBOXE_NATIVE_DEF(__vector_y_set) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    v->vector.y = arguments[0];
}


SANDBOXE_NATIVE_DEF(__vector_z_get) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    context.SetReturnValue(v->vector.z);
}

SANDBOXE_NATIVE_DEF(__vector_z_set) {
    Sandboxe::VectorObject * v = (Sandboxe::VectorObject*)source;
    v->vector.z = arguments[0];
}






/// global functions
SANDBOXE_NATIVE_DEF(__vector_create_default) {
    Sandboxe::VectorObject * object = nullptr;
    
    if (arguments.size() == 1) {
        object = new Sandboxe::VectorObject(Dynacoe::Vector(arguments[0]));
    } else if (arguments.size() == 2) {
        object = new Sandboxe::VectorObject(Dynacoe::Vector(arguments[0], arguments[1]));
    } else if (arguments.size() == 3) {
        object = new Sandboxe::VectorObject(Dynacoe::Vector(arguments[0], arguments[1], arguments[2]));
    } else {
        object = new Sandboxe::VectorObject();
    }
    context.SetReturnValue(object);

}


void dynacoe_vector(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::VectorT,
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
