#include <sandboxe/script/runtime.h>

using Sandboxe::Script::Runtime::Primitive;
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

Primitive::Primitive(const Dynacoe::Entity::ID & in) {
    defined = true;
    data = in.String();
    hint = TypeHint::EntityIDT;
}

Primitive::Primitive(Sandboxe::Script::Runtime::Object * in) {
    defined = true;
    data = (Chain() << (uint64_t)in);
    hint = TypeHint::ObjectReferenceT;
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

Primitive::operator Dynacoe::Entity::ID() const {
    return Dynacoe::Entity::ID(data);
}

Primitive::operator Sandboxe::Script::Runtime::Object * () const {
    return (Sandboxe::Script::Runtime::Object*)(Chain() << data).AsUInt64();
}










