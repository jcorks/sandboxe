#ifndef H_SANDBOXE_DT_OBJECT_INCLUDED
#define H_SANDBOXE_DT_OBJECT_INCLUDED

#include <sandboxe/script/runtime.h>

namespace Sandboxe {
namespace Script {
namespace Runtime {


// Internal representation of a runtime object that interfades with duktap primitives
class Object_Internal {
  public:


    Object_Internal(int typeID, Object * parent_);    
    ~Object_Internal();    
    

    // Gets the owning parent of this reference
    Object * GetParent();

 
    
  private:
    int type;
    uint32_t heapIndex;
    Object * parent;


  public:
   // inherited!
    Primitive Get(const std::string & name);
    void Set(const std::string & name, const Primitive &);
    Primitive CallMethod(const std::string & name = "", const std::vector<Primitive> & args = {});
    bool IsNative() const;
    int GetTypeID() const;

    
    uint32_t AddNonNativeReference(Object * ref);
    void UpdateNonNativeReference(Object *, uint32_t index = 0);
    Object * GetNonNativeReference(uint32_t index = 0) const;
    // inherited!



};


}
}
}


#endif
