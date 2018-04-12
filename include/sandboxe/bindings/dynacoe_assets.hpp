#ifndef H_sandboxe_bindings_dynacoe_assets
#define H_sandboxe_bindings_dynacoe_assets
#include <sandboxe/native/native.h>
#include <sandboxe/native/assetID.h>
#include <sandboxe/native/byteArray.h>
/*
    Dynacoe::Assets Bindings
    
    notes:

*/

namespace Sandboxe {
namespace Bindings {

SANDBOXE_NATIVE_DEF(__asset_id_valid_get) {
    Sandboxe::AssetID * id = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(source);
    context.SetReturnValue(id->id.Valid());
}
SANDBOXE_NATIVE_DEF(__asset_id_valid_set) {}

SANDBOXE_NATIVE_DEF(__asset_id_name_get) {
    Sandboxe::AssetID * id = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(source);
    context.SetReturnValue(Dynacoe::Assets::Name(id->id));
}
SANDBOXE_NATIVE_DEF(__asset_id_name_set) {}


SANDBOXE_NATIVE_DEF(__asset_id_get) {
    //TODO
}

SANDBOXE_NATIVE_DEF(__asset_id_remove) {
    Sandboxe::AssetID * id = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(source);
    Dynacoe::Assets::Remove(id->id);
}
SANDBOXE_NATIVE_DEF(__asset_id_write) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    Sandboxe::AssetID * id = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(source);
    context.SetReturnValue(Dynacoe::Assets::Write(id->id, arguments[0], arguments[1]));
}




SANDBOXE_NATIVE_DEF(__assets_load) {
    Dynacoe::AssetID id;
    if (arguments.size() == 2) {
        id = Dynacoe::Assets::Load(arguments[0], arguments[1], false);
    } else if (arguments.size() == 3) {
        id = Dynacoe::Assets::Load(arguments[0], arguments[1], arguments[2]);        
    } else {
        return;
    }
    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::AssetIDT);
    Sandboxe::AssetID * s = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(object);
    s->id = id;
    context.SetReturnValue(object);
}

SANDBOXE_NATIVE_DEF(__assets_load_from_buffer) {
    SANDBOXE_ASSERT__ARG_COUNT(3);
    SANDBOXE_ASSERT__ARG_TYPE(2, ObjectReferenceT);
    SANDBOXE_ASSERT__ARG_NATIVE_TYPE(2, ByteArrayT);
    
    Sandboxe::ByteArray * array = Sandboxe::NativeObject::Get<Sandboxe::ByteArray>(arguments[2]);
    
    Dynacoe::AssetID id;
    id = Dynacoe::Assets::LoadFromBuffer(arguments[0], arguments[1], array->data);
    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::AssetIDT);
    Sandboxe::AssetID * s = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(object);
    s->id = id;
    context.SetReturnValue(object);
}

SANDBOXE_NATIVE_DEF(__assets_supported_load_extensions) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    int i = arguments[0];
    if (i < 1 || i >= (int) Dynacoe::Assets::Type::NoType) return;
    
    auto names = Dynacoe::Assets::SupportedLoadExtensions((Dynacoe::Assets::Type)i);
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < names.size(); ++i) {
        out.push_back(names[i]);
    }
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__assets_supported_write_extensions) {
    SANDBOXE_ASSERT__ARG_COUNT(1);
    int i = arguments[0];
    if (i < 1 || i >= (int) Dynacoe::Assets::Type::NoType) return;
    
    auto names = Dynacoe::Assets::SupportedWriteExtensions((Dynacoe::Assets::Type)i);
    std::vector<Sandboxe::Script::Runtime::Primitive> out;
    for(uint32_t i = 0; i < names.size(); ++i) {
        out.push_back(names[i]);
    }
    context.SetReturnArray(out);
}

SANDBOXE_NATIVE_DEF(__assets_query) {
    SANDBOXE_ASSERT__ARG_COUNT(2);
    int i = arguments[0];
    if (i < 1 || i >= (int) Dynacoe::Assets::Type::NoType) return;

    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::AssetIDT);
    Sandboxe::AssetID * s = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(object);
    s->id = Dynacoe::Assets::Query((Dynacoe::Assets::Type)i, arguments[1]);
    context.SetReturnValue(object);
}

SANDBOXE_NATIVE_DEF(__assets_new) {
    if (arguments.size() < 1) {
        SANDBOXE_ASSERT__ARG_COUNT(1);
        return;
    }
    std::string name = "";
    if (arguments.size() == 2) {
        name = std::string(arguments[1]);
    } 

    int i = arguments[0];
    if (i < 1 || i >= (int) Dynacoe::Assets::Type::NoType) return;

    auto object = Sandboxe::NativeObject::New(Sandboxe::NativeType::AssetIDT);
    Sandboxe::AssetID * s = Sandboxe::NativeObject::Get<Sandboxe::AssetID>(object);
    s->id = Dynacoe::Assets::New((Dynacoe::Assets::Type)i, name);
    context.SetReturnValue(object);
}



void dynacoe_assets(std::vector<std::pair<std::string, Sandboxe::Script::Runtime::Function>> & fns) {
    
    Sandboxe::Script::Runtime::AddType(
        Sandboxe::NativeTypeToString(Sandboxe::NativeType::AssetIDT),
        // methods
        {
            {"get", __asset_id_get},
            {"remove", __asset_id_remove},
            {"write", __asset_id_write}
        },
        // properties
        {
        },
        
        // managed properties,
        {
            {"valid", {__asset_id_valid_get, __asset_id_valid_set}},
            {"name", {__asset_id_name_get, __asset_id_name_set}},
        }
    );

    fns.push_back({"__assets_load", __assets_load});
    fns.push_back({"__assets_load_from_buffer", __assets_load_from_buffer});
    fns.push_back({"__assets_supported_load_extensions", __assets_supported_load_extensions});
    fns.push_back({"__assets_query", __assets_query});
    fns.push_back({"__assets_new", __assets_new});
    fns.push_back({"__assets_supported_write_extensions", __assets_supported_write_extensions});
}

}
}



#endif