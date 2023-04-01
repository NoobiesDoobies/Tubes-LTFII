// Create JoyStick object into the DIV 'joy1Div'
//var Joy1 = new JoyStick('joy1Div');

var joy1IinputPosX = document.getElementById("joy1PosizioneX");
var joy1InputPosY = document.getElementById("joy1PosizioneY");
var joy1Direzione = document.getElementById("joy1Direzione");
var joy1X = document.getElementById("joy1X");
var joy1Y = document.getElementById("joy1Y");
joy1X.value = 0;
joy1Y.value = 0;
/*
setInterval(function(){ joy1IinputPosX.value=Joy1.GetPosX(); }, 50);
setInterval(function(){ joy1InputPosY.value=Joy1.GetPosY(); }, 50);
setInterval(function(){ joy1Direzione.value=Joy1.GetDir(); }, 50);
setInterval(function(){ joy1X.value=Joy1.GetX(); }, 50);
setInterval(function(){ joy1Y.value=Joy1.GetY(); }, 50);
*/
// Create JoyStick object into the DIV 'joy1Div'
var Joy1 = new JoyStick('joy1Div', {}, function(stickData) {
    joy1IinputPosX.value = stickData.xPosition;
    joy1InputPosY.value = stickData.yPosition;
    joy1Direzione.value = stickData.cardinalDirection;
    joy1X.value = stickData.x;
    joy1Y.value = stickData.y;
});


setInterval(postJoyStickPosition, 100);

function postJoyStickPosition(){
    var xhttp = new XMLHttpRequest();
    var url = 'http://192.168.4.1/updateJoyStickValue'
    var data = new FormData();
    data.append('xVal', joy1X.value);
    data.append('yVal', joy1Y.value);
    console.log(data)
    xhttp.open('POST', url, true);
    xhttp.onreadystatechange = function() {//Call a function when the state changes.
        if(xhttp.readyState == 4 && xhttp.status == 200) {
            alert(xhttp.responseText);
        }
    }
    xhttp.send(data);
}
