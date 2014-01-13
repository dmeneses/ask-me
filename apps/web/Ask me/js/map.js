
function showAdvancedSetting(box) {
   	$("#setting-div").slideToggle("slow");
}

function setLocation(position) {
	var lonLat = new OpenLayers.LonLat(position.coords.longitude,position.coords.latitude)
	.transform(new OpenLayers.Projection("EPSG:4326"), map.getProjectionObject());

	map.setCenter (lonLat, 16);
}

function loadMap() {
	$("#ask-form").submit(function () {
		$("#map-div").slideToggle("slow");
		return false;
	});

	document.getElementById("setting-checkbox").checked = false;
	$("#map-div").slideUp("fast");

	map = new OpenLayers.Map("map-div");
	map.addLayer(new OpenLayers.Layer.OSM());
	map.zoomToMaxExtent();

	getLocation(setLocation);
}

loadMap();
