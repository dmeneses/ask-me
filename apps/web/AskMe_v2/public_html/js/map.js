
function showAdvancedSetting(box) {
   	$("#setting-div").slideToggle("slow");
}

function setLocation(position) {
	var lon = position.coords.longitude;
	var lat = position.coords.latitude;
	setMapPosition(lat, lon);
	var lonLat = new OpenLayers.LonLat(lon, lat)
	.transform(new OpenLayers.Projection("EPSG:4326"), map.getProjectionObject());
	actualPosition.moveTo(map.getPixelFromLonLat(lonLat));
}

function setMapPosition(latitude, longitude)
{
	var lonLat = new OpenLayers.LonLat(longitude, latitude)
	.transform(new OpenLayers.Projection("EPSG:4326"), map.getProjectionObject());

	map.setCenter(lonLat, 16);
}

function loadMap() {
	map = new OpenLayers.Map("map-div");
	map.addLayer(new OpenLayers.Layer.OSM());
	map.zoomToMaxExtent();

   	markers = new OpenLayers.Layer.Markers("Markers");
	map.addLayer(markers);

	actualPosition = new OpenLayers.Marker(new OpenLayers.LonLat(-98, 35));
	markers.addMarker(actualPosition);

	map.events.register("click", map, function(e) {
   		actualPosition.moveTo(e.xy);
   	});

	getLocation(setLocation);
}

function loadSocialInfo(socialInfoList)
{
	console.log('Loading social information list');

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

function clearMarkers()
{
	actualPosition = new OpenLayers.Marker(actualPosition.lonlat);
	markers.clearMarkers();
	markers.addMarker(actualPosition);
}

loadMap();
