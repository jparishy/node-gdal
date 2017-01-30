var gdal = require('../lib/gdal.js');
var assert = require('chai').assert;

describe('gdal', function() {
	afterEach(gc);

	describe('vectorTranslate()', function() {
		beforeEach(function() {
		});
		afterEach(function() {
		});
        it('should throw an error on raster dataset for src', function() {
			var tif = gdal.open(__dirname + '/data/sample.tif');
			var shp = gdal.open(__dirname + '/data/shp/sample.shp');
			var t_srs = gdal.SpatialReference.fromUserInput('EPSG:4326');
            var params = {
                src: tif,
                dst: shp,
                t_srs: t_srs
            };
            assert.throws(function() {
                gdal.vectorTranslate(params);
            }, "src dataset must be a vector dataset");
        });
		it('should translate a vector dataset', function() {
			var original = gdal.open(__dirname + '/data/shp/sample.shp');

            var file = __dirname + '/data/temp/ds_vt_test.' + String(Math.random()).substring(2) + '.tmp.shp';
			var outDS = gdal.open(file, 'w', 'ESRI Shapefile');

			var t_srs = gdal.SpatialReference.fromUserInput('EPSG:4326');
            
           var toParams = {
                src: original,
                dst: outDS,
                t_srs: t_srs
            };

            var to = gdal.vectorTranslate(toParams);
            assert(t_srs.isSame(to.layers.get(0).srs), 'Should have same srs as the one loaded from file for projection');

            outDS.close();

            file = __dirname + '/data/temp/ds_vt_test.' + String(Math.random()).substring(2) + '_2.tmp.shp';
            outDS = gdal.open(file, 'w', 'ESRI Shapefile');

            var o_srs = original.layers.get(0).srs;
           var backParams = {
                src: to,
                dst: outDS,
                t_srs: o_srs
            };

            var back = gdal.vectorTranslate(backParams);
            
            assert(back.layers.get(0).srs.isSame(o_srs), 'Should have original srs after reprojecting back to original');
		});
	});
});