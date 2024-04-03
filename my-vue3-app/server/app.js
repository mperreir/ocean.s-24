const express = require('express');
const http = require('http');

const PORT = process.env.PORT || 3010;

module.exports = PORT;


const app = express();
const server = http.createServer(app);

const path = require('path')


// launch main server app
//warning:  do not change the port, it will be automatically taken from env en dev and prod servers ...
var addr_server = server.listen(PORT, function () {
    var host = addr_server.address().address;
    var port = addr_server.address().port;

    console.log("Server running at http://%s:%s", host, port);
});


const io = require("socket.io")(server, {
    cors: {
      origin: ["https://hyblab.polytech.univ-nantes.fr/ocean-2"],
      methods: ["GET", "POST"]
    }
});


app.use('/ocean-2', express.static(path.join(__dirname, '../dist')));

app.get('/ocean-2/userpage', (req, res) => {
  res.sendFile(path.join(__dirname, '../dist', 'user.html'));
});

app.get('/ocean-2/datapage', (req, res) => {
  // Make sure to point to the correct html file within the 'dist' directory
  res.sendFile(path.join(__dirname, '../dist', 'data.html'));
});


io.on('connection', (socket) => {
  console.log('A user connected');

  socket.on('send message', (msg) => {

    io.emit('new message', msg);

  });
});
