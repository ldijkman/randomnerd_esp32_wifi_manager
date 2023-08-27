/*
    https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/
    https://plnkr.co/edit/ZEkhoGgs4ntDZzT0    
*/



function tabsex() {
var insert=`
<!-- 
    examples.js function tabsex() 
    https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/
    https://plnkr.co/edit/ZEkhoGgs4ntDZzT0 
-->
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body {font-family: Arial;}

/* Style the tab */
.tab {
  overflow: hidden;
  border: 1px solid #ccc;
  background-color: #f1f1f1;
}

/* Style the buttons inside the tab */
.tab button {
  background-color: inherit;
  float: left;
  border: none;
  outline: none;
  cursor: pointer;
  padding: 14px 16px;
  transition: 0.3s;
  font-size: 17px;
}

/* Change background color of buttons on hover */
.tab button:hover {
  background-color: #ddd;
}

/* Create an active/current tablink class */
.tab button.active {
  background-color: #ccc;
}

/* Style the tab content */
.tabcontent {
  display: none;
  padding: 6px 12px;
  border: 1px solid #ccc;
  border-top: none;
  background-color: #474141;
}
</style>
</head>
<body>

modifeid example from <b>
https://www.w3schools.com/howto/tryit.asp?filename=tryhow_js_tabs Tabs<br><br>
<p>Click on the buttons inside the tabbed menu:</p>
<button class="tablinks" onclick="myFunction()">show & hide</button><br><br><br>
<div class="tab" id="tab">
  <button class="tablinks" onclick="openCity(event, 'HTML')">HTML</button>
  <button class="tablinks" onclick="openCity(event, 'CSS')">CSS</button>
  <button class="tablinks" onclick="openCity(event, 'JavaScript')">JavaScript</button>
    <button class="tablinks" onclick="openCity(event, 'Arduino')">Arduino</button>
  <button class="tablinks" onclick="openCity(event, 'ESP')">ESP</button>
  <button class="tablinks" onclick="myFunction()" style="float:right;">Hide</button>
</div>

<div id="HTML" class="tabcontent">
  <h3>HTML TagBoard BrickBoard</h3>
  <p>HTML
      https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/
    https://plnkr.co/edit/ZEkhoGgs4ntDZzT0   </p>
</div>

<div id="CSS" class="tabcontent">
  <h3>CSS TagBoard BrickBoard</h3>
  <p>CSS
      https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/
    https://plnkr.co/edit/ZEkhoGgs4ntDZzT0   </p> 
</div>

<div id="JavaScript" class="tabcontent">
  <h3>JavaScript TagBoard BrickBoard</h3>
  <p>JavaScript
      https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/
    https://plnkr.co/edit/ZEkhoGgs4ntDZzT0   </p>
</div>

<div id="Arduino" class="tabcontent">
  <h3>Arduino TagBoard BrickBoard</h3>
  <p>Arduino</p> 
  <pre>
  // https://create.arduino.cc/example/builtin/02.Digital%5CButton/Button/preview

  // constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}

  </pre> 
  <iframe frameborder="0" src="https://create.arduino.cc/example/builtin/02.Digital%5CButton/Button/preview?embed" style="height:510px;width:100%;margin:10px 0"></iframe>
</div>

<div id="ESP" class="tabcontent">
  <h3>ESP TagBoard BrickBoard</h3>
  <p>ESP32 ESP8266 TagBoard BrickBoard</p> 
</div>



<div id="Hide"  class="tabcontent">
 <h3>ESP</h3>
 <p>ESP</p> 
</div>

<p><b>Note:</b> The element will not take up any space when the display property set to "none".</p>

<script>
/*
    https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/
    https://plnkr.co/edit/ZEkhoGgs4ntDZzT0    
*/
function myFunction() {
  var x = document.getElementById("tab");
  if (x.style.display === "none") {
    x.style.display = "block";
    openCity(event, 'HTML');
  } else {
    x.style.display = "none";
      var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  }
}
<\/script>

<script>
/*
    https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/
    https://plnkr.co/edit/ZEkhoGgs4ntDZzT0    
*/
function openCity(evt, cityName) {
  var i, tabcontent, tablinks;
  tabcontent = document.getElementsByClassName("tabcontent");
  for (i = 0; i < tabcontent.length; i++) {
    tabcontent[i].style.display = "none";
  }
  tablinks = document.getElementsByClassName("tablinks");
  for (i = 0; i < tablinks.length; i++) {
    tablinks[i].className = tablinks[i].className.replace(" active", "");
  }
  document.getElementById(cityName).style.display = "block";
  evt.currentTarget.className += " active";
}
<\/script>
   
</body>
</html> 
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }
 
var br = document.createElement("br"); // create a linebreak br
document.getElementById("phtmlbuttons").appendChild(br);

var btn = document.createElement("button");
btn.innerHTML = "HTML";
btn.type = "button";
btn.id="htmlbutton1";
document.getElementById("phtmlbuttons").appendChild(btn); // add button to <p id="phtmlbuttons"> </p>
document.getElementById("htmlbutton1").onclick = function() { 
// var insert snippet is between backticks `` = key left of 1
// some characters may break the backtick use backslash \
var insert=`
         <!DOCTYPE HTML>
         <html>
           <head>
             <meta http-equiv="content-type" content="text/html; charset=utf-8" />
             <title>pagetitle</title>
             <style>
             body{
                color:black;
                background-color:aqua;  
             }
             </style>
            <\script src=""><\/script>
           </head>
           <body>
             <h1> Hi hello welcome!</h1>
           </body>
         </html>
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }




var btn = document.createElement("button");
btn.innerHTML = "button added from examples.js";
btn.type = "button";
btn.id="htmlbutton30";
document.getElementById("phtmlbuttons").appendChild(btn); // add button to <p id="phtmlbuttons"> </p>
document.getElementById("htmlbutton30").onclick = function() { 
// var insert snippet is between backticks `` = key left of 1
// some characters may break the backtick use backslash \
var insert=`
create button and snippet from examples.js
add your own buttons and snippets from 1 file examples.js
/*
<pre>
░▀█▀░█░█░▀█▀░█▀▀░░░▀█▀░█▀▀░░░█▀▄░█▀▀░▀█▀░▀█▀░█▀▀░█▀▄
░░█░░█▀█░░█░░▀▀█░░░░█░░▀▀█░░░█▀▄░█▀▀░░█░░░█░░█▀▀░█▀▄
░░▀░░▀░▀░▀▀▀░▀▀▀░░░▀▀▀░▀▀▀░░░▀▀░░▀▀▀░░▀░░░▀░░▀▀▀░▀░▀
Figlet font Pagga https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/ 
</pre>
*/
     test30 set from example.js
     button is created from examples.js
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
}

var btn = document.createElement("button");
btn.innerHTML = "Add button from examples.js";
btn.type = "button";
btn.id="htmlbutton31";                                          // id must be unique
document.getElementById("phtmlbuttons").appendChild(btn);       // add button to <p id="phtmlbuttons"> </p>
document.getElementById("htmlbutton31").onclick = function() {  // id same as btn.id=
// var insert snippet is between backticks `` = key left of 1
// some characters may break the backtick use backslash \
var insert=`
create button and snippet from examples.js<br>
add your own buttons and snippets from 1 file examples.js<br>
/*
<pre>
░▀█▀░█▀▀░░░█▀▄░█▀▀░▀█▀░▀█▀░█▀▀░█▀▄
░░█░░▀▀█░░░█▀▄░█▀▀░░█░░░█░░█▀▀░█▀▄
░▀▀▀░▀▀▀░░░▀▀░░▀▀▀░░▀░░░▀░░▀▀▀░▀░▀
Figlet font Pagga https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/ 
</pre>
*/
     test30 set from example.js
     button is created from examples.js
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
}



var btn = document.createElement("button");
btn.innerHTML = "HR";
btn.type = "button";
btn.id="htmlbutton4";
document.getElementById("phtmlbuttons").appendChild(btn); // add button to <p id="phtmlbuttons"> </p>
document.getElementById("htmlbutton4").onclick = function() { 
// var insert snippet is between backticks `` = key left of 1
// some characters may break the backtick use backslash \
var insert=`
create button and snippet from examples.js
add your own buttons and snippets from 1 file examples.js


/*
<pre>
  ██ ██   ██ ██████  ██   
 ██  ██   ██ ██   ██  ██  
██   ███████ ██████    ██ 
 ██  ██   ██ ██   ██  ██  
  ██ ██   ██ ██   ██ ██   
                          
                          
Figlet font ANSI Regular https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/ 
</pre>

<h2>Horiontal Ruler line</h2>

<hr style="width:50%;text-align:left;margin-left:0">

Set the height<br>
<hr style="height:10px;border-width:0;color:gray;background-color:gray">

<hr style="height:20px;border-width:1px;background-color:blue;">
Set the width centered<br>
<hr style="width:50%">

 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }




// add to javascript buttons
var br = document.createElement("br"); // create a linebreak br
document.getElementById("pjavascriptbuttons").appendChild(br);

var btn = document.createElement("button");
btn.innerHTML = "Add buttons and snippets from examples.js";
btn.type = "button";
btn.id="javascriptbutton1";                                          // id must be unique
document.getElementById("pjavascriptbuttons").appendChild(btn);       // add button to <p id="pjavascriptbuttons"> </p>
document.getElementById("javascriptbutton1").onclick = function() {  // id same as btn.id=
// var insert snippet is between backticks `` = key left of 1
// some characters may break the backtick use backslash \
var insert=`
create button and snippet from examples.js<br>
add your own buttons and snippets from 1 file examples.js<br>

/*
<pre>
░▀▀█░█▀█░█░█░█▀█░█▀▀░█▀▀░█▀▄░▀█▀░█▀█░▀█▀
░░░█░█▀█░▀▄▀░█▀█░▀▀█░█░░░█▀▄░░█░░█▀▀░░█░
░▀▀░░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀░░░░▀░
Figlet font Pagga https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/ 
</pre>
*/
     test30 set from example.js
     button is created from examples.js
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
}


// add to javascript buttons
var btn = document.createElement("button");
btn.innerHTML = "setinterval";
btn.type = "button";
btn.id="javascriptbutton2";                                          // id must be unique
document.getElementById("pjavascriptbuttons").appendChild(btn);       // add button to <p id="pjavascriptbuttons"> </p>
document.getElementById("javascriptbutton2").onclick = function() {  // id same as btn.id=
// var insert snippet is between backticks `` = key left of 1
// some characters may break the backtick use backslash \
var insert=`
/*
<pre>
░█▀▀░█▀▀░▀█▀░▀█▀░█▀█░▀█▀░█▀▀░█▀▄░█░█░█▀█░█░░
░▀▀█░█▀▀░░█░░░█░░█░█░░█░░█▀▀░█▀▄░▀▄▀░█▀█░█░░
░▀▀▀░▀▀▀░░▀░░▀▀▀░▀░▀░░▀░░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀
Figlet font Pagga https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/ 
</pre>
*/
<p id="demo"></p>

<script>
  const element = document.getElementById("demo");
  setInterval(function() {element.innerHTML += "Hello "}, 1000);
<\/script>
<!-- https://www.w3schools.com/jsref/met_win_setinterval.asp -->
 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }




// add to CSS buttons
var br = document.createElement("br"); // create a linebreak br
document.getElementById("pcssbuttons").appendChild(br);

var btn = document.createElement("button");
btn.innerHTML = "Add buttons and snippets from examples.js";
btn.type = "button";
btn.id="cssbutton1";                                          // id must be unique
document.getElementById("pcssbuttons").appendChild(btn);       // add button to <p id="pcssbuttons"> </p>
document.getElementById("cssbutton1").onclick = function() {  // id same as btn.id=
// var insert snippet is between backticks `` = key left of 1
// some characters may break the backtick use backslash \
var insert=`
create button and snippet from examples.js<br>
add your own buttons and snippets from 1 file examples.js<br>

/*
<pre>
 ██████╗███████╗███████╗
██╔════╝██╔════╝██╔════╝
██║     ███████╗███████╗
██║     ╚════██║╚════██║
╚██████╗███████║███████║
 ╚═════╝╚══════╝╚══════╝
                        
Figlet font ANSI Shadow https://run.plnkr.co/plunks/ZEkhoGgs4ntDZzT0/ 
</pre>
*/
     test30 set from example.js
     button is created from examples.js
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
}




document.getElementById("htmlbutton18").value = "test button18";
document.getElementById("htmlbutton18").hidden = 0;
 function htmlex18() {
     var insert=`
     test18 set from example.js
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }





function cssborderex() {
var insert=` 
 <!DOCTYPE html>
<html>
<head>
<style>
h1 {
  border-style: solid;
  border-color: coral;
}

div {
  border-style: solid;
  border-color: coral;
}
</style>
</head>
<body>

<h1>A heading with a colored border</h1>

<div>https://www.w3schools.com/cssref/tryit.asp?filename=trycss_border-color</div>

</body>
</html>
 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }



   function inputtype() {
var insert=`
<h1>HTML5 input types</h1>
<h2>A quick demo</h2>
<form>
  <h2>Text</h2>
  <p>
    <label for="text">Text input:</label>
    <input type="text" id="text" />
  </p>
  <p>
    <label for="email">Email input:</label>
    <input type="email" id="email" />
  </p>
  <p>
    <label for="url">URL input:</label>
    <input type="url" id="url" />
  </p>
  <p>
    <label for="search">Search input:</label>
    <input type="search" id="search" />
  </p>
  <h2>Numeric</h2>
  <p>
    <label for="number">Number input:</label>
    <input type="number" id="number" />
  </p>
  <p>
    <label for="tel">Tel input:</label>
    <input type="tel" id="tel" />
  </p>
  <p>
    <label for="range">Range input:</label>
    <input type="range" id="range" min="1" max="100" />
  </p>
  <h2>Date/Time (Chrome only)</h2>
  <p>
    <label for="date">Date input:</label>
    <input type="date" id="date" />
  </p>
  <p>
    <label for="month">Month input:</label>
    <input type="month" id="month" />
  </p>
  <p>
    <label for="week">Week input:</label>
    <input type="week" id="week" />
  </p>
  <p>
    <label for="time">Time input:</label>
    <input type="time" id="time" />
  </p>
  <h2>Other</h2>
  <p>
    <label for="color">Colour input:</label>
    <input type="color" id="color" />
  </p>
</form>
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }

   function iframeex() {
var insert=`
 <iframe width="697" height="392" src="https://www.youtube.com/embed/eC0tJmIl_lY">
</iframe>
<br><br>
 <iframe width="100%" height="392" src="https://plnkr.co">
</iframe>
<br><br>
<iframe width="697" height="392" src="https://www.youtube.com/embed/5uapPPC8eQY">
</iframe>
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }

   function imgsrc() {
var insert=`
<br>
style float right<br>
<img src="https://i.pinimg.com/236x/8a/fd/4b/8afd4b5a88b15f2afaedb82bff4409c9.jpg" width="40%" heigth="40%" style="float:right;" title="i am an image, no it is not me"><br>
<br>
 <img src="https://i.pinimg.com/236x/8a/fd/4b/8afd4b5a88b15f2afaedb82bff4409c9.jpg" width="100%" heigth="100%" title="i am an image, no it is not me"><br>
`; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }

    function olulli() {
var insert=`
<br>
ordered list
 <ol>
 <li>Blah </li>
 <li>Blah Blah </li>
 <li>Blah Blah Blah </li>
 </ol>
 <br>
 unordered list
<ul>
 <li>Blah </li>
 <li>Blah Blah </li>
 <li>Blah Blah Blah </li>
 </ul>
 <br>
 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }

    function buttonex() {
var insert=`
 <br>
 <button onclick="alert('Hi!')">Click Me?</button>
 <br>
 <input type="button" onclick="window.open('http://google.com', '_blank', 'location=yes,height=570,width=520,scrollbars=yes,status=yes');" value="Go Google" />
 <br>
 image button<br>
 <button onclick="window.open('http://google.com', '_blank', 'location=yes,height=570,width=520,scrollbars=yes,status=yes');" value="Go Google" />
 <img src="data:image/jpeg;base64,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d50dTbJgks0B/SI2kgcZ26cem8StDisrGigaFhup9n0LD/amaXwE1aW0vxk4mgODm79MCMehaxYs9LBKKi1Rt5pCYz2PotcTgK9Ob7Lavk0m/O2nj4XN6deElrnuO5JA1woQFi2rDkaOzyMlZQa411/nLC0B3TR1OoLRsp5+ZPs7S51pY7gEe7J5qjAdZComUbJPlWdtptURiszcIIX1vyAGovDSGk4knTgBhipMEqmGm61ROMbNZ5bV9Ek9c7N7rZmte1RdXHN3Xh99S3al5c2xwsfgWxMBB3tyDTq0K6rjZuWIxx46Suyua3d3LIREWAEREAREQBERAVTPn2Px/giZ8+x+P8EQHfyR6iL3bPsCmKHkj1EXu2fYFMQBERAEREAREQBERAEREAREQBERAEREAREQBei1WcSNoQveiAoGWcwIZHF2tNJOkgXSektoSuU3MCIabOT/AOyQfQrVF4opoYitBWjOSXBtfJpKnCWqXkUXJOazISDFZY2OGh5beeOh7quHUVZLHkihvSGp511qLyopSlJ3k7vjmbJJZI8NFF5RFgyEREAREQBERAEREBVM+fY/H+CJnz7H4/wRAd/JHqIvds+wKYoeSPURe7Z9gUxAEREAREQBERAEREAREQBERAEREAREQBERAEREAREQBERAEREAREQBERAEREAREQFUz59j8f4ImfPsfj/BEB38keoi92z7ApioGTs7JxDFRkfoM3n8UfuXv23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBeEVH23z8SLsf5k23z8SLsf5kBNz59j8f4IqnnhnNM4RVZH+ved+znXlAf//Z">
 </button>
 <br>
 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }


    function centerex() {
var insert=`
 text<br>
 <center>
 text in center<br>
 <h1>centered</h1>
 <img src="" width="100" height="100" alt="no url give me a src url"><br>
 </center>
 <br>
 text<br>
 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }

     function commentex() {
var insert=`
hidden html comment<br>
<!--html singe line comment-->
<!--
  html multiline line comment

  // for css & javascript single line use //

  /*
    for css & javascript multi line use /* */
    for css & javascript multi line use /* */
    for css & javascript multi line use /* */
  */
-->
hidden html comment<br>
 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }
















     function hrex() {
var insert=`
<h2>Horiontal Ruler line</h2>

<hr style="width:50%;text-align:left;margin-left:0">

Set the height<br>
<hr style="height:10px;border-width:0;color:gray;background-color:gray">

<hr style="height:20px;border-width:1px;background-color:blue;">
Set the width centered<br>
<hr style="width:50%">

 `; 
  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }












      function textareaex() {
var insert=`
\n
<textarea id="textfieldid" class="" name="blah" rows="20" cols="20" style="color:blue;background-color:lime;" title="popup title of my blah blah bblah text area field">
rows is number of lines
cols is width in characetrs
text here BLAHBLAHBLAH
BLAHBLAHBLAH
BLAHBLAHBLAH
BLAHBLAHBLAH
BLAHBLAHBLAH
BLAH BLAH BLAH
blah blah blah
resize bottom right corner drag
</textarea>
\n
 `; 

  ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), insert);
 }




function paste2() {
     var pastetext=`
 <!DOCTYPE html>
 <html>
 <head>
 <title>  </title>
 <style>
 body{
   background-color:orange;
   color:yellow;
 }
 </style>
 </head>
 <body>
 <center>
 <h1>Hello</h1>
 </center>
 <br>
 <a href="http://plnkr.co/edit/ZEkhoGgs4ntDZzT0" target="paste2">Paste 2 Example from<br>http://plnkr.co/edit/ZEkhoGgs4ntDZzT0<br>Electric Storm</a><br>
 </body>
 </html>
        `;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), pastetext);
      }


    
function paste9() {
      htmltext = `paste9
<iframe id="" align="left" width="500" height="320" src="https://www.youtube.com/embed/5uapPPC8eQY" style="border:none; -ms-transform: scale(1, 1); transform: scale(1, 1)" scrolling="no">
</iframe>
<br>
<br>
<h1>latest video Electric Storm</h1>
<br>
<iframe width="697" height="392" src="https://www.youtube.com/embed/eC0tJmIl_lY" title="Ace Editor Preview   WYSIWYG  Electric Storm" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen>
</iframe><br>
<br>
 <center><small>
 Electric Storm<br>
 <a href="http://plnkr.co/edit/ZEkhoGgs4ntDZzT0" target="_blank">http://plnkr.co/edit/ZEkhoGgs4ntDZzT0</a><br>
 <br>
 </center>
      `;
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
}


function paste20() {
          var htmltext;
        htmltext = "<!DOCTYPE HTML> \n";
        htmltext += "<html> <!-- start and end document--> \n";
        htmltext += "<head>\n";
        htmltext += "<title> titel of the page </title>\n";
        htmltext += "<style>/* style css shoudl be in the head */\n";
        htmltext += "body{\n";
        htmltext += "  background-color: rgb(47,52,107);\n";
        htmltext += "  color: rgb(234,245,19);\n";
        htmltext += "}\n";
        htmltext += "</style>\n";
        htmltext += "</head><!-- end head start body -->\n";
        htmltext += "<body><!-- end head start body -->\n";
        htmltext += "<h1>Hello h1 text</h1>\n";
        htmltext += "<h2>h2 text</h2>\n";
        htmltext += "<h3>h3 text</h3>\n";
        htmltext += "<h4>h4 text</h4>\n";
        htmltext += "<h5>h5 text</h5>\n";
        htmltext += "<h6>h6 text</h6>\n";
        htmltext += "<hr> hr is a horizontal line ruler <br>\n";
        htmltext += "<center> center text </center> \n";
        htmltext += "<p> Paragraph 1 </p>\n";
        htmltext += "<p> Paragraph 2 </p>\n";
        htmltext += "<p> Paragraph 3</p>\n";
        htmltext += "br break the line to new line<br>\n";
        htmltext += "&nbsp; is a space <br>\n";
        htmltext += "<strike> strike trough text </strike><br>\n";
        htmltext += "<b> bold text </b><bbr>\n";
        htmltext += "<i> italic text</i><br>\n";
        htmltext += "<u>underline text</u><br>\n";
        htmltext += "<li> list item </li><br>\n";
        htmltext += "<blockquote>blockquote</blockquote><br>\n";
        htmltext += " </body> <!-- end body should be at end of page -->\n";
        htmltext += " </html><!-- end html should be at end of page -->\n";
        ace.edit("editor").session.insert(ace.edit("editor").getCursorPosition(), htmltext);
      }

