const express = require('express');
const http = require('http'); // Use 'http' instead of 'https'
const path = require('path');
const socketIo = require('socket.io');

const PORT = process.env.PORT || 3010;

const app = express();
const server = http.createServer(app); // Use HTTP server

const io = socketIo(server, {
  cors: {
    origin: ["https://hyblab.polytech.univ-nantes.fr"],
    methods: ["GET", "POST"]
  }
});

const addr_server = server.listen(PORT, function () {
    const host = addr_server.address().address;
    const port = addr_server.address().port;

    console.log("Server running at http://%s:%s", host, port); // Change to 'http'
});

app.use('/ocean-2', express.static(path.join(__dirname, '../dist')));

app.get('/ocean-2/userpage', (req, res) => {
  res.sendFile(path.join(__dirname, '../dist', 'user.html'));
});

app.get('/ocean-2/datapage', (req, res) => {
  res.sendFile(path.join(__dirname, '../dist', 'data.html'));
});


io.on('connection', (socket) => {
  console.log('A user connected');

  socket.on('send message', (msg) => {
    io.emit('new message', msg);
  });
});
