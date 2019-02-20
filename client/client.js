const
	io = require("socket.io-client"),
	ioClient = io.connect("http://localhost:7999");

ioClient.on("seq-num", (msg) => console.info(msg));

ioClient.emit("test");
