const express = require('express')

const app = express()
const server  = require('http').createServer(app)
const io = require('socket.io')(server)
const port = process.env.PORT || 3000

app.use(express.static(__dirname + '/public'))

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/index.html')
})

io.on('connection', function (socket) {
    console.info('a user connected')

    socket.on('message', function (data) {
      io.emit('message', data)
    })

    socket.on('disconnect', function () {
      console.info('a user left')
    })
})

server.listen(port, function () {
  console.info('server start on port : %d', port)
})