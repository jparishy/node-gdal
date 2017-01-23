#include "gdal_utils.hpp"
#include "gdal_common.hpp"
#include "gdal_spatial_reference.hpp"
#include "gdal_dataset.hpp"

#include <iostream>
#include <sstream>
#include <cstdio>

namespace node_gdal {


void Utils::Initialize(Local<Object> target)
{
	Nan::SetMethod(target, "vectorTranslate", vectorTranslate);
}

NAN_METHOD(Utils::vectorTranslate)
{
	Nan::HandleScope scope;

	Local<Object> obj;
	Local<Value> prop;
	
	GDALVectorTranslateOptions *opts;

	Dataset* ds;
	SpatialReference* t_srs;
	int error = 0;

	NODE_ARG_OBJECT(0, "Vector translate options", obj);

	if(obj->HasOwnProperty(Nan::New("src").ToLocalChecked())){
		prop = obj->Get(Nan::New("src").ToLocalChecked());
		if(prop->IsObject() && !prop->IsNull() && Nan::New(Dataset::constructor)->HasInstance(prop)){
			ds = Nan::ObjectWrap::Unwrap<Dataset>(prop.As<Object>());
			if(ds->getDataset()) {
				if(ds->getDataset()->GetLayerCount() == 0){
					Nan::ThrowError("src dataset must be a vector dataset");
					return;
				}
			}
			else
			{
				Nan::ThrowTypeError("src dataset already closed");
				return;
			}
		} else {
			Nan::ThrowError("src property must be a Dataset object");
			return;
		}
	} else {
		Nan::ThrowError("src dataset must be provided");
		return;
	}

	NODE_WRAPPED_FROM_OBJ(obj, "t_srs", SpatialReference, t_srs);

	char *str = NULL;
	int err = t_srs->get()->exportToProj4(&str);

	char *args[] = { (char *) "-t_srs", str, NULL };
	opts = GDALVectorTranslateOptionsNew(args, NULL);


	GDALDatasetH in = ds->getDataset();

	char dir[] = "/tmp/gdal.vectorTranslate.XXXXXXXXXX";
	mkdtemp(dir);

	std::ostringstream path;
	path << dir;
	path << "/";
	path << "tmp.gdal";

	GDALDataset *outDS = (GDALDataset *)GDALVectorTranslate(path.str().c_str(), NULL, 1, &in, opts, &error);
	GDALVectorTranslateOptionsFree(opts);

	if(error != 0)
	{
		Nan::ThrowError(CPLGetLastErrorMsg());
	}
	else
	{
		info.GetReturnValue().Set(Dataset::New(outDS));
	}
}

} //node_gdal namespace