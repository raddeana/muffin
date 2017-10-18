var socket = io()

$('#send').click(function () {
  socket.emit('message', $('#message').val())
  $('#message').val('')
})

socket.on('message', function (data) {
  $('#message-window').append($('<li>').text(data))
})