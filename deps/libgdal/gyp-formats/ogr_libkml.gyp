{
	"includes": [
		"../common.gypi"
	],
	"targets": [
		{
			"target_name": "libgdal_ogr_libkml_frmt",
			"type": "static_library",
			"sources": [
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmldatasource.cpp",
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmldriver.cpp",
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmlfeature.cpp",
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmlfeaturestyle.cpp",
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmlfield.cpp",
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmlgeometry.cpp",
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmllayer.cpp",
				"../gdal/ogr/ogrsf_frmts/libkml/ogrlibkmlstyle.cpp"
			],
			"include_dirs": [
				"./gdal/ogr/ogrsf_frmts/libkml"
			]
		}
	]
}
