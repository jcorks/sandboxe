#ifndef h_dynacoe_sandboxe_shader_included
#define h_dynacoe_sandboxe_shader_included



#include <sandboxe/native/native.h>
#include <sandboxe/native/shader.h>

/*
    Dynacoe::Shader  class bindings.

    Notes:
        - Since renderers aren't accessible, GetID() is not bound
        - GetStatus() is now a read-only member "status"
        - GetLog() is now a read-only member "log"
        - GetShaderLanguage() is now a read-only member "shaderLanguage"
 */





namespace Sandboxe {
namespace Bindings {






// functions 

SANDBOXE_NATIVE_DEF(__shader_add_stage) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    auto s = (Sandboxe::ShaderObject *)source;
    int stage = arguments[0];
    if (stage < 0 || stage >= (int)Dynacoe::Shader::Stage::NotAStage) return;
    s->shader.AddStage((Dynacoe::Shader::Stage)stage, arguments[1]);
}

SANDBOXE_NATIVE_DEF(__shader_compile) {
    auto s = (Sandboxe::ShaderObject *)source;
    s->shader.Compile();
}


// properties
SANDBOXE_NATIVE_DEF(__shader_get_log) {
    auto s = (Sandboxe::ShaderObject *)source;
    context.SetReturnValue(s->shader.GetLog());
}

SANDBOXE_NATIVE_DEF(__shader_get_status) {
    auto s = (Sandboxe::ShaderObject *)source;
    context.SetReturnValue((int)s->shader.GetStatus());
}

SANDBOXE_NATIVE_DEF(__shader_get_shader_language) {
    auto s = (Sandboxe::ShaderObject *)source;
    context.SetReturnValue(s->shader.GetShaderLanguage());
}



/// global functions
SANDBOXE_NATIVE_DEF(__shader_create) {
    context.SetReturnValue(new Sandboxe::ShaderObject);
}


void dynacoe_shader(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::ShaderT,
        // methods
        {
            {"addStage", __shader_add_stage},
            {"compile", __shader_compile}

        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"log", {__shader_get_log, SANDBOXE_NATIVE_EMPTY}}, 
            {"status", {__shader_get_status, SANDBOXE_NATIVE_EMPTY}}, 
            {"shaderLanguage", {__shader_get_shader_language, SANDBOXE_NATIVE_EMPTY}}, 

        }
    );
    
    fns.push_back({"__shader_create", __shader_create});    
}


}
}

#endif
