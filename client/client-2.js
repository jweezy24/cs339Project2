var net = require('net');

var client = new net.Socket();

client.connect(7999, '67.163.37.156', function() {
//client.connect(7999, '127.0.0.1', function() {
	console.log('connected');
	client.write('Test ... this is client');
});

client.on('data', function(data) {
	console.log('Received: ' + data);
	// client dies after receiving response from server
	client.destroy();
});

client.on('close', function() {
	console.log('Connection closed');
});
