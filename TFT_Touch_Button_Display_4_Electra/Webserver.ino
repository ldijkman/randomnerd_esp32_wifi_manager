// hello
// https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft
// https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat
// http://www.Arduino.TK
//
// https://m.facebook.com/groups/2643123052617990
// https://www.facebook.com/groups/esp32smartthermostat
//
// GNU General Public License,
// which basically means that you may freely copy, change, and distribute it,
// but you may not impose any restrictions on further distribution,
// and you must make the source code available.
//

// This function returns an HTML webpage
// It uses the Raw string macro 'R' to place commands in PROGMEM
const char Web_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html><head>
<title>Art, ESP32 Smart Thermostat</title>
 <link rel="shortcut icon" href="http://arduino.tk/thumbsup_2.png"> 
 <link rel="alternate icon" class="js-site-favicon" type="image/png" href="http://arduino.tk/thumbsup_2.png">
<meta name=\"viewport" content="width=device-width, initial-scale=.7\">
<meta name=\"author" content="Remote HTML Web Control Art ESP32 Smart Thermostat\">
<meta name=\"copyright\" content=\"2020-2021 Dirk Luberth Dijkman Bangert 30 1619GJ The Netherlands\">
<meta name=\"description\" content=\"ESP32 Smart Thermostat\">
<meta name=\"keywords\" content=\"\">
<!--<meta name=\"robots\" content=\"noimageindex, nofollow, nosnippet\">-->
<meta property=\"og:url\" content=\"http://www.Arduino.TK/\">

  <style>
    .displayobject{
       font-family: sans-serif;
       margin: auto;
       text-align: center;
       width: 100%;
       height: 1000px;
       border: 0px solid #000000;
       padding: 0px;
       //background: #558ED5;
       background-image: url('http://arduino.tk/clouds.jpg');
       border: 1px solid black;
       background-size: 100% 100%;
    }
    h1 {
      font-size: 25px;
      color: white;
    }
    h4 {
      font-size: 25px;
      color: violet;
    }
    
    a:link {
      color: black;
      background-color: transparent;
      text-decoration: none;
    }

    a:visited {
      color: black;
      background-color: transparent;
      text-decoration: none;
    }

    a:hover {
      color: black;
      background-color: transparent;
      text-decoration: underline;
    }

    a:active {
      color: black;
      background-color: transparent;
      text-decoration: underline;
    }
  </style>




  <script>

      setInterval(function(){getSensorDataeen(); }, 2500); // Call function every set interval 
    setInterval(function(){getSensorDatatwee(); }, 2000);
    setInterval(function(){getSensorDatadrie(); }, 1500);
    setInterval(function(){getSensorDatavier(); }, 1000);

    //document.getElementById("modusid").innerHTML = "Cool modus"; 
      
       function getSensorDataeen() {
        var xa = new XMLHttpRequest();  
         xa.onreadystatechange = function() {
            if (xa.readyState == 4 && xa.status == 200) {
              document.getElementById("tempid").innerHTML = this.responseText;
            } 
          }
          xa.open("GET", "temp", true);
          xa.send();
       }


      function getSensorDatatwee() {
        var ya= new XMLHttpRequest();        
        ya.onreadystatechange = function() {
          if (ya.readyState == 4 && ya.status == 200) {
            document.getElementById("humidid").innerHTML = this.responseText;
          }  
        }     
        ya.open("GET", "humid", true);
        ya.send();
      }
      
      function getSensorDatadrie() {
        var zza = new XMLHttpRequest();        
        zza.onreadystatechange = function() {
          if (zza.readyState == 4 && zza.status == 200) {
            document.getElementById("pressid").innerHTML = this.responseText;
          } 
        }
        zza.open("GET", "pressure", true);
        zza.send(); 
      }
      
      function getSensorDatavier() {    
        var qqa = new XMLHttpRequest();
        qqa.onreadystatechange = function() {  
          if (qqa.readyState == 4 && qqa.status == 200) {
            document.getElementById("modusid").innerHTML = this.responseText;
            document.getElementById("modusidtext").value = this.responseText;
         }
        }
        qqa.open("GET", "modus", true);
        qqa.send(); 
      }  
       
</script>

   <script type="text/javascript"> 
        window.history.forward(); 
        function noBack() { 
            window.history.forward(); 
        } 
    </script> 


  </head>
  <body><!-- bgcolor="DodgerBlue"> -->
     <div class = "displayobject">
     <center>
       <h1>Art ESP32 Smart Thermostat <br>
       Art in the Air / Cloud<br>
       The Art of Temperature Controlled</h1>
       </center>
       <h4><a href="/temp">Temperature</a> <span id="tempid">-- </span> &degC</h4>
       <h4><a href="/humid">Humidity</a> <span id="humidid">-- </span> %</h4>
       <h4><a href="/pressure">Pressure</a> <span id="pressid">-- </span> mbar</h4>
       <h4><a href="/modus">modus</a> <span id="modusid">-- </span></h4>
       Active modus = <input type="button" id="modusidtext" value="?" size="2" >=<input type="button" id="textmodusid" value="?"><br><br>

<script>

setInterval(function(){myFunction(); }, 1000);

function myFunction(val) { 
  //alert("The input value has changed. The new value is: " + val);

  if(document.getElementById("modusidtext").value==0){
    document.getElementById("textmodusid").value="Normal modus";
     document.getElementById("normalbtn").style="color:green; background-color:PaleTurquoise;";
    }else{
      document.getElementById("normalbtn").style="color:black; background-color:grey;";
  }
  if(document.getElementById("modusidtext").value==1){
    document.getElementById("textmodusid").value="Eco modus";
     document.getElementById("ecobtn").style="color:green; background-color:PaleTurquoise;";
  }else{
      document.getElementById("ecobtn").style="color:black; background-color:grey;";
  }
  if(document.getElementById("modusidtext").value==2){
    document.getElementById("textmodusid").value="Auto modus";
     document.getElementById("autobtn").style="color:green; background-color:PaleTurquoise;";
  }else{
      document.getElementById("autobtn").style="color:black; background-color:grey;";
  }
  if(document.getElementById("modusidtext").value==3){
    document.getElementById("textmodusid").value="Cool modus";
     document.getElementById("coolbtn").style="color:green; background-color:PaleTurquoise;";
  }else{
      document.getElementById("coolbtn").style="color:black; background-color:grey;";
  }
}
</script>
       <!--
       <input type="button" onclick="location.href='modus0';" value="Normal modus" />
       <input type="button" onclick="location.href='modus1';" value="Eco modus" />
       <input type="button" onclick="location.href='modus2';" value="Auto modus" />
       <input type="button" onclick="location.href='modus3';" value="Cool modus" /><br><br>
       -->
       <button id="normalbtn" onclick="location.href='/modus0';" style="color:grey"><h3>Normal modus</h3></button> 
       <button id="ecobtn" onclick="location.href='/modus1';" style="color:grey"><h3>Eco modus</h3></button> 
       <button id="autobtn" onclick="location.href='/modus2';" style="color:grey"><h3>Auto modus</h3></button> 
       <button id="coolbtn" onclick="location.href='/modus3';" style="color:grey"><h3>Cool modus</h3></button> 
       <br>
       www.Arduino.TK<br>
       Phonebrowser? &#8942; &#9776; add to startscreen and you have a quicklink to thermostat<br>
       wifi router ssid <input type="text" id="ssidtext" value="?" size="30" ><br>
       wifi router password <input type="text" id="passwordtext" value="?" size="30" ><br>
       </h1>
       <iframe id="1" src='http://10.10.100.100' width="350" height="300" scrolling="no" style="-moz-transform: scale(0.5, 0.5); -webkit-transform: scale(0.5, 0.5); -o-transform: scale(0.5, 0.5);"></iframe>
       <iframe id="2" src='http://10.10.100.101' width="350" height="300" scrolling="no" style="-moz-transform: scale(0.5, 0.5); -webkit-transform: scale(0.5, 0.5); -o-transform: scale(0.5, 0.5);"></iframe><br>
       <iframe id="3" src='http://10.10.100.102' width="350" height="300" scrolling="no" style="-moz-transform: scale(0.5, 0.5); -webkit-transform: scale(0.5, 0.5); -o-transform: scale(0.5, 0.5);"></iframe>
       <iframe id="1" src='http://10.10.100.10' width="350" height="300" scrolling="no" style="-moz-transform: scale(0.5, 0.5); -webkit-transform: scale(0.5, 0.5); -o-transform: scale(0.5, 0.5);"></iframe><br>
       <iframe id="2" src='http://10.10.100.10' width="350" height="300" scrolling="no" style="-moz-transform: scale(0.5, 0.5); -webkit-transform: scale(0.5, 0.5); -o-transform: scale(0.5, 0.5);"></iframe>
       <iframe id="1" src='http://10.10.100.10' width="350" height="300" scrolling="no" style="-moz-transform: scale(0.5, 0.5); -webkit-transform: scale(0.5, 0.5); -o-transform: scale(0.5, 0.5);"></iframe><br>
      
       
   
 </div>

</body>
</html>
)=====";


void handleRoot() {
  //String s = Web_page;             //Display HTML contents
  server.send(200, "text/html", Web_page); //Send web page
}

void handleTEMP() { // This function is called by the script to update the sensor value, in this example random data!
  String temp = String(BME280.readTemperature(),2);
  server.send(200, "text/plain", temp);
}

void handleHUMID() { // This function is called by the script to update the sensor value, in this example random data!
  String humid = String(BME280.readHumidity(),2);
  server.send(200, "text/plain", humid); //Send sensor reading when there's a client ajax request
}

void handlePRESS() { // This function is called by the script to update the sensor value, in this example random data!
  String pressure = String(BME280.readPressure() / 100.0F,2);
  server.send(200, "text/plain", pressure); //Send sensor reading when there's a client ajax request
}

void handlemodus() { // This function is called by the script to update the sensor value, in this example random data!
  String modusvalue = String(modus);
  server.send(200, "text/plain", modusvalue); //Send sensor reading when there's a client ajax request
}



void handlemodus0() { // This function is called by the script to update the sensor value, in this example random data!
  modus=0;
   String modusvalue = String(modus);
    server.send(200, "text/html", Web_page); //Send web page
  //server.send(200, "text/plain", modusvalue); //Send sensor reading when there's a client ajax request
}


void handlemodus1() { // This function is called by the script to update the sensor value, in this example random data!
  modus=1;
   String modusvalue = String(modus);
   server.send(200, "text/html", Web_page); //Send web page
  //server.send(200, "text/plain", modusvalue); //Send sensor reading when there's a client ajax request
}



void handlemodus2() { // This function is called by the script to update the sensor value, in this example random data!
  modus=2;
   String modusvalue = String(modus);
   server.send(200, "text/html", Web_page); //Send web page
  //server.send(200, "text/plain", modusvalue); //Send sensor reading when there's a client ajax request
}

void handlemodus3() { // This function is called by the script to update the sensor value, in this example random data!
  modus=3;
   String modusvalue = String(modus);
   server.send(200, "text/html", Web_page); //Send web page
  //server.send(200, "text/plain", modusvalue); //Send sensor reading when there's a client ajax request
}
