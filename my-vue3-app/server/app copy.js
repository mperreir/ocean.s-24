const express = require('express');
const http = require('http');

const PORT = 3010;
module.exports = PORT;


const app = express();
const server = http.createServer(app);


var port = "PORT" in process.env ? process.env.PORT : 8080;
var server = app.listen(port, function () {
    var host = server.address().address;
    var port = server.address().port;

    console.log("Hyblab routing app listening at http://%s:%s", host, port);
});

const path = require('path')


const io = require("socket.io")(server, {
    cors: {
      origin: [`http://localhost:${PORT}`,` https://hyblab.polytech.univ-nantes.fr:${PORT}`],
      methods: ["GET", "POST"]
    }
  });
  
app.use(express.static(path.join(__dirname, '../dist')));

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

server.listen( PORT, () => console.log(`Server running on port ${PORT}`));

