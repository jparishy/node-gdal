var gdal = require('../lib/gdal.js');
var assert = require('chai').assert;

describe('gdal', function() {
	afterEach(gc);

	describe('vectorTranslate()', function() {
		beforeEach(function() {
		});
		afterEach(function() {
		});
        it('should throw an error on raster dataset', function() {
			var src = gdal.open(__dirname + '/data/sample.tif');
			var t_srs = gdal.SpatialReference.fromUserInput('EPSG:4326');
            var params = {
                src: src,
                t_srs: t_srs
            };
            assert.throws(function() {
                gdal.vectorTranslate(params);
            }, "src dataset must be a vector dataset");
        });
		it('should translate a vector dataset', function() {
			var src = gdal.open(__dirname + '/data/shp/sample.shp');
			var t_srs = gdal.SpatialReference.fromUserInput('EPSG:4326');
            var params = {
                src: src,
                t_srs: t_srs
            };
            gdal.vectorTranslate(params);
		});
	});
});