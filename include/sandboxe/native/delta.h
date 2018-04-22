#ifndef h_sandboxe_delta_included
#define h_sandboxe_delta_included
#include <cassert>
namespace Sandboxe {


static void OnChangeNull(void*,void*){};


// tracks changes of objects with a user-provided callback.
template<typename T>
class Delta {
  public:
    Delta(){Disable();}
    void Set(void(*onChange)(T*,void*), void * data) {
        OnChange = (onChange);
        onChangeData = (data);   
    }
    

    // Calls the change callback with the source and the given data.
    void Changed(T * source) {
        OnChange(source, onChangeData);
    }
    
    // disables this delta, rendering the Changed function useless.
    void Disable() {
        OnChange = (void(*)(T*,void*))OnChangeNull;
    }
    
  private:
    // called when the object changes
    void (*OnChange)(T *, void * data);
    
    // Called when 
    void * onChangeData;
};
    
}


#endif