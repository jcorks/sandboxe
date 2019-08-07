#ifndef dynacoe_filesys_sandboxe_binding_included
#define dynacoe_filesys_sandboxe_binding_included


#include <sandboxe/native/native.h>
#include <sandboxe/native/filesys.h>

/*
    Dynacoe::Filesys  class bindings.

    Notes:
        - The directory object is integrated into this implementation.
          Any directory functions are implemented as if they were referenced 
          from the current directory
        - directory file functions are condensed into getObjects();
        - QueryDirectory() -> directory property
        - GetCWD() -> cwd
        - the Find*() class of functions are not implemented
        - CreateDirectory is not implemented.

 */





namespace Sandboxe {
namespace Bindings {





// functions 

SANDBOXE_NATIVE_DEF(__filesys_change_dir) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto fs = (Sandboxe::FilesysObject*)source;
    fs->object.ChangeDir(arguments[0]);
    
}

SANDBOXE_NATIVE_DEF(__filesys_go_to_child) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto fs = (Sandboxe::FilesysObject*)source;
    context.SetReturnValue(fs->object.GoToChild(arguments[0]));
    
}

SANDBOXE_NATIVE_DEF(__filesys_go_to_parent) {
    auto fs = (Sandboxe::FilesysObject*)source;
    context.SetReturnValue(fs->object.GoToParent());    
}

SANDBOXE_NATIVE_DEF(__filesys_get_names) {
    auto fs = (Sandboxe::FilesysObject*)source;
    Dynacoe::Filesys::Directory d = fs->object.QueryDirectory();
    std::vector<Sandboxe::Script::Runtime::Primitive> out;

    auto size = d.Size();
    for(int i = 0; i < size; ++i) {
        out.push_back(d.GetNextName());
    }
    context.SetReturnArray(out);    
}


SANDBOXE_NATIVE_DEF(__filesys_query) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto fs = (Sandboxe::FilesysObject*)source;
    context.SetReturnValue(fs->object.QueryDirectory().Query(arguments[0]));    
}

SANDBOXE_NATIVE_DEF(__filesys_is_file) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    auto fs = (Sandboxe::FilesysObject*)source;
    context.SetReturnValue(fs->object.QueryDirectory().IsFile(arguments[0]));    
}


// managed properties


SANDBOXE_NATIVE_DEF(__filesys_cwd_get) {
    auto fs = (Sandboxe::FilesysObject*)source;
    context.SetReturnValue(fs->object.GetCWD());
}



/// global functions
SANDBOXE_NATIVE_DEF(__filesys_create_new) {
    Sandboxe::FilesysObject * object = nullptr;
    
    if (arguments.size() == 1) {
        object = new Sandboxe::FilesysObject(arguments[0]);
    } else {
        object = new Sandboxe::FilesysObject();
    }
    context.SetReturnValue(object);

}


void dynacoe_filesys(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    Sandboxe::Script::Runtime::AddType(
        (int)Sandboxe::NativeType::FilesysT,
        // methods
        {
            {"changeDir", __filesys_change_dir},
            {"goToChild", __filesys_go_to_child},
            {"goToParent", __filesys_go_to_parent},
            {"getNames", __filesys_get_names},
            {"query", __filesys_query},
            {"isFile", __filesys_is_file}

        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"cwd", {__filesys_cwd_get, SANDBOXE_NATIVE_EMPTY}},
        }
    );
    
    fns.push_back({"__filesys_create_new", __filesys_create_new});    
}


}
}

#endif
