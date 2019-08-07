#ifndef H_dynacoe_sandboxe_filesys_included
#define H_dynacoe_sandboxe_filesys_included

#include <sandboxe/native/native.h>
#include <Dynacoe/Util/Filesys.h>

namespace Sandboxe {
class FilesysObject : public Sandboxe::Script::Runtime::Object {
  public:




    
    Dynacoe::Filesys object;
    
    
    
    FilesysObject(const std::string & initLocation) :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::FilesysT),
        object(initLocation)
    {
    }

    FilesysObject() :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::FilesysT)
    {
    }
    

    
    void OnGarbageCollection() {
    }
    
    
    const char * GetObjectName() const {
        return "Filesys";
    }
    
};
}

#endif
