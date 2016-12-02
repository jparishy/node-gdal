#include "v8_helper.hpp"

namespace node_gdal {
namespace v8_helper {

// Source:
// https://github.com/nodejs/nan/issues/587

	Local<Value> GetPrivate(Local<Object> object, Local<String> key) {
		Isolate* isolate = Isolate::GetCurrent();
		Local<Context> context = isolate->GetCurrentContext();
		Local<Private> privateKey = Private::ForApi(isolate, key);
		Local<Value> value;
		Maybe<bool> result = object->HasPrivate(context, privateKey);
		if (!(result.IsJust() && result.FromJust()))
			return Local<Value>();
		if (object->GetPrivate(context, privateKey).ToLocal(&value))
			return value;
		return Local<Value>();
	}

	void SetPrivate(Local<Object> object, Local<String> key, Local<Value> value) {
		if (value.IsEmpty())
			return;
		Isolate* isolate = Isolate::GetCurrent();
		Local<Context> context = isolate->GetCurrentContext();
		Local<Private> privateKey = Private::ForApi(isolate, key);
		object->SetPrivate(context, privateKey, value);
	}
}
}