var express = require('express');
var socket = require('socket.io');
// App setup
var app = express();
//Create a server
var server = app.listen(5000,function(){
	console.log('listen to requests on port 5000')
});

//static files
app.use(express.static('public'));

//socket setup
var io = socket(server);
//listen to make a connection
io.on('connection',function(socket){
	console.log('made socket connection', socket.id) 
});

