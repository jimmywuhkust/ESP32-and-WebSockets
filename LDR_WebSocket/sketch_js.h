/****************************************************************************
MIT License

Copyright (c) 2017-2018 gdsports625@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
****************************************************************************/
const char SKETCH_JS[] PROGMEM = R"=====(

//////////////////////////////////////////////
// ************** WebSocket *************** //
//////////////////////////////////////////////

var websocket;

function wsConnect() {
  
  // start a WebSocket
  websocket = new WebSocket('ws://' + window.location.hostname + ':81/');
  console.log("ws://" + window.location.hostname + ":81/");
    
  websocket.onopen = function(event) { onOpen(event) }
  websocket.onclose = function(event) { onClose(event) }
  websocket.onmessage = function(event) { onMessage(event) }
  websocket.onerror = function(event) { console.log(event.data); }
}

function onOpen(event){
  console.log('websocket opened ' + event.data);
}

function onClose(event){
  console.log('websocket closed ' + event.data);
  wsConnect();
}

function onMessage(event){
  // console.log('websocket data: ' + event.data);
  var value = String(event.data);
  value = parseInt(value);
  receivedData(value);
}

//////////////////////////////////////////////
// **************** P5.js ***************** //
//////////////////////////////////////////////

var t = 0; // time variable
var thickness = 10;
var radius = 20;

function setup() {
  createCanvas(windowWidth, windowHeight);
}

function draw() {
    
  // WAVEY GRASS
  background(10, 20, 0, 10); // transparent background (creates trails)

  // make a x and y grid of ellipses
  for (let x = 0; x <= width; x = x + 30) {
    for (let y = 0; y <= height; y = y + 30) {
      
      // starting point of each circle depends on mouse position
      const xAngle = map(mouseX, 0, width, -4 * PI, 4 * PI, true);
      const yAngle = map(mouseY, 0, height, -4 * PI, 4 * PI, true);
      // and also varies based on the particle's location
      const angle = xAngle * (x / width) + yAngle * (y / height);

      // each particle moves in a circle
      const myX = x + radius * cos(2 * PI * t + angle);
      const myY = y + radius * sin(2 * PI * t + angle);
      fill(40, 200, 40);
      noStroke();
      ellipse(myX, myY, thickness); // draw particle
    }
  }

  t = t + 0.01; // update time
}

function receivedData(data) {
  var value = map(data, 0, 3300, 0, 30);
  thickness = value;
}

)=====";
