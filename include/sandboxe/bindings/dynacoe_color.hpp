#ifndef dynacoe_color_sandboxe_binding_included
#define dynacoe_color_sandboxe_binding_included

#include <sandboxe/native/native.h>
#include <sandboxe/native/color.h>



/* 

    Bindings for Dynacoe::Color
    Notes:
        - Float only!
        - can clone 



*/

namespace Sandboxe {
namespace Bindings {
    

// managed properties

void argument_to_color_object(Dynacoe::Color & dest, const Sandboxe::Script::Runtime::Primitive & arg) {
    switch(arg.hint) {
      case Sandboxe::Script::Runtime::Primitive::TypeHint::ObjectReferenceT:; {
        // trye to get a color object, if possible
            auto src = dynamic_cast<Sandboxe::ColorObject*>((Sandboxe::Script::Runtime::Object*)arg);
            if (src) {
                dest = src->color;
            }
            break;
        }
      default:
        dest = Dynacoe::Color(std::string(arg));
        
    }
}

SANDBOXE_NATIVE_DEF(__color_set) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto t = (Sandboxe::ColorObject*)source;
    argument_to_color_object(t->color, arguments[0]);
}


SANDBOXE_NATIVE_DEF(__color_r_get) {
    auto t = (Sandboxe::ColorObject*)source;
    context.SetReturnValue((float)t->color.r);
}

SANDBOXE_NATIVE_DEF(__color_r_set) {
    auto t = (Sandboxe::ColorObject*)source;
    t->color.r = (float)arguments[0];
    t->delta.Changed(t);
}

SANDBOXE_NATIVE_DEF(__color_g_get) {
    auto t = (Sandboxe::ColorObject*)source;
    context.SetReturnValue((float)t->color.g);
}

SANDBOXE_NATIVE_DEF(__color_g_set) {
    auto t = (Sandboxe::ColorObject*)source;
    t->color.g = (float)arguments[0];
    t->delta.Changed(t);

}

SANDBOXE_NATIVE_DEF(__color_b_get) {
    auto t = (Sandboxe::ColorObject*)source;
    context.SetReturnValue((float)t->color.b);
}

SANDBOXE_NATIVE_DEF(__color_b_set) {
    auto t = (Sandboxe::ColorObject*)source;
    t->color.b = (float)arguments[0];
    t->delta.Changed(t);
}


SANDBOXE_NATIVE_DEF(__color_a_get) {
    auto t = (Sandboxe::ColorObject*)source;
    context.SetReturnValue((float)t->color.a);
}

SANDBOXE_NATIVE_DEF(__color_a_set) {
    auto t = (Sandboxe::ColorObject*)source;
    t->color.a = (float)arguments[0];
    t->delta.Changed(t);
}


SANDBOXE_NATIVE_DEF(__color_to_string) {
    auto t = (Sandboxe::ColorObject*)source;
    context.SetReturnValue(t->color.ToString());
}

SANDBOXE_NATIVE_DEF(__color_clone) {
    auto src = (Sandboxe::ColorObject*)source;

    auto t = new Sandboxe::ColorObject;
    t->color = src->color;
    context.SetReturnValue(t);
}




/// global functions
SANDBOXE_NATIVE_DEF(__color_create) {
    auto t = new Sandboxe::ColorObject;
    if (arguments.size() == 1) {
        t->color = Dynacoe::Color(std::string(arguments[0]));
    } else if (arguments.size() == 3){
        t->color = Dynacoe::Color((float)arguments[0], (float)arguments[1], (float)arguments[2]);
    } else if (arguments.size() == 4) {
        t->color = Dynacoe::Color((float)arguments[0], (float)arguments[1], (float)arguments[2], (float)arguments[3]);
    }
    context.SetReturnValue(t);
}


void dynacoe_color(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::ColorT,
        // methods
        {
            {"toString", __color_to_string},
            {"clone", __color_clone},
            {"set", __color_set}
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"r", {__color_r_get, __color_r_set}},
            {"g", {__color_g_get, __color_g_set}},
            {"b", {__color_b_get, __color_b_set}},
            {"a", {__color_a_get, __color_a_set}},
            
            {"red", {__color_r_get, __color_r_set}},
            {"green", {__color_g_get, __color_g_set}},
            {"blue", {__color_b_get, __color_b_set}},
            {"alpha", {__color_a_get, __color_a_set}}

        } 
    );
    
    fns.push_back({"__color_create", __color_create});    
}
    
    
    
}
}




#endif