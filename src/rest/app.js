var express = require("express");
var addon = require('./../addon/build/Release/addon.node');
var app     = express();
var http    = require("http");
var server  = http.createServer(app);

app.get('/askme', function(req, res) {
	console.log("Word: " + req.query.word);
	console.log("Latitude: " + req.query.latitude);
	console.log("Longitude: " + req.query.longitude);
	console.log("Radio: " + req.query.radio);
	var answer = new addon.Answer();
	var array = answer.reply(req.query.word, parseFloat(req.query.latitude), parseFloat(req.query.longitude), parseFloat(req.query.radio));
	console.log("Size: " + array.length);
    res.jsonp(JSON.stringify(array));
});

server.listen(3000, function() {
	console.log("Node server running on http://localhost:3000");
});
