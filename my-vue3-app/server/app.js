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
      origin: [`http://localhost:${PORT}/`,"http://hyblab.polytech.univ-nantes.fr",`https://hyblab.polytech.univ-nantes.fr:${PORT}/`,"http://192.168.1.153",`https://192.168.1.153:${PORT}/`],
      methods: ["GET", "POST"]
    }
  });

app.use(express.static(path.join(__dirname, '../dist')));

app.get('/userpage', (req, res) => {
  res.sendFile(path.join(__dirname, '../dist', 'user.html'));
});

app.get('/datapage', (req, res) => {
  res.sendFile(path.join(__dirname, '../dist', 'data.html'));
});


io.on('connection', (socket) => {
  console.log('A user connected');

  socket.on('send message', (msg) => {

    io.emit('new message', msg);

  });
});
