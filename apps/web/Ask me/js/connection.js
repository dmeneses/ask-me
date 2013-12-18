function connect()
{
	$.ajax({
    url: 'http://localhost:3000/askme',
    type: 'GET',
    dataType: 'jsonp',
    data: 'word=de&latitude=-17.365978&longitude=-66.175486&radio=1',
    
    success: function(data, xhr, status) {
        alert('Hello world ' + data.Name);
    },

    error: function(xhr, status) {
        alert(xhr.status + " " + xhr.statusText);
    }
	});
}