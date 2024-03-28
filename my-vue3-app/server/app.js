const express = require('express');
const http = require('http');

const app = express();
const server = http.createServer(app);

const path = require('path')

const io = require("socket.io")(server, {
    cors: {
      origin: ["http://localhost:8080","http://172.20.10.13:8080"],
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

const PORT = 8080;
server.listen( PORT, () => console.log(`Server running on port ${PORT}`));