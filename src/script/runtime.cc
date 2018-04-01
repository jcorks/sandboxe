#include <sandboxe/script/runtime.h>

using Sandboxe::Script::Runtime::Primitive;
using Dynacoe::Chain;

Primitive::Primitive() {
    defined = false;
}

Primitive::Primitive(bool in) {
    defined = true;
    data = in ? "1" : "0";
}


Primitive::Primitive(int in) {
    defined = true;
    data = (Chain() << in);
}


Primitive::Primitive(float in) {
    defined = true;
    data = (Chain() << in);
}

Primitive::Primitive(double in) {
    defined = true;
    data = (Chain() << in);
}

Primitive::Primitive(uint32_t in) {
    defined = true;
    data = (Chain() << in);
}

Primitive::Primitive(uint64_t in) {
    defined = true;
    data = (Chain() << in);
}

Primitive::Primitive(const std::string & str) {
    defined = true;
    data = str;
}

Primitive::Primitive(const Dynacoe::Entity::ID & in) {
    defined = true;
    data = in.String();
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










