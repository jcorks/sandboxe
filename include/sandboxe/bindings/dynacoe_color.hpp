#ifndef dynacoe_color_sandboxe_binding_included
#define dynacoe_color_sandboxe_binding_included

#include <sandboxe/native/native.h>



/* 

    Bindings for Dynacoe::Color
    Notes:
        - Float only!
        - can clone 



*/

namespace Sandboxe {
namespace Bindings {
    

// managed properties



SANDBOXE_NATIVE_DEF(__color_r_get) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    context.SetReturnValue((float)t->r);
}

SANDBOXE_NATIVE_DEF(__color_r_set) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    t->r = (float)arguments[0];
}

SANDBOXE_NATIVE_DEF(__color_g_get) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    context.SetReturnValue((float)t->g);
}

SANDBOXE_NATIVE_DEF(__color_g_set) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    t->g = (float)arguments[0];
}

SANDBOXE_NATIVE_DEF(__color_b_get) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    context.SetReturnValue((float)t->b);
}

SANDBOXE_NATIVE_DEF(__color_b_set) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    t->b = (float)arguments[0];
}


SANDBOXE_NATIVE_DEF(__color_a_get) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    context.SetReturnValue((float)t->a);
}

SANDBOXE_NATIVE_DEF(__color_a_set) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    t->a = (float)arguments[0];
}


SANDBOXE_NATIVE_DEF(__color_to_string) {
    Dynacoe::Color * t = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);
    context.SetReturnValue(t->ToString());
}

SANDBOXE_NATIVE_DEF(__color_clone) {
    Dynacoe::Color * src = Sandboxe::NativeObject::Get<Dynacoe::Color>(source);

    auto t = Sandboxe::NativeObject::New(Sandboxe::NativeType::ColorT);
    Dynacoe::Color * color = Sandboxe::NativeObject::Get<Dynacoe::Color>(t);

    *color = *src;
    context.SetReturnValue(t);
}




/// global functions
SANDBOXE_NATIVE_DEF(__color_create) {
    auto t = Sandboxe::NativeObject::New(Sandboxe::NativeType::ColorT);
    Dynacoe::Color * color = Sandboxe::NativeObject::Get<Dynacoe::Color>(t);
    if (arguments.size() == 1) {
        *color = Dynacoe::Color(std::string(arguments[0]));
    } else if (arguments.size() == 3){
        *color = Dynacoe::Color((float)arguments[0], (float)arguments[1], (float)arguments[2]);
    } else if (arguments.size() == 2) {
        *color = Dynacoe::Color((float)arguments[0], (float)arguments[1], (float)arguments[2], (float)arguments[3]);
    }
    context.SetReturnValue(t);
}


void dynacoe_color(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        Sandboxe::NativeTypeToString(Sandboxe::NativeType::ColorT),
        // methods
        {
            {"toString", __color_to_string},
            {"clone", __color_clone},
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