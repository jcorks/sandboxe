#ifndef H_sandboxe_binding_helpers_h
#define H_sandboxe_binding_helpers_h


// meant to cover any needed functionality across different major versions of 
// v8 and possible other scripting languages


#include <v8.h>


#define SANDBOXE_THROW(__T__)                 return v8::ThrowException(v8::String::New((__T__)))

#define SANDBOXE_ASSERT__ARG_COUNT(__T__)     if (args.Length() != (__T__)) return v8::ThrowException(v8::String::New((Dynacoe::Chain() << "The called function expects " << __T__ << " argument(s).").ToString().c_str()))
#define SANDBOXE_ASSERT(__T__)                if (!(__T__)) return v8::ThrowException(v8::String::New("Internal assertion failure."))

#define SANDBOXE_SCOPE                        v8::HandleScope v8_handleScope
#define SANDBOXE_BINDSET_DEF(__T__)           void __T__(v8::Handle<v8::ObjectTemplate> & v8_source)
#define SANDBOXE_BINDSET_CALL(__T__)          __T__(context)
#define SANDBOXE_BIND_DEF(__T__)              v8::Handle<v8::Value> __T__(const v8::Arguments & args)
#define SANDBOXE_BIND_CALL(__S__, __T__)      v8_source->Set(v8::String::New(__S__), v8::FunctionTemplate::New(__T__)); 
#define SANDBOXE_ARG(__N__)                   (*(v8::String::Utf8Value(args[__N__])))
#define SANDBOXE_ARG_COUNT                    (args.Length())
#define SANDBOXE_NORETURN                     return v8::Undefined()


#define SANDBOXE_OBJECT_CREATE(__T__)                               v8::Handle<v8::ObjectTemplate> __T__ = v8::ObjectTemplate::New(); __T__->SetInternalFieldCount(1)
#define SANDBOXE_OBJECT_RETRIEVE(__T__)                             v8::Handle<v8::Object> __T__ = info.This();
#define SANDBOXE_OBJECT_SET(__T__, __KEY__, __VALUE__)              __T__->Set(v8::String::New(__KEY__), v8::String::New(__VALUE__))
#define SANDBOXE_OBJECT_SET_FN(__T__, __KEY__, __VALUE__)           __T__->Set(v8::String::New(__KEY__), v8::String::New(__VALUE__))
#define SANDBOXE_OBJECT_GET(__T__, __KEY__)                         std::string(*v8::String::Utf8Value(__T__->Get(v8::String::New(__KEY__))))
#define SANDBOXE_OBJECT_BIND_ATTRIBUTE(__T__,__S__,__GET__,__SET__) __T__->SetAccessor(v8::String::NewSymbol(__S__), __GET__, __SET__)
#define SANDBOXE_OBJECT_BIND_ATTRIBUTE_READ_ONLY(__T__,__S__,__GET__,__SET__) __T__->SetAccessor(v8::String::NewSymbol(__S__), __GET__, __SET__)
#define SANDBOXE_OBJECT_GET_DEF(__T__)                              v8::Handle<v8::Value> __T__(v8::Local<v8::String> name, const v8::AccessorInfo & info)
#define SANDBOXE_OBJECT_SET_DEF(__T__)                              void __T__(Local<String> property, v8::Local<v8::String> name, const v8::AccessorInfo & info)

v8::Handle<v8::Value> SANDBOXE_VALUE(const std::string & str) {return v8::String::New(str.c_str(), str.size());}



#endif
