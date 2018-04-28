#ifndef H_sandboxe_bindings_dynacoe_view_manager
#define H_sandboxe_bindings_dynacoe_view_manager
#include <sandboxe/native/native.h>
#include <sandboxe/native/display.h>

/*
    Dynacoe::ViewManager Bindings
    
    notes:
        - Convenience functions are left out
        - Retrieval has not been bound

*/

namespace Sandboxe {
namespace Bindings {

SANDBOXE_NATIVE_DEF(__view_manager_create_display) {
    std::string name = "";
    int w = 640;
    int h = 480;
    if (arguments.size() > 0) {
        name = (std::string)arguments[0];
    }
    if (arguments.size() > 1) {
        w = arguments[1];
    }
    if (arguments.size() > 2) {
        h = arguments[2];
    }

    auto out = new Sandboxe::DisplayObject(
        Dynacoe::ViewManager::New(name, w, h)
    );
    context.SetReturnValue(out);
}


SANDBOXE_NATIVE_DEF(__view_manager_destroy_display) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, DisplayObject);
    
    auto disp = (Sandboxe::DisplayObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    
    Dynacoe::ViewManager::Destroy(disp->id);
}

SANDBOXE_NATIVE_DEF(__view_manager_set_main) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    SANDBOXE_ASSERT__ARG_TYPE(0, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE(0, DisplayObject);
    
    auto disp = (Sandboxe::DisplayObject*)(Sandboxe::Script::Runtime::Object*)arguments[0];
    
    Dynacoe::ViewManager::SetMain(disp->id);
}


void dynacoe_view_manager(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {

    fns.push_back({"__view_manager_create_display", __view_manager_create_display});
    fns.push_back({"__view_manager_destroy_display", __view_manager_destroy_display});
    fns.push_back({"__view_manager_set_main", __view_manager_set_main});


}

}
}



#endif