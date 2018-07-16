#ifndef H_dynacoe_sandboxe_display_included
#define H_dynacoe_sandboxe_display_included

namespace Sandboxe {
class DisplayObject : public Sandboxe::Script::Runtime::Object {
  public:

    class NonNativeResizeCallback : public Dynacoe::Display::ResizeCallback {
      public:
        virtual ~NonNativeResizeCallback(){};
        NonNativeResizeCallback(DisplayObject * d) : parent(d) {}
        DisplayObject * parent;
        void operator()(int nw, int nh) {
            parent->CallMethod("onResize", {nw, nh});
        }
    };

    class NonNativeCloseCallback : public Dynacoe::Display::CloseCallback {
      public:
        virtual ~NonNativeCloseCallback(){};
        NonNativeCloseCallback(DisplayObject * d) : parent(d) {}
        DisplayObject * parent;
        void operator()() {
            parent->CallMethod("onClose", {});
        }
    };


    
    Dynacoe::ViewID id;
    NonNativeResizeCallback * resizeCB;
    NonNativeCloseCallback * closeCB;
    
    
    DisplayObject(const Dynacoe::ViewID & id_) :
        Sandboxe::Script::Runtime::Object((int)Sandboxe::NativeType::DisplayT)
    {
        resizeCB = new NonNativeResizeCallback(this);
        closeCB = new NonNativeCloseCallback(this);
        id = id_;
        
        auto disp = Dynacoe::ViewManager::Get(id);
        disp->AddResizeCallback(resizeCB);
        disp->AddCloseCallback(closeCB);
        
    }
    
    void OnGarbageCollection() {
        delete resizeCB;
        delete closeCB;
    }
    
    
    const char * GetObjectName() const {
        return "StateControl";
    }
    
};
}

#endif
