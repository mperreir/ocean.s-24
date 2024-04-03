const express = require('express');
const https = require('https'); // Use 'https' instead of 'http'
const fs = require('fs'); // For reading SSL/TLS files
const path = require('path');
const socketIo = require('socket.io');

const PORT = process.env.PORT || 3010;

// Assuming you have 'certificate.pem' and 'privatekey.pem' files
const options = {
  key: fs.readFileSync(path.join(__dirname, 'privatekey.pem')),
  cert: fs.readFileSync(path.join(__dirname, 'certificate.pem'))
};

const app = express();
const server = https.createServer(options, app); // Use HTTPS server

// Rest of your express app setup...

const io = socketIo(server, {
  cors: {
    origin: ["https://hyblab.polytech.univ-nantes.fr:3010/"],
    methods: ["GET", "POST"]
  }
});

// Socket.io setup and event handlers...

var addr_server = server.listen(PORT, function () {
    var host = addr_server.address().address;
    var port = addr_server.address().port;

    console.log("Server running at https://%s:%s", host, port); // Change to 'https'
});

// Express static and route handlers...


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
