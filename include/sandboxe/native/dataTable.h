#ifndef h_dynacoe_sandboxe_data_table_included
#define h_dynacoe_sandboxe_data_table_included


#include <sandboxe/native/component.h>
#include <Dynacoe/Components/DataTable.h>

namespace Sandboxe {


class DataTableObject : public Dynacoe::DataTable, public Sandboxe::ComponentAdaptor {
  public:
    
    DataTableObject() : Dynacoe::DataTable(), Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::DataTableT) {}
    

    
    void OnGarbageCollection() {
        
    }
    
    void OnStep() {
        Native_OnStep();
    }

    void OnDraw() {
        Native_OnDraw();
    }

    const char * GetObjectName() const {
        return "DataTable";
    }

    
    #include "component_implementation_common"
    
    
    
};
    
    

    
}


#endif