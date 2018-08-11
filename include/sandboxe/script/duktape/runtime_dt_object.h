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
    Object_Internal();
    ~Object_Internal();    

    void AssignHeapEntry();

    // creates a new non-native object proxy to manipulate 
    // the duktape object as a sandboxe object. This object 
    // will also be marked as a "temporary object non-native object".
    // This means that, unless it is added as a non-native reference 
    // through Object::AddNonNativeReference(), it may be cleaned up and 
    // removed by the garbage collector on its own.
    static Object * CreateTemporaryObjectFromStackTop();
    

    // Gets the owning parent of this reference
    Object * GetParent();

    // Sweeps through and removes any temporary object references from the 
    // context heap store. This makes the temporary object eligible for 
    // garbage collection by the duktape context
    static void SweepTemporaryObjects();
    
    // Gets the DTContext heap index for this object. 
    // If the heapIndex is 0, the object has likely been cleaned up already.
    uint32_t GetHeapStoreIndex() const;
 
    
  private:
    int type;
    uint32_t heapIndex;
    Object * parent;
    std::vector<Object*> ownedTemps;

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
