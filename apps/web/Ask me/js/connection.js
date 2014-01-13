function addSocialInfomation()
{
    getLocation(connectToAskMeREST);
}

function connectToAskMeREST(position)
{
    console.log("Connectiing with AskMe REST");
    var request = buildURL(position.coords.latitude, position.coords.longitude);

    $.ajax({
        url: 'http://localhost:3000/askme',
        type: 'GET',
        dataType: 'jsonp',
        data: 'word=de&latitude=-17.365978&longitude=-66.175486&radio=1',

        success: function(data, xhr, status) {
            console.log('Connection success');
            var array = $.parseJSON(data);
            var items = new Array();
            array.forEach(function(item){
                items.push("<li>" + item.message + "</li>");
            });
            
            $("ul").html(items.join(" "));
        },

        error: function(xhr, status) {
            console.log('Connection Fail!');
            alert(xhr.status + " " + xhr.statusText);
        }
    });
}

function buildURL(latitude, longitude)
{
    var word = document.getElementById("word").value;
    var url = format("word={0}&latitude={1}&longitude={2}&radio=1", word, latitude, longitude);

    return url;
}

function format() {
    var format = arguments[0];

    for (var i = 0; i < arguments.length - 1; i++) {
        var reg = new RegExp("\\{" + i + "\\}", "gm");             
        format = format.replace(reg, arguments[i + 1]);
    }

    return format;
}


