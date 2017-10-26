const express = require('express')
const app = express()

app.use(express.static(__dirname + '/'))

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/index.html')
})

let server = app.listen(3000, function () {
  let host = server.address().address;
  let port = server.address().port;

  console.log('app listening at http://%s:%s', host, port);
});