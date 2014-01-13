
function showAdvancedSetting(box)
{
   	$("#setting").slideToggle("slow");
}

function setLocation(position)
{
	var lonLat = new OpenLayers.LonLat(position.coords.longitude,position.coords.latitude)
	.transform(
		new OpenLayers.Projection("EPSG:4326"), // transform from WGS 1984
		map.getProjectionObject() // to Spherical Mercator Projection
	);

	map.setCenter (lonLat, 16);
}

function loadMap()
{
	$("#askform").submit(function () {
		$("#map").slideToggle("slow");
		return false;
	});

	document.getElementById("checkSetting").checked = false;
	$("#map").slideUp("fast");

	map = new OpenLayers.Map("map");
	map.addLayer(new OpenLayers.Layer.OSM());
	map.zoomToMaxExtent();

	getLocation(setLocation);
}

loadMap();
