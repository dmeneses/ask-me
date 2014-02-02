
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

function createCurrentMarker()
{
	var size = new OpenLayers.Size(21,25);
	var offset = new OpenLayers.Pixel(-(size.w/2), -size.h);
	var icon = new OpenLayers.Icon(
		'http://www.members1st.org/EntityLocator_prod/Content/images/current_position.png', 
		size, offset);
	actualPosition = new OpenLayers.Marker(new OpenLayers.LonLat(-98, 35), icon);
}

function loadMap() {
    map = new OpenLayers.Map("map-div");
    map.addLayer(new OpenLayers.Layer.OSM());
    map.zoomToMaxExtent();

    markers = new OpenLayers.Layer.Markers("Markers");
    map.addLayer(markers);

	createCurrentMarker();
	markers.addMarker(actualPosition);
	
	map.events.register("click", map, function(e) {
   		actualPosition.moveTo(e.xy);
   	});

    getLocation(setLocation);
}

function loadSocialInfo(socialInfoList)
{
    console.log('Loading social information list');
    var tweetList = document.getElementById("tweetList").innerHTML;

    for (var i = 0; i < socialInfoList.length; i++) {
        var social = socialInfoList[i];
        addMarker(social);
        tweetList += '<li class="list-group-item">' + social.message

        switch (social.sentiment) {
            case -1:
                tweetList += '<span class="glyphicon glyphicon-thumbs-down"></span></li>';
                break;
            case 0:
                tweetList += '<span class="glyphicon glyphicon-hand-left"></span></li>';
                break;
            case 1:
                tweetList += '<span class="glyphicon glyphicon-thumbs-up"></span></li>';
                break;
            case 2:
                tweetList += '<span class="glyphicon glyphicon-minus"></span></li>';
                break;
            default:
                tweetList += '</li>';
        }

    }

    document.getElementById("tweetList").innerHTML = tweetList;
}

function addMarker(socialInformation)
{
    var lonLat = new OpenLayers.LonLat(socialInformation.longitude, socialInformation.latitude)
            .transform(new OpenLayers.Projection("EPSG:4326"), map.getProjectionObject());
    var marker = new OpenLayers.Marker(lonLat);
    marker.events.register("click", marker, function(e) {
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
