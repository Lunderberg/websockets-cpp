var textbox = document.getElementById("text_sent");
var output = document.getElementById("output");
var socket = new WebSocket("ws://" + location.hostname + ":9002");

function send_clicked() {
    var obj = {"time": new Date().getTime() / 1000,
               "message": textbox.value,
              };

    socket.send(JSON.stringify(obj));
}

socket.onmessage = function(event) {
    output.innerHTML = event.data;
};
