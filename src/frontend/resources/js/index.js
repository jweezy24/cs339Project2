var express = require('express');
var socket = require('socket.io');
var http = require('http');
var ipAddress = "67.163.37.156"
var port = "7999";

module.exports = app;

// App setup
var app = express();
app.set('port', port);

//Create a server
var io = socket(server);
var server = http.createServer();
server.listen(port,ipAddress);
socket = io.listen(server);

//static files
app.use(express.static('public'));

//socket setup
//listen to make a connection
io.on('connection',function(socket){
	console.log('made socket connection', socket.id);
	socket.on('msg',function(data){
		io.emit('msg'.data);
		console.log(data);
	}) 
});



