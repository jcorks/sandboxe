#include <sandboxe/script/runtime.h>

using Sandboxe::Script::Runtime::Primitive;
using Sandboxe::Script::Runtime::Context;

using Dynacoe::Chain;

Primitive::Primitive() {
    defined = false;
    hint = TypeHint::StringT;
}

Primitive::Primitive(bool in) {
    defined = true;
    data = in ? "1" : "0";
    hint = TypeHint::BooleanT;
}


Primitive::Primitive(int in) {
    defined = true;
    data = (Chain() << in);
    hint = TypeHint::IntegerT;

}


Primitive::Primitive(float in) {
    defined = true;
    data = (Chain() << in);
    hint = TypeHint::FloatT;
}

Primitive::Primitive(double in) {
    defined = true;
    data = (Chain() << in);
    hint = TypeHint::DoubleT;
}

Primitive::Primitive(uint32_t in) {
    defined = true;
    data = (Chain() << in);
    hint = TypeHint::UInt32T;
}

Primitive::Primitive(uint64_t in) {
    defined = true;
    data = (Chain() << in);
    hint = TypeHint::UInt64T;
}

Primitive::Primitive(const std::string & str) {
    defined = true;
    data = str;
    hint = TypeHint::StringT;
}



Primitive::Primitive(Sandboxe::Script::Runtime::Object * in) {
    defined = true;
    data = (Chain() << (uint64_t)in);
    hint = in->IsNative() ? TypeHint::ObjectReferenceT : TypeHint::ObjectReferenceNonNativeT;
}



Primitive::operator int() const {
    return (Chain() << data).AsInt();
}

Primitive::operator bool() const {
    if (data == "true") return 1;
    if (data == "false") return 0;
    return (Chain() << data).AsInt() != 0;
}

Primitive::operator float() const {
    return (Chain() << data).AsFloat();
}

Primitive::operator double() const {
    return (Chain() << data).AsDouble();
}

Primitive::operator uint32_t() const {
    return (Chain() << data).AsUInt32();
}

Primitive::operator uint64_t() const {
    return (Chain() << data).AsUInt64();
}

Primitive::operator std::string() const {
    return data;
}


Primitive::operator Sandboxe::Script::Runtime::Object * () const {
    return (Sandboxe::Script::Runtime::Object*)(Chain() << data).AsUInt64();
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







