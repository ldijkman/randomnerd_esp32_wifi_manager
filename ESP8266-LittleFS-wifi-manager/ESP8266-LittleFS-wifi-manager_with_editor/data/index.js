/**
 * ----------------------------------------------------------------------------
 * ESP32 Remote Control with WebSocket
 * ----------------------------------------------------------------------------
 * © 2020 Stéphane Calderoni
 * ----------------------------------------------------------------------------
 */

var gateway = `ws://${window.location.hostname}/ws`;
var websocket;

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------

window.addEventListener('load', onLoad);

function onLoad(event) {
    initWebSocket();
    initButton();
}

// ----------------------------------------------------------------------------
// WebSocket handling
// ----------------------------------------------------------------------------

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    let data = JSON.parse(event.data);
    document.getElementById('ledstate').innerHTML = data.status;
    document.getElementById('image').src = data.status+".gif";
    document.getElementById('mdnsscan').innerHTML = data.scan;
    document.getElementById('NTPTime').innerHTML = data.time;
    document.getElementById('OFFDelay').innerHTML = data.offdelay;
    document.getElementById('OFFcountdwn').innerHTML = data.offcnt;
   document.getElementById('T').innerHTML = data.T;
    document.getElementById('H').innerHTML = data.H;
    document.getElementById('P').innerHTML = data.P;
}

// ----------------------------------------------------------------------------
// Button handling
// ----------------------------------------------------------------------------

function initButton() {
    document.getElementById('toggle').addEventListener('click', onToggle);
    document.getElementById('offdelaybutton').addEventListener('click', onOffdelay);
}

function onToggle(event) {
    websocket.send(JSON.stringify({'action':'toggle'}));
}

function onOffdelay(event) {
     var temp=document.getElementById('offdelay').value;
    websocket.send(JSON.stringify({'off_delay':temp}));
}
