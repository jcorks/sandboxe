#include <sandboxe/script/runtime.h>
#include <sandboxe/entity/terminal.h>
#include <sandboxe/script/shell.h>
#include <Dynacoe/Library.h>
#include <Dynacoe/RawData.h>
#include <sandboxe/trunk.h>
#include <stack>
#include <cassert>
#include <v8.h>
#include <sandboxe/bindings/all.hpp>
#include <map>
#include <duktape.h>

using Sandboxe::Script::Runtime::Function;
using Sandboxe::Script::Runtime::Object;
using Sandboxe::Script::Runtime::Primitive;
using Sandboxe::Script::Runtime::Context;
using Sandboxe::Script::Runtime::Object_Internal;


struct ECMAContext {
    duk_context * context;
};


void Sandboxe::Script::Runtime::Initialize() {
    ECMAContext 
}




