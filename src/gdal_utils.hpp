#ifndef __GDAL_UTILS_H__
#define __GDAL_UTILS_H__

// node
#include <node.h>
#include <node_object_wrap.h>

// nan
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <nan.h>
#pragma GCC diagnostic pop

// gdal
#include <gdal_priv.h>
#include <gdal_utils.h>

// ogr
#include <ogrsf_frmts.h>

using namespace v8;
using namespace node;

// Methods and classes from gdal_utils.h
// http://www.gdal.org/gdal__utils_8h.html

namespace node_gdal {
namespace Utils {

	void Initialize(Local<Object> target);

	NAN_METHOD(vectorTranslate);

}
}

#endif