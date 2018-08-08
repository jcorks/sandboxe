
// symbolic wrapper for the topmost object on the duk stack
class TObject {
  public:
    TObject(duk_context * ctx) : source(ctx) {
        assert(duk_get_top(source));
    }

    std::string Get(const std::string & str) const {
        int stackSz = (duk_get_top(source));

        duk_get_prop_string(source, -1, str.c_str());      
        const char * prop = duk_safe_to_string(source, -1); 
        std::string out(prop ? prop : "");
        duk_pop(source);

        assert(stackSz == duk_get_top(source));
        return out;
    }


    // sets a hidden property pointer that is accessible via pointer
    void MapPointer(void * key, void * value) const {
        int stackSz = (duk_get_top(source));

        duk_push_pointer(source, value);
        duk_put_prop_string(source, -2, PointerToHiddenKey(key));
        

        assert(stackSz == duk_get_top(source));                
    }


    void * GetMappedPointer(void * key) {
        int stackSz = (duk_get_top(source));

        duk_get_prop_string(source, -1, PointerToHiddenKey(key));      
        void * prop = duk_to_pointer(source, -1); 
        duk_pop(source);
        

        assert(stackSz == duk_get_top(source));
        return prop;
    }



    Sandboxe::Script::Runtime::Primitive GetAsPrimitive() {
        switch(duk_get_type(source, -1)) {
            case DUK_TYPE_NONE:      return Primitive();
            case DUK_TYPE_UNDEFINED: return Primitive();
            case DUK_TYPE_NULL:      return Primitive();
            case DUK_TYPE_BOOLEAN:   return Primitive(duk_get_boolean(source, -1));
            case DUK_TYPE_NUMBER:    return Primitive(duk_get_number(source, -1));
            case DUK_TYPE_STRING:    return Primitive(std::string(duk_get_string(source, -1)));
            case DUK_TYPE_OBJECT:    return Primitive();
            case DUK_TYPE_BUFFER:    return Primitive(); // no generic implementation
            case DUK_TYPE_POINTER:   return Primitive(); // hidden property
            case DUK_TYPE_LIGHTFUNC: return Primitive(std::string(duk_get_string(source, -1))); // function?

        }


        return Primitive();
    }


  private:
    duk_context * source;

    const char * PointerToHiddenKey(void * p) const {
        static char holder[34];
        snprintf(holder, 34, "\xFF%p", p);
        return holder;
    }

};
