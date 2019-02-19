//make connection with server
var socket = io.connect("http://localhost:5000");

//Querying the DOM
var message = document.getElementByID('message');
	handle = document.getElementByID('handle'),
	btn = document.getElementByID('send'),
	output = document.getElementByID('output');