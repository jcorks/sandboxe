#include <sandboxe/script/runtime.h>
#include <cinttypes>

using Sandboxe::Script::Runtime::Primitive;
using Sandboxe::Script::Runtime::Context;

using Dynacoe::Chain;
static char format_buffer_s[256];

Primitive::Primitive() {
    defined = false;
    hint = TypeHint::StringT;
    nsu = false;
}

Primitive::Primitive(bool in) {
    defined = true;
    intData = in;
    fltData = in;
    hint = TypeHint::BooleanT;
    nsu = true;
}


Primitive::Primitive(int in) {
    defined = true;
    intData = in;
    fltData = in;
    hint = TypeHint::IntegerT;
    nsu = true;
}


Primitive::Primitive(float in) {
    defined = true;
    intData = in;
    fltData = in;
    hint = TypeHint::FloatT;
    nsu = true;
}

Primitive::Primitive(double in) {
    defined = true;
    intData = in;
    fltData = in;
    hint = TypeHint::DoubleT;
    nsu = true;
}

Primitive::Primitive(uint32_t in) {
    defined = true;
    intData = in;
    fltData = in;
    hint = TypeHint::UInt32T;
    nsu = true;
}

Primitive::Primitive(uint64_t in) {
    defined = true;
    intData = in;
    fltData = in;
    hint = TypeHint::UInt64T;
    nsu = true;
}



Primitive::Primitive(const std::string & str) {
    defined = true;
    data = str;
    hint = TypeHint::StringT;
    nsu = false;
}



Primitive::Primitive(Sandboxe::Script::Runtime::Object * in) {
    defined = true;
    objectData = in;
    hint = in->IsNative() ? TypeHint::ObjectReferenceT : TypeHint::ObjectReferenceNonNativeT;;
    nsu = true;
}



Primitive::operator int() const {
    return intData;
}

Primitive::operator bool() const {
    return intData;
}

Primitive::operator float() const {
    return fltData;
}

Primitive::operator double() const {
    return fltData;
}

Primitive::operator uint32_t() const {
    return intData;
}

Primitive::operator uint64_t() const {
    return intData;
}


Primitive::operator std::string() const {
    if (nsu) {
        switch(hint) {
          case TypeHint::StringT:
            break;
          case TypeHint::UInt32T:
          case TypeHint::IntegerT:
            snprintf(format_buffer_s, 255, "%" PRIu64, intData);
            *((std::string*)&data) = std::string(format_buffer_s);
            break;
            
          case TypeHint::BooleanT:
            *((std::string*)&data) = intData ? "true" : "false";
            break;

          case TypeHint::FloatT:
          case TypeHint::DoubleT:
            snprintf(format_buffer_s, 255, "%f", fltData);
            *((std::string*)&data) = std::string(format_buffer_s);
            break;

          case TypeHint::ObjectReferenceT:
          case TypeHint::ObjectReferenceNonNativeT:
            *((std::string*)&data) = (Chain() << (uint64_t)objectData);
        }
        *((bool*)&nsu) = false;
    }
    return data;
}


Primitive::operator Sandboxe::Script::Runtime::Object * () const {
    return objectData;
}




Context::~Context() {
    if (inputArray) {
        delete inputArray;
    }
}

void Context::SetArrayArgument(uint32_t arg, const std::vector<Primitive> & args) {
    if (!inputArray) {
        inputArray = new std::vector<std::vector<Primitive>>();
    }
    while(arg >= inputArray->size()) {
        inputArray->push_back({});
    }
    (*inputArray)[arg] = args;
}


std::vector<Primitive> * Context::GetArrayArgument(uint32_t arg) {
    if (!inputArray) return nullptr;
    if (arg >= inputArray->size()) return nullptr;
    return &(*inputArray)[arg]; 
}


void Sandboxe::Script::Runtime::Empty(Sandboxe::Script::Runtime::Object * source, const std::vector<Sandboxe::Script::Runtime::Primitive> & arguments, Sandboxe::Script::Runtime::Context & context){}





