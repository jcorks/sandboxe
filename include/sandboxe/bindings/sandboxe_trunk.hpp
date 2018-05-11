#ifndef H_sandboxe_bindings_dynacoe_trunk
#define H_sandboxe_bindings_dynacoe_trunk
#include <sandboxe/native/native.h>
#include <sandboxe/trunk.h>


/*
    Bindings for Sandboxe::Trunk

    Trunk usage support:
        - Asset loading

 */

namespace Sandboxe {
namespace Bindings {



SANDBOXE_NATIVE_DEF(__trunk_commit) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    context.SetReturnValue(Sandboxe::Trunk::Commit(arguments[0]));
}

SANDBOXE_NATIVE_DEF(__trunk_stage) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::Trunk::Stage(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__trunk_remove) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    Sandboxe::Trunk::Remove(arguments[0]);
}

SANDBOXE_NATIVE_DEF(__trunk_query) {
    auto list = Sandboxe::Trunk::Query();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < list.size(); ++i) {
        out.push_back(list[i]);
    }
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__trunk_clear) {
    Sandboxe::Trunk::Clear();
}



void sandboxe_trunk(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    fns.push_back({"__trunk_commit", __trunk_commit});
    fns.push_back({"__trunk_stage", __trunk_stage});
    fns.push_back({"__trunk_remove", __trunk_remove});
    fns.push_back({"__trunk_query", __trunk_query});
    fns.push_back({"__trunk_clear", __trunk_clear});


}

}
}



#endif