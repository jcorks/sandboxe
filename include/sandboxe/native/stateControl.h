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
    
    struct StateBlock {
      Sandboxe::Script::Runtime::Object * stepSrc;
      Sandboxe::Script::Runtime::Object * drawSrc;    
      Sandboxe::Script::Runtime::Object * initSrc;        
    };

    std::vector<StateBlock *> loops;
    

    
    static DynacoeEvent(NativeHandler_Step) {
        auto loop = (StateBlock *)functionData;
        loop->stepSrc->CallMethod();
        return true;
    }
    
    static DynacoeEvent(NativeHandler_Draw) {
        auto loop = (StateBlock *)functionData;
        loop->drawSrc->CallMethod();
        return true;
    }

    static DynacoeEvent(NativeHandler_Init) {
        auto loop = (StateBlock *)functionData;
        loop->initSrc->CallMethod();
        return true;
    }
    
    
  public:
      
    void CreateStateNonNative(
      const Sandboxe::Script::Runtime::Primitive & tag,
      const Sandboxe::Script::Runtime::Primitive & initSrcP,
      const Sandboxe::Script::Runtime::Primitive & stepSrcP,
      const Sandboxe::Script::Runtime::Primitive & drawSrcP
    ) {
        StateBlock * block = new StateBlock;
        

        
        block->stepSrc = (stepSrcP.hint == Sandboxe::Script::Runtime::Primitive::TypeHint::ObjectReferenceNonNativeT) ? (Sandboxe::Script::Runtime::Object *)stepSrcP : nullptr;
        block->drawSrc = (drawSrcP.hint == Sandboxe::Script::Runtime::Primitive::TypeHint::ObjectReferenceNonNativeT) ? (Sandboxe::Script::Runtime::Object *)drawSrcP : nullptr;
        block->initSrc = (initSrcP.hint == Sandboxe::Script::Runtime::Primitive::TypeHint::ObjectReferenceNonNativeT) ? (Sandboxe::Script::Runtime::Object *)initSrcP : nullptr;

        if (block->stepSrc) AddNonNativeReference(block->stepSrc);        
        if (block->drawSrc) AddNonNativeReference(block->drawSrc);        
        if (block->initSrc) AddNonNativeReference(block->initSrc);        

        Dynacoe::StateControl::StateLoop loopReal;
        loopReal.Step = block->stepSrc ? NativeHandler_Step : nullptr;
        loopReal.Draw = block->drawSrc ? NativeHandler_Draw : nullptr;
        loopReal.Init = block->initSrc ? NativeHandler_Init : nullptr;
        loopReal.data = block;
        
        if (loopReal.Step == loopReal.Draw &&
            loopReal.Step == loopReal.Init) {
            
            Sandboxe::Script::Runtime::ScriptError("State " + std::string(tag) + " has neither onStep, onDraw, nor onInit defined.");
        }
        
        loops.push_back(block);
        
        CreateState(tag, loopReal);
    }
  
};
    
    

    
}


#endif
