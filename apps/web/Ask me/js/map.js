
function showAdvancedSetting(box) {
   	$("#setting-div").slideToggle("slow");
}

function setLocation(position) {
	setMapPosition(position.coords.longitude,position.coords.latitude);
}

function setMapPosition(latitude, longitude)
{
	var lonLat = new OpenLayers.LonLat(longitude, latitude)
	.transform(new OpenLayers.Projection("EPSG:4326"), map.getProjectionObject());

	map.setCenter(lonLat, 16);
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
	console.log('Loading social information list');
	markers = new OpenLayers.Layer.Markers( "Markers" );
	map.addLayer(markers);

	for(var i = 0; i < socialInfoList.length; i++) {
		addMarker(socialInfoList[i]);
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
    console.log('Social info message : ' + socialInformation.message);    
}

loadMap();
