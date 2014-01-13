
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

function loadSocialInfo(socialInfoList)
{
	markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);

	for(info in socialInfoList) {
		addMarker(indo);
	}
}

function addMarker(socialInformation)
{
	var lonLat = new OpenLayers.LonLat(socialInformation.longitude, socialInformation.latitude)
      .transform(new OpenLayers.Projection("EPSG:4326"), map.getProjectionObject());
	var marker = new OpenLayers.Marker(lonLat);
    marker.events.register("click", marker, function(e){
    	popup = new OpenLayers.Popup.FramedCloud("tweet", marker.lonlat, 
    		new OpenLayers.Size(200, 200), socialInformation.message, null, true);
    	map.addPopup(popup);
    }); 
    markers.addMarker(marker);      
}

loadMap();
