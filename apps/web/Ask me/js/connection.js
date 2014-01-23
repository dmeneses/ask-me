function ask() {

    if ($('#setting-checkbox').is(":checked")) {
        useAdvancedSetting();
    } else {
        getLocation(useGPS);
    }
    
}

function connectToAskMeREST(latitude, longitude) {
    console.log("Connectiing with AskMe REST");
    var request = buildURL(latitude, longitude);

    $.ajax({
        url: 'http://localhost:3000/askme',
        type: 'GET',
        dataType: 'jsonp',
        data: request,

        success: function(data, xhr, status) {
            console.log('Connection success');
            var socialInfoList = $.parseJSON(data);
            loadSocialInfo(socialInfoList);
            setMapPosition(socialInfoList[0].latitude, socialInfoList[0].longitude);
        },

        error: function(xhr, status) {
            console.log('Connection Fail!');
            alert(xhr.status + " " + xhr.statusText);
        }
    });
}

function buildURL(latitude, longitude) {
    var word = document.getElementById("word-input").value;
    var url = "word=" + word + "&latitude=" + latitude + "&longitude=" + longitude +"&radio=1";

    return url;
}

function useGPS(position)
{
    console.log("Using GPS");
    connectToAskMeREST(position.coords.latitude, position.coords.longitude);
}

function useAdvancedSetting()
{
    console.log("Using advanced");
    var latitude = $('#latitude').val();
    var longitude = $('#longitude').val();
    connectToAskMeREST(latitude, longitude);
}
