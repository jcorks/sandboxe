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
    
    struct StateLoopNative {
        StateLoopNative() :
            step(nullptr),
            draw(nullptr),
            init(nullptr){}
            
        Sandboxe::Script::Runtime::Object * step;
        Sandboxe::Script::Runtime::Object * draw;
        Sandboxe::Script::Runtime::Object * init;
    };
    std::vector<StateLoopNative*> loops;
    
    static DynacoeEvent(NativeHandler_Step) {
        auto loop = (StateLoopNative*)functionData;
        Sandboxe::Component::NativeHandler(
            loop->step,
            component,
            self,
            source, 
            args
        );
    }
    
    
    static DynacoeEvent(NativeHandler_Draw) {
        auto loop = (StateLoopNative*)functionData;
        Sandboxe::Component::NativeHandler(
            loop->draw,
            component,
            self,
            source, 
            args
        );
    }

    
    static DynacoeEvent(NativeHandler_Init) {
        auto loop = (StateLoopNative*)functionData;
        Sandboxe::Component::NativeHandler(
            loop->init,
            component,
            self,
            source, 
            args
        );
    }
  public:
    void CreateStateNonNative(
      const Sandboxe::Script::Runtime::Primitive & tag,
      const std::vector<Sandboxe::Script::Runtime::Primitive> & fns
    ) {
        StateLoopNative * loop = new StateLoopNative();
        loops.push_back(loop);
        
        auto step = fns.size() >= 1 ? fns[0] : Sandboxe::Script::Runtime::Primitive();
        auto draw = fns.size() >= 2 ? fns[1] : Sandboxe::Script::Runtime::Primitive();
        auto init = fns.size() >= 3 ? fns[2] : Sandboxe::Script::Runtime::Primitive();
        
        if (step.IsDefined()) {
            AddNonNativeReference(step);
        }
        if (draw.IsDefined()) {
            AddNonNativeReference(draw);
        }
        if (init.IsDefined()) {
            AddNonNativeReference(init);
        }
        
        
        loop->step = step;
        loop->draw = draw;
        loop->init = init;
        
        Dynacoe::StateControl::StateLoop loopReal;
        loopReal.Step = step.IsDefined() ? NativeHandler_Step : nullptr;
        loopReal.Draw = draw.IsDefined() ? NativeHandler_Draw : nullptr;
        loopReal.Init = init.IsDefined() ? NativeHandler_Init : nullptr;
        loopReal.data = loop;
        
        
        
        CreateState(tag, loopReal);
    }
  
};
    
    

    
}


#endif