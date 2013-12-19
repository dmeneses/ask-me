function connect()
{
    var word = document.getElementById("word").value;
    var url = format("word={0}&latitude=-17.365978&longitude=-66.175486&radio=1", word);

    $.ajax({
        url: 'http://localhost:3000/askme',
        type: 'GET',
        dataType: 'jsonp',
        data: '',

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
            alert(xhr.status + " " + xhr.statusText);
        }
    });
}

function format() {
    var s = arguments[0];

    for (var i = 0; i < arguments.length - 1; i++) {
        var reg = new RegExp("\\{" + i + "\\}", "gm");             
        s = s.replace(reg, arguments[i + 1]);
    }

    return s;
}