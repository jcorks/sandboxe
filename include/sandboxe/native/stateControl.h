#ifndef h_dynacoe_sandboxe_state_control_included
#define h_dynacoe_sandboxe_state_control_included


#include <sandboxe/native/component.h>



namespace Sandboxe {




class StateControlObject : public Dynacoe::StateControl, public Sandboxe::ComponentAdaptor {
  public:
    
    // a native-form StateLoop that holds callable objects in place of functions for the stateloop

    
    StateControlObject() : 
        Sandboxe::ComponentAdaptor((int)Sandboxe::NativeType::StateControlT){}

    ~StateControlObject() {
        for(uint32_t i = 0; i < loops.size(); ++i) {
            delete loops[i];
        }
    }
    

    
    void OnGarbageCollection() {
        
    }
    
    
    const char * GetObjectName() const {
        return "StateControl";
    }


    
    
    
    #include "component_implementation_common"
    
  private:
    

    std::vector<Sandboxe::Script::Runtime::Object *> loops;
    
    static DynacoeEvent(NativeHandler_Step) {
        auto loop = (Sandboxe::Script::Runtime::Object *)functionData;
        loop->CallMethod("onStep");
        return true;
    }
    
    
    static DynacoeEvent(NativeHandler_Draw) {
        auto loop = (Sandboxe::Script::Runtime::Object *)functionData;
        loop->CallMethod("onDraw");
        return true;
    }

    
    static DynacoeEvent(NativeHandler_Init) {
        auto loop = (Sandboxe::Script::Runtime::Object *)functionData;
        loop->CallMethod("onInit");
        return true;
    }
  public:
    void CreateStateNonNative(
      const Sandboxe::Script::Runtime::Primitive & tag,
      const Sandboxe::Script::Runtime::Primitive & fnBlock
    ) {
        Sandboxe::Script::Runtime::Object * obj = fnBlock;
        loops.push_back(obj);

        AddNonNativeReference(obj);        
                
        Dynacoe::StateControl::StateLoop loopReal;
        loopReal.Step = NativeHandler_Step;
        loopReal.Draw = NativeHandler_Draw;
        loopReal.Init = NativeHandler_Init;
        loopReal.data = obj;
        
        
        
        CreateState(tag, loopReal);
    }
  
};
    
    

    
}


#endif
