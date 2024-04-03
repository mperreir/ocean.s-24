const express = require('express');
const http = require('http');
const path = require('path');
const cors = require('cors'); // 添加CORS支持

const PORT = process.env.PORT || 3010;
const app = express();
const server = http.createServer(app);

// 配置CORS
app.use(cors({
  origin: [
    `http://localhost:${PORT}/`, 
    "http://hyblab.polytech.univ-nantes.fr", 
    "https://hyblab.polytech.univ-nantes.fr",
    `http://hyblab.polytech.univ-nantes.fr:${PORT}/`, 
    "http://192.168.1.153", 
    `http://192.168.1.153:${PORT}/`,
    `https://hyblab.polytech.univ-nantes.fr:${PORT}/`, 
    "http://hyblab.polytech.univ-nantes.fr/ocean-2/", 
    "https://hyblab.polytech.univ-nantes.fr/ocean-2",
  ],
  methods: ["GET", "POST"]
}));

app.use(express.json()); // 用于解析JSON类型的请求体
app.use('/ocean-2', express.static(path.join(__dirname, '../dist')));

let messages = []; // 存储消息的数组

// 处理POST请求，接收消息
app.post('/ocean-2/messages', (req, res) => {
    const message = req.body;
    message.id = Date.now();
    messages.push(message);
    res.status(201).send({ message: 'Message received', id: message.id });
});

// 处理GET请求，发送消息
app.get('/ocean-2/messages', (req, res) => {
    res.status(200).json(messages);
});

app.get('/ocean-2/userpage', (req, res) => {
  res.sendFile(path.join(__dirname, '../dist', 'user.html'));
});

app.get('/ocean-2/datapage', (req, res) => {
  res.sendFile(path.join(__dirname, '../dist', 'data.html'));
});

server.listen(PORT, () => console.log(`Server running at http://localhost:${PORT}`));
