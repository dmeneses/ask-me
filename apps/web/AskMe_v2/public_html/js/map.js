
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
    var size = new OpenLayers.Size(21, 25);
    var offset = new OpenLayers.Pixel(-(size.w / 2), -size.h);
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
    var placesList = document.getElementById("placesList").innerHTML;

    for (var i = 0; i < socialInfoList.length; i++) {
        var socialInfo = socialInfoList[i];
        tweetList += buildTweetItem(socialInfo);
        placesList += buildPlaceItem(socialInfo.places);
        addMarker(socialInfo);
    }

    document.getElementById("tweetList").innerHTML = tweetList;
    document.getElementById("placesList").innerHTML = placesList;
}

function buildTweetItem(socialInfo) {
    var tweet = '<li class="list-group-item">' + socialInfo.message

    switch (socialInfo.sentiment) {
        case -1:
            tweet += '<span class="badge"><span class="glyphicon glyphicon-thumbs-down"></span></span></li>';
            break;
        case 0:
            tweet += '<span class="badge"><span class="glyphicon glyphicon-hand-left"></span></span></li>';
            break;
        case 1:
            tweet += '<span class="badge"><span class="glyphicon glyphicon-thumbs-up"></span></span></li>';
            break;
        case 2:
            tweet += '<span class="badge"><span class="glyphicon glyphicon-minus"></span></span></li>';
            break;
        default:
            tweet += '</li>';
    }

    return tweet;
}

function buildPlaceItem(placesInfo) {
    var placesList = "";

    for (var i = 0; i < placesInfo.length; i++) {
        var place = placesInfo[i];
        placesList += '<li class="list-group-item">' + place.name + '</li>'
    }

    return placesList;
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
