#ifndef H_sandboxe_bindings_dynacoe_engine
#define H_sandboxe_bindings_dynacoe_engine
#include <sandboxe/native/native.h>
#include <Dynacoe/Util/Time.h>

namespace Sandboxe {
namespace Bindings {

SANDBOXE_NATIVE_DEF(__engine_set_root) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, EntityObjectID);

    
    const Dynacoe::Entity::ID & other = ((Sandboxe::EntityObjectID*)(Sandboxe::Script::Runtime::Object*)arguments[0])->id;
    Dynacoe::Engine::Root() = other;
    context.SetReturnValue(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__engine_get_root) {
    auto ent = Dynacoe::Engine::Root().IdentifyAs<Sandboxe::Entity>();
    if (!ent) {
        return;
    }
    context.SetReturnValue(ent->object);
}

SANDBOXE_NATIVE_DEF(__engine_attach_manager) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, EntityObjectID);

    
    const Dynacoe::Entity::ID & other = ((Sandboxe::EntityObjectID*)(Sandboxe::Script::Runtime::Object*)arguments[0])->id;
    Dynacoe::Engine::AttachManager(other);
}

SANDBOXE_NATIVE_DEF(__engine_quit) {
    Dynacoe::Engine::Quit();
}

SANDBOXE_NATIVE_DEF(__engine_set_max_fps) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Dynacoe::Engine::SetMaxFPS(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__engine_get_base_directory) {
    context.SetReturnValue(Dynacoe::Engine::GetBaseDirectory());
}

SANDBOXE_NATIVE_DEF(__engine_version) {
    context.SetReturnValue(Dynacoe::Engine::Version());
}

SANDBOXE_NATIVE_DEF(__engine_get_total_time) {
    context.SetReturnValue(Dynacoe::Time::MsSinceStartup());
}

void dynacoe_engine(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    fns.push_back({"__engine_set_root", __engine_set_root});
    fns.push_back({"__engine_get_root", __engine_get_root});
    fns.push_back({"__engine_quit", __engine_quit});
    fns.push_back({"__engine_set_max_fps", __engine_set_max_fps});
    fns.push_back({"__engine_get_total_time", __engine_get_total_time});
    fns.push_back({"__engine_get_base_directory", __engine_get_base_directory});
    fns.push_back({"__engine_attach_manager", __engine_attach_manager});
    fns.push_back({"__engine_version", __engine_version});

}

}
}



#endif