//make connection with server
var socket = new io.Socket();
socket.connect('http://'+ipAddress+':'+port);

//Querying the DOM
var message = document.getElementById('message'),
	handle = document.getElementById('handle'),
	btn = document.getElementById('send'),
	output = document.getElementById('output');

//send out events

btn.addEventListener('click',function(){
	socket.emit('msg',{
		message: message.value,
		handle:handle.value
	});
});

//listen for events
socket.on('msg',function(data){
	output.innerHTML +='<p><strong>' + data.handle +':</strong>'+ data.message+'</p>';
})