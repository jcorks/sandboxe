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



  private:
    duk_context * source;
};
