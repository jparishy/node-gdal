
#ifndef __V8_HELPER_H__
#define __V8_HELPER_H__

// node
#include <node.h>

// nan
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <nan.h>
#pragma GCC diagnostic pop

using namespace v8;

// Source:
// https://github.com/nodejs/nan/issues/587

namespace node_gdal {
	namespace v8_helper {
		Local<Value> GetPrivate(Local<Object> object, Local<String> key);
		void SetPrivate(Local<Object> object, Local<String> key, Local<Value> value);
	}
}

#endif
