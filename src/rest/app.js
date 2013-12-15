var express = require("express");
var addon = require('./../addon/build/Release/addon.node');
var app     = express();
var http    = require("http");
var server  = http.createServer(app);

app.configure(function () {
    app.use(express.bodyParser());
    app.use(express.methodOverride());
    app.use(app.router);
});

app.get('/askme', function(req, res) {
	console.log("Word: " + req.query.word);
	console.log("Latitude: " + req.query.latitude);
	console.log("Longitude: " + req.query.longitude);
	console.log("Radio: " + req.query.radio);
	var answer = new addon.Answer();
	var array = answer.reply(req.query.word, req.query.latitude, req.query.logitude, req.query.radio);
	console.log("Size: " + array.length);
    res.send(array);
});

server.listen(3000, function() {
	console.log("Node server running on http://localhost:3000");
});