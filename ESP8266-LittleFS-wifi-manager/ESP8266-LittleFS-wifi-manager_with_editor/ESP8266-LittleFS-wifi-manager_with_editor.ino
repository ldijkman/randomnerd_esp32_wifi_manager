


// Got it working???
// Share a video link https://github.com/ldijkman/randomnerd_esp32_wifi_manager/discussions
//
// Bet you can do better as me => https://www.youtube.com/user/LuberthDijkman/videos
//
////////////////////////////////////////////////////////////////////////////////////////////////

//this one uses a fork from ESPASYNC library
//https://github.com/lorol/ESPAsyncWebServer
//or
//https://github.com/ldijkman/ESPAsyncWebServer

//donwload zip and replace existing ESPAsyncWebServer library, on my pi  /home/pi/Arduino/libraries/ESPAsyncWebServer-master


///////////////////////////////////////////////////////////////////////////////////////////////



// i have placed some videos on youtube
// for video overview
// https://www.youtube.com/user/LuberthDijkman/videos

// DO NOT FORGET TO SUBSCRIBE ?! ;-)



// quick modification for test change from esp32 & spiffs to esp8266 & littlefs  https://github.com/ldijkman/randomnerd_esp32_wifi_manager/discussions/4

// esp8266 LittleFS mDNS wifimanager
// tested on a 4mb wemos d1 mini esp8266 with relais shield relais gpio 5 == WORKING                  4mb(fs 2mb~ota 1019kb)
// tested on esp8266 nodemcu 4mb onboard LED gpio16 == WORKING (LED inverted)                         4mb(fs 2mb~ota 1019kb)
// tested on sonoff basic esp8285 1mb (programmed with esp8266 settings relais gpio13 == WORKING ;-)  1mb(fs 512~ota 246)

// my esp8266 arduino ide settings https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/images/20220121_172823.jpg

// LittleFS data upload tool for Arduino IDE
//             https://github.com/earlephilhower/arduino-esp8266littlefs-plugin
//             unzip in arduino/tools directory...restart arduino...now you should have in the menu  => Arduino IDE => Tools => ESP8266 LittleFS Data Upload


// now possible to reconfigure wifimanager from STA mode (esp8266 version)



//*********************
//     Hey Electra!
/*********************
  http://electra.local
    http://living.local
         http://kitchen.local
              http://garage.local
                   ETCETERA!
  Easy No Hassle home automation
  BrainPain free home automation
  Blondes friendly home automation
  Home Automation for Dummies
  each swith / device its own human friendly URL with webpage
     and each webpage should show an automaticly scanned linked list of all mDNS URL's devices in local network
  ******************************************************************************************************************************
  started with the example from
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-wi-fi-manager-asyncwebserver/
  ******************************************************************************************************************************
  i use arduino ide linux arm32 1.8.13 on raspberry pi  https://www.arduino.cc/en/software
  i use arduino ide linux arm32 1.8.19 on raspberry pi  https://www.arduino.cc/en/software
  you need to upload the data directory to LittleFS => Arduino IDE => Tools => ESP32 Sketch Data Upload (turn serial monitor off else failure)
    howto add to Arduino IDE and use LittleFS upload tool  https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
        or  place this/next zip file in => arduino/tools/ directory
                    https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/
                    https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/download/1.0/ESP32FS-1.0.zip
           and unzip it there
           restart arduino
           now you should have in the menu  => Arduino IDE => Tools => ESP32 Sketch Data Upload
  added mdns dot local URL
    wanted should show a scan to list all mdns devices dot local urls in local network automaticly on devices webpage
            https://github.com/ldijkman/Hey_Electra/blob/main/ESP32/ESP32_mDNS_list.ino
    wanted a settable countdown off timer is this called inching switch
    wanted easy set/overview timed settings webpage in this device https://jsfiddle.net/luberth/ow3zceyn/show/
  [x]  wanted dhcp ip settting not fixed  // Blondes do not know wat to enter  == solved
    wanted unique Access point AP name broadcasted in the air == "esp32 wifimanager" + chipid
    wanted set mDNS dot local url from wifimanager inputfield
    wanted page refresh to actual switch state if state is changed on another webpage    ajax or websockets?
    wanted i/o setting wifimager input field for relais i/o pin and/or status LED i/o pin
    wanted ntp time server input field in wifimanager
    wanted ntp time server offset input field in wifimanager
                                                                   https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino
                                                                   https://randomnerdtutorials.com/esp32-ntp-timezones-daylight-saving/
    wanted load change wifimanager.html settings from station STA mode
  [x]  wanted add OTA over the air updates
                                        https://randomnerdtutorials.com/esp32-ota-over-the-air-vs-code/
    wanted sunrise sunset times or geolocation
    wanted add available wifi broadcaster in the air ssid scan to wifimanager.html
  [x] wanted relais http://url_or_ip/status status html or text url webpage 0 or 1 for external programs status display
          http:// url or ip  /status   returns text 0 ro 1 for remote monitoring
          https://randomnerdtutorials.com/esp32-save-data-permanently-preferences/
          ESP32 Save Data Permanently using Preferences Library
          maybe this is better for saving settings
          maybe this will survive LittleFS sketch data upload or ota file system upload
          when in dhcp no ip address is known/shown on exit page wifimanager
          it should be possible to do a temp from ap to apsta connection to show user dhcp address
          but i have seen it only once in a german wifimanager
          https://www.john-lassen.de/en/projects/esp-8266-arduino-ide-webconfig
          no wrong i am mistaking
          ESP32 is dual core = 2 processors
          i think i use one
          looks like espasyncwebsrver does not like delaying in loop
          would it be possible to run parts of the code on the second unused core / processor?
*********/

// https://github.com/ldijkman/Hey_Electra/blob/main/ESP32/RandomNerd/ESP32_WiFi_Manager.ino
// https://github.com/ldijkman/randomnerd_esp32_wifi_manager


#include <Arduino.h>
#include "Hash.h"         // otherwise error sha1???? websockets
//#include <WiFi.h>


#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>                  // https://github.com/me-no-dev/ESPAsyncTCP
#include <ESP8266mDNS.h>


#include <FS.h>

#include <LittleFS.h>
#define MYFS LittleFS
//#include <AsyncElegantOTA.h>   //do not like it           // https://github.com/ayushsharma82/AsyncElegantOTA
#include <SPIFFSEditor.h>

#include <ESPAsyncWebServer.h>
//this one uses a fork from ESPASYNC library
//https://github.com/lorol/ESPAsyncWebServer
//or
//https://github.com/ldijkman/ESPAsyncWebServer

#include <ArduinoJson.h>
//#include <time.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com");   // do not know how to make this variable yet

//Week Days
String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

const char* http_username = "admin";
const char* http_password = "admin";



const uint8_t DEBOUNCE_DELAY = 10; // in milliseconds

//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;
String subnet;
String mdns;
String dhcpcheck;
String relaispin;
String statusledpin;
String buttonpin;
String ntpserver;
String ntptimeoffset;
String offdelay;
int offdelayint;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";
const char* subnetPath = "/subnet.txt";
const char* mdnsPath = "/mdns.txt";
const char* dhcpcheckPath = "/dhcpcheck.txt";
const char* relaispinPath = "/relaispin.txt";
const char* statusledpinPath = "/statusledpin.txt";
const char* buttonpinPath = "/buttonpin.txt";
const char* ntpserverPath = "/ntpserver.txt";
const char* ntptimeoffsetPath = "/ntptimeoffset.txt";
const char* offdelayPath = "/offdelay.txt";

int postsuccesfull = 0;
int notify = 0;



String formattedTime;

//next should become an input field for mdns dot local name in wifimanager
String mdnsdotlocalurl = "electra";    // becomes http://electra.local     give each device a unique name
// const char* mdnsdotlocalurl = "living";  // becomes http://living.local      give each device a unique name
// const char* mdnsdotlocalurl = "kitchen"; // becomes http://kitchen.local     give each device a unique name
// const char* mdnsdotlocalurl = "garage";  // becomes http://garage.local      give each device a unique name
// on android phone use the bonjour browser app to see the .local devices on the network
// https://play.google.com/store/apps/details?id=de.wellenvogel.bonjourbrowser&hl=en&gl=US
// apple does mdns?
// my raspberry pi does mdns!
// windows ?


IPAddress localIP(0, 0, 0, 0);
IPAddress gatewayIP(0, 0, 0, 0);
IPAddress subnetMask(0, 0, 0, 0);


// Timer variables
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds) removed did not work on esp8266 wifi connect crash reboot

String scanstr = "";  // %MDNSSCAN%


// Set LED GPIO
int ledPin = 5;    // wemos uno sized esp32 board
// Stores LED state

String ledState;


// Initialize LittleFS
void initLittleFS() {
  // if (!LittleFS.begin()) {
  //  Serial.println("An error has occurred while mounting LittleFS");
  //}
  //Serial.println("LittleFS mounted successfully");

  if (MYFS.begin()) {

    Serial.print(F("FS mounted\n"));
  } else {
    Serial.print(F("FS mount failed\n"));
  }


}

// Read File from LittleFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return String();
  }

  String fileContent;
  while (file.available()) {
    fileContent = file.readStringUntil('\n');
    break;
  }
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, "w");
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {//this one uses a fork from ESPASYNC library
    //https://github.com/lorol/ESPAsyncWebServer
    //or
    //https://github.com/ldijkman/ESPAsyncWebServer
    Serial.println("- frite failed");
  }
}





// Initialize WiFi
bool initWiFi() {
  if (ssid == "" /*|| ip == ""*/) {  // no ip // made it DHCP
    Serial.println("Undefined SSID wrong wifiroutername or wifirouterpassword");
    return false;
  }

  WiFi.mode(WIFI_STA);

  if (dhcpcheck == "on") {
    // dhcp

  } else {
    // fixed ip
    localIP.fromString(ip.c_str());
    gatewayIP.fromString(gateway.c_str());
    subnetMask.fromString(subnet.c_str());

    if (!WiFi.config(localIP, gatewayIP, subnetMask)) {
      Serial.println("STA Failed to configure");
      return false;
    }
  }

  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Connecting to WiFi...");


  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (i >= 20) {
      Serial.println("Failed to connect. in 20sec");
      return false;
    }
    delay(1000);
    Serial.print(i); Serial.print(' ');
    i++;
  }
  delay(500);
  Serial.println("");
  Serial.println(WiFi.localIP());


  if (!MDNS.begin(mdnsdotlocalurl.c_str())) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }

  MDNS.addService("http", "tcp", 80);

  Serial.print("http://");
  Serial.print(mdnsdotlocalurl);
  Serial.println(".local");
  return true;
}




// Replaces placeholder with LED state value
// replaces the text between %match% in LittleFS index.html on upload with actual variables
String processor(const String& var) {

  // it has become a bit copy paste mess relaspin ledpin ledstate
  if (var == "STATE") {                 // in index.html noted as &STATE&
    if (digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return String(ledState);
  }
  else if (var == "MDNSNAME") {                                      // in index.html noted as %MDNSNAME%
    return String(mdnsdotlocalurl);
  } else if (var == "IP") {                                          // in index.html noted as %IP%
    return WiFi.localIP().toString();
  } else if (var == "GATEWAY") {                                    // in index.html noted as %GATEWAY%
    return WiFi.gatewayIP().toString();
  } else if (var == "SUBNET") {                                     // in index.html noted as %SUBNET%
    return WiFi.subnetMask().toString();
  } else if (var == "OFFDELAY") {                                   // in index.html noted as %OFFDELAY%
    return offdelay.c_str();
  } else if (var == "NTPTIME") {                                    // in index.html noted as &NTPTIME&
    String mystring = "time ntp";
    return mystring;
  } else if (var == "MDNSSCAN") {                                     // in index.html noted as %MDNSSCAN%
    String mystring = scanstr;
    return mystring;
  } else if (var == "NETWORKINFO") {                                   // in index.html noted as %NETWORKINFO%
    String mystring = "mDNS: " + String(mdnsdotlocalurl) + ".local<br>";
    mystring += "SSID: " + ssid + "<br>";
    mystring += " DHCP: " + dhcpcheck + "<br>";
    mystring += "IP: " + WiFi.localIP().toString() + "<br>";
    mystring += "GateWay: " + WiFi.gatewayIP().toString() + "<br>";
    mystring +=  "<a href=\"http://" + WiFi.gatewayIP().toString() + "\">Maybe WiFiRouter Admin / Config page</a><br>";
    mystring += "Subnet: " + WiFi.subnetMask().toString() + "<br>";
    mystring += "DNS: " + WiFi.dnsIP().toString() + "<br>";
    mystring += "MAC: " + WiFi.macAddress() + "<br>";
    mystring += "NTP Server: " + ntpserver + "<br>";
    mystring += "NTP Offset " + ntptimeoffset + " hour <br>";
    return mystring;
  }

  return String();
}







void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initLittleFS();
  initWebSocket();



  // Load values saved in LittleFS
  ssid = readFile(MYFS, ssidPath);
  Serial.println(ssid);
  pass = readFile(MYFS, passPath);
  Serial.println(pass);
  ip = readFile(MYFS, ipPath);
  Serial.println(ip);
  gateway = readFile(MYFS, gatewayPath);
  Serial.println(gateway);
  subnet = readFile(MYFS, subnetPath);
  Serial.println(subnet);
  mdnsdotlocalurl = readFile(MYFS, mdnsPath);
  Serial.println(mdnsdotlocalurl);
  dhcpcheck = readFile(MYFS, dhcpcheckPath);
  Serial.println(dhcpcheck);
  relaispin = readFile(MYFS, relaispinPath);
  Serial.println(relaispin);

  ledPin = relaispin.toInt();
  Serial.println(relaispin);

  statusledpin = readFile(MYFS, statusledpinPath);
  Serial.println(statusledpin);
  buttonpin = readFile(MYFS, buttonpinPath);
  Serial.println(buttonpin);
  ntpserver = readFile(MYFS, ntpserverPath);
  Serial.println(ntpserver);
  ntptimeoffset = readFile(MYFS, ntptimeoffsetPath);
  Serial.println(ntptimeoffset);


  offdelay = readFile(MYFS, offdelayPath);
  Serial.println(offdelay);
  if (offdelay.toInt() < 10) {
    offdelay = 360;
  }

  offdelayint = offdelay.toInt();
  Serial.println(offdelay);

  // Set GPIO ledPin as an OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);




  if (initWiFi()) {

    events.onConnect([](AsyncEventSourceClient * client) {
      client->send("hello!", NULL, millis(), 1000);
    });
    server.addHandler(&events);

    server.addHandler(new SPIFFSEditor(http_username, http_password, MYFS));

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(MYFS, "/index.html", "text/html", false, processor);
      notify = 1;
    });

    //server.serveStatic("/", LittleFS, "/");
    server.serveStatic("/", MYFS, "/").setDefaultFile("/index.htm");

    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
      digitalWrite(ledPin, HIGH);
      ledState = "ON";
      request->send(MYFS, "/index.html", "text/html", false, processor);
      notify = 1;
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
      digitalWrite(ledPin, LOW);
      ledState = "OFF";
      request->send(MYFS, "/index.html", "text/html", false, processor);
      notify = 1;
    });

    //  /status returns text 0 ro 1 for remote monitoring
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest * request) {
      int readval = digitalRead(ledPin);
      request->send(200, "text/txt", String(readval));
    });


    //  /resetwifitoap
    server.on("/resetwifitoap", HTTP_GET, [](AsyncWebServerRequest * request) {
      LittleFS.remove("/ssid.txt");
      LittleFS.remove("/pass.txt");
      request->send(200, "text/html", "<h1>deleted wifi credentials ssid.txt and pass.txt<br>Done.<br>ESP restart,<br>connect to AP access point ESP WIFI MANAGER <br>to configure wifi settings again<br><a href=\"http://192.168.4.1\">http://192.168.4.1</a></h1>");
      delay(5000);
      ESP.restart();
    });

    //  /reboot
    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(200, "text/html", "<h1>Huh, Reboot Electra, Restart ESP32<br><a href=\"http://" + WiFi.localIP().toString()  + "\">http://" + WiFi.localIP().toString() + "</a></h1>");
      delay(5000);
      ESP.restart();
    });

    server.on("/timer", HTTP_POST, [](AsyncWebServerRequest * request) {
      int params = request->params();
      for (int i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isPost()) {
          // HTTP POST ssid value
          const char* PARAM_INPUT_20 = "off";                  // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_20) {
            offdelay = p->value().toInt();
            Serial.print("offdelay set to: ");
            Serial.println(offdelay);
            // Write file to save value
            writeFile(MYFS, offdelayPath, offdelay.c_str());
            offdelayint = offdelay.toInt();
            Serial.println(offdelayint);
          }
        }
      }
      request->send(MYFS, "/index.html", "text/html", false, processor);
    });


    server.on("/list", HTTP_GET, [](AsyncWebServerRequest * request) {    // /list files in LittleFS on webpage
      if (!MYFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
      }

      File root = MYFS.open("/", "r");
      File file = root.openNextFile();
      String str = "";
      while (file) {
        str += " / ";
        str += file.name();
        str += "\r\n";
        file = root.openNextFile();
      }
      str += "\r\n";
      str += "\r\n";
      str += "totalBytes   ";
      //str += LittleFS.totalBytes();
      str += "\r\n";
      str += "usedBytes    ";
      //str += LittleFS.usedBytes();
      str += "\r\n";
      str += "freeBytes??? ";
      //str += LittleFS.totalBytes()-LittleFS.usedBytes();
      str += "\r\n";
      request->send(200, "text/txt", str);
    });


    server.on("/heap", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(200, "text/plain", String(ESP.getFreeHeap()));
    });




    server.onNotFound([](AsyncWebServerRequest * request) {
      Serial.printf("NOT_FOUND: ");
      if (request->method() == HTTP_GET)
        Serial.printf("GET");
      else if (request->method() == HTTP_POST)
        Serial.printf("POST");
      else if (request->method() == HTTP_DELETE)
        Serial.printf("DELETE");
      else if (request->method() == HTTP_PUT)
        Serial.printf("PUT");
      else if (request->method() == HTTP_PATCH)
        Serial.printf("PATCH");
      else if (request->method() == HTTP_HEAD)
        Serial.printf("HEAD");
      else if (request->method() == HTTP_OPTIONS)
        Serial.printf("OPTIONS");
      else
        Serial.printf("UNKNOWN");
      Serial.printf(" http://%s%s\n", request->host().c_str(), request->url().c_str());

      if (request->contentLength()) {
        Serial.printf("_CONTENT_TYPE: %s\n", request->contentType().c_str());
        Serial.printf("_CONTENT_LENGTH: %u\n", request->contentLength());
      }

      int headers = request->headers();
      int i;
      for (i = 0; i < headers; i++) {
        AsyncWebHeader* h = request->getHeader(i);
        Serial.printf("_HEADER[%s]: %s\n", h->name().c_str(), h->value().c_str());
      }

      int params = request->params();
      for (i = 0; i < params; i++) {
        AsyncWebParameter* p = request->getParam(i);
        if (p->isFile()) {
          Serial.printf("_FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
        } else if (p->isPost()) {
          Serial.printf("_POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        } else {
          Serial.printf("_GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }

      // request->send(404);
      request->send(MYFS, "/index.htm", "text/html", false);
    });
    server.onFileUpload([](AsyncWebServerRequest * request, const String & filename, size_t index, uint8_t *data, size_t len, bool final) {
      if (!index)
        Serial.printf("UploadStart: %s\n", filename.c_str());
      Serial.printf("%s", (const char*)data);
      if (final)
        Serial.printf("UploadEnd: %s (%u)\n", filename.c_str(), index + len);
    });
    server.onRequestBody([](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      if (!index)
        Serial.printf("BodyStart: %u\n", total);
      Serial.printf("%s", (const char*)data);
      if (index + len == total)
        Serial.printf("BodyEnd: %u\n", total);
    });












    checkpost();   // post submit for AP and STA?




    // AsyncElegantOTA.begin(&server);    // Start ElegantOTA
    server.begin();

  }///////////////////////////////////////////////////////////////////
  else {
    // Connect to Wi-Fi network with SSID and password == setup an AP AccessPoint for wifi direct connect
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    //String broadcastintheair = String("ESP-WIFI-MANAGER-") + WiFi.macAddress().c_str();  // want a unique broadcast id for each device
    //String broadcastintheair = String("ESP-WIFI-MANAGER-") + WiFi.macAddress().c_str();  // esp32   want a unique broadcast id for each device
    String broadcastintheair = String("ESP-WIFI-MANAGER-") + ESP.getChipId();              // esp8266 want a unique broadcast id for each device

    WiFi.softAP(broadcastintheair.c_str(), NULL);                                        // i do not know, strings and chars thing drive me nuts
    // i have seen all errors possible, getting this working ;-)

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(MYFS, "/wifimanager.html", "text/html");
    });

    server.serveStatic("/", MYFS, "/");

    checkpost();   // post submit for AP and STA?

    server.begin();
  }

  int offset = (ntptimeoffset.toInt() * 3600);
  timeClient.setTimeOffset(offset);
  Serial.print("ntptimeoffset sec "); Serial.println(offset);

  NTPClient timeClient(ntpUDP, ntpserver.c_str());   // do not know how to make this variable yet
  Serial.println(ntpserver.c_str());


  timeClient.begin();


}

unsigned long startmillis = 0;




// loop // // loop // // loop // // loop // // loop // // loop // // loop // // loop // // loop //
void loop() {
  timeClient.update();
  ws.cleanupClients();

  // if ( digitalread hardware_button.pressed()) {
  // while  ( digitalread hardware_button.pressed()) {//bounce}
  // }
  // toggle state
  // notifyClients();
  // }

  if (postsuccesfull == 1) {
    postsuccesfull = 0;
    delay(5000);
    Serial.println(""); Serial.println("Restart"); Serial.println("");
    ESP.restart();
  }

  if (notify == 1) {        // switch from url /on / off notifyClients
    notify = 0;
    delay(250);
    notifyClients();
  }

  MDNS.update();   // looks like this is needed only for esp8266 otherwise i dont see mdns url in bonjourbrowser not needed for esp32

  if (millis() - startmillis >= 10000) {    // non blocking delay 10 seconds
    startmillis = millis();                 // scan for mdns devices urls every ??? seconds
    browseService("http", "tcp");

    Serial.print("ntpserver "); Serial.println(ntpserver.c_str());
    Serial.print("ntptimeoffset sec "); Serial.println((ntptimeoffset.toInt() * 3600));

// https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/
    unsigned long epochTime = timeClient.getEpochTime();
    // Serial.print("Epoch Time: ");
    // Serial.println(epochTime);    // Epoch Time: 1644662416


    formattedTime = timeClient.getFormattedTime();
    //Serial.print("Formatted Time: ");
    //Serial.println(formattedTime);  // Formatted Time: 10:40:16

    int currentHour = timeClient.getHours();
 //   Serial.print("Hour: ");
 //   Serial.println(currentHour);

    int currentMinute = timeClient.getMinutes();
 //   Serial.print("Minutes: ");
 //   Serial.println(currentMinute);

    int currentSecond = timeClient.getSeconds();
//    Serial.print("Seconds: ");
//    Serial.println(currentSecond);

    String weekDay = weekDays[timeClient.getDay()];
//    Serial.print("Week Day: ");
//    Serial.println(weekDay);

    //Get a time structure
    struct tm *ptm = gmtime ((time_t *)&epochTime);

    int monthDay = ptm->tm_mday;
//    Serial.print("Month day: ");
//    Serial.println(monthDay);

    int currentMonth = ptm->tm_mon + 1;
//    Serial.print("Month: ");
//    Serial.println(currentMonth);

    String currentMonthName = months[currentMonth - 1];
//    Serial.print("Month name: ");
//    Serial.println(currentMonthName);

    int currentYear = ptm->tm_year + 1900;
//    Serial.print("Year: ");
//    Serial.println(currentYear);

    //Print complete date:
//    String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
//    Serial.print("Current date: ");
//    Serial.println(currentDate);

//    Serial.println("");
// https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/



  }




  /*
    Serial.println("scan start");
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
     Serial.println("no networks found");
    } else {
     Serial.print(n);
     Serial.println(" networks found");
     for (int i = 0; i < n; ++i) {
       // Print SSID and RSSI for each network found
       Serial.print(i + 1);
       Serial.print(": ");
       Serial.print(WiFi.SSID(i));
       Serial.print(" (");
       Serial.print(WiFi.RSSI(i));
       Serial.print(")");
       Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
       delay(10);
     }
    }
    Serial.println("");
    }
  */
}


////////////////////////////////////////////////////////////////////////////////////////////
// checkpost in a function so that wifimanager page can be configured from AP and from STA
////////////////////////////////////////////////////////////////////////////////////////////
void checkpost() {
  server.on("/", HTTP_POST, [](AsyncWebServerRequest * request) {
    int params = request->params();
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      if (p->isPost()) {
        // HTTP POST ssid value
        const char* PARAM_INPUT_1 = "ssid";                  // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_1) {
          ssid = p->value().c_str();
          Serial.print("SSID set to: ");
          Serial.println(ssid);
          // Write file to save value
          writeFile(MYFS, ssidPath, ssid.c_str());
        }
        // HTTP POST pass value
        const char* PARAM_INPUT_2 = "pass";                 // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_2) {
          pass = p->value().c_str();
          Serial.print("Password set to: ");
          Serial.println(pass);
          // Write file to save value
          writeFile(MYFS, passPath, pass.c_str());
        }
        // HTTP POST ip value
        const char* PARAM_INPUT_3 = "ip";                   // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_3) {
          dhcpcheck = "off";
          writeFile(MYFS, dhcpcheckPath, "off");          //dhcp unchecked . if we recieve post with ip set dhcpcheck.txt file to off
          ip = p->value().c_str();
          Serial.print("IP Address set to: ");
          Serial.println(ip);
          writeFile(MYFS, ipPath, ip.c_str());            // Write file to save value
        }
        // HTTP POST gateway value
        const char* PARAM_INPUT_4 = "gateway";              // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_4) {
          gateway = p->value().c_str();
          Serial.print("gateway Address set to: ");
          Serial.println(gateway);
          writeFile(MYFS, gatewayPath, gateway.c_str());          // Write file to save value
        }

        // HTTP POST subnet value
        const char* PARAM_INPUT_5 = "subnet";               // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_5) {
          subnet = p->value().c_str();
          Serial.print("subnet Address set to: ");
          Serial.println(subnet);
          writeFile(MYFS, subnetPath, subnet.c_str());            // Write file to save value
        }
        // HTTP POST mdns value
        const char* PARAM_INPUT_6 = "mdns";                 // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_6) {
          mdnsdotlocalurl = p->value().c_str();
          Serial.print("mdnsdotlocalurl Address set to: ");
          Serial.println(mdnsdotlocalurl);
          writeFile(MYFS, mdnsPath, mdnsdotlocalurl.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_7 = "dhcp";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_7) {
          dhcpcheck = p->value().c_str();
          Serial.print("dhcpcheck set to: ");
          Serial.println(dhcpcheck);
          writeFile(MYFS, dhcpcheckPath, dhcpcheck.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_8 = "relaispin";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_8) {
          relaispin = p->value().c_str();
          Serial.print("relaispin set to: ");
          Serial.println(relaispin);
          writeFile(MYFS, relaispinPath, relaispin.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_9 = "statusledpin";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_9) {
          statusledpin = p->value().c_str();
          Serial.print("statusledpin set to: ");
          Serial.println(statusledpin);
          writeFile(MYFS, statusledpinPath, statusledpin.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_10 = "buttonpin";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_10) {
          buttonpin = p->value().c_str();
          Serial.print("buttonpin set to: ");
          Serial.println(buttonpin);
          writeFile(MYFS, buttonpinPath, buttonpin.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_11 = "ntpserver";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_11) {
          ntpserver = p->value().c_str();
          Serial.print("ntpserver set to: ");
          Serial.println(ntpserver);
          writeFile(MYFS, ntpserverPath, ntpserver.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_12 = "ntptimeoffset";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_12) {
          ntptimeoffset = p->value().c_str();
          Serial.print("ntptimeoffset set to: ");
          Serial.println(ntptimeoffset);
          writeFile(MYFS, ntptimeoffsetPath, ntptimeoffset.c_str());            // Write file to save value
        }



        //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }
    if (dhcpcheck == "on") {
      ip = "dhcp ip adress";
    }
    request->send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"15; url=http://" + mdnsdotlocalurl + ".local\"><h1>Done.<br> ESP8266 Reboot AutoReConnect Sequence Activated! ;-)<br>This page wil reload to mDNS URL address in 15 seconds<br> connect router <br>go to: <a href=\"http://" + ip + "\">" + ip + "</a><br><a href=\"http://" + mdnsdotlocalurl + ".local\">http://" + mdnsdotlocalurl + ".local</a> Android use BonjourBrowser App</h1>");

    postsuccesfull = 1;

  });



}






// next only works/shows its great usefulness if there are more ESP mDNS URL devices on the local network
// scanned mdns url linked list should be on main webpage refreshed every ?? seconds
// for now prints to serial monitor
// https://github.com/ldijkman/Hey_Electra/blob/main/ESP32/ESP32_mDNS_list.ino

void browseService(const char * service, const char * proto) {
  //scanstr += ("Browsing for service _%s._%s.local. ... ", service, proto);
  int n = MDNS.queryService(service, proto);
  scanstr = "";
  if (n == 0) {
    scanstr += "<font color=\"red\"><b>No other Devices found in local network<br>\n\r Program more devices with this software<br>\n\r  And See / Release the power off Electra ;-)<br></b></font>\n\r";
  } else {
    scanstr += "\n\r";
    scanstr += n;
    scanstr += " Other Device(s) found on local network";
    scanstr += "\n\r";
    Serial.print(scanstr);
    scanstr = "";
    for (int i = 0; i < n; i++) {
      //scanstr += "  ";
      //scanstr += i + 1;
      scanstr += "<p><a href=\"http://";
      scanstr += MDNS.IP(i).toString() + ":";
      scanstr += MDNS.port(i);
      scanstr += "\">";
      scanstr += MDNS.hostname(i);
      //scanstr += ".local</a><br>";    // esp32 does it different ???
      scanstr += "</a></p>";          // esp8266 does it different ???
      //scanstr += "\n\r";

    }
  }
  Serial.print(scanstr);
  Serial.println("");
  Serial.println("Soon Electra will Power a Gazillion Devices");
  Serial.println("");

  Serial.print("WiFi.status == ");
  Serial.print(WiFi.status());
  Serial.print(": ");

  switch (WiFi.status()) {
    case 0:
      Serial.println("WL_IDLE_STATUS");
      break;
    case 1:
      Serial.println("WL_NO_SSID_AVAIL");
      break;
    case 2:
      Serial.println("WL_SCAN_COMPLETED");
      break;
    case 3:
      Serial.println("WL_CONNECTED");
      break;
    case 4:
      Serial.println("WL_CONNECT_FAILED");
      break;
    case 5:
      Serial.println("WL_CONNECTION_LOST");
      break;
    case 6:
      Serial.println("WL_DISCONNECTED");
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
  Serial.println("");
  notifyClients();

}

// ----------------------------------------------------------------------------
// WebSocket initialization
// ----------------------------------------------------------------------------
// copyed code from https://github.com/m1cr0lab-esp32/remote-control-with-websocket
// copyed code from https://github.com/rheinz/remote-control-with-websocket

void notifyClients() {
  const unsigned int size = JSON_OBJECT_SIZE(1024);//i do not know
  StaticJsonDocument<size> json;

  // it has become a bit copy paste mess relaspin ledpin ledstate
  //Serial.println(ledState.c_str());
  //Serial.println(scanstr);
  json["status"] = ledState.c_str(); // relais status
  json["time"] = formattedTime.c_str();
  json["offdelay"] = offdelay.c_str();
  json["scan"] = scanstr.c_str();   // mdnsscan

  char buffer[1024];   //i do not know
  serializeJson(json, Serial);
  size_t len = serializeJson(json, buffer); //print to serial monitor
  ws.textAll(buffer, len);
  Serial.println(buffer);
}
/*
  void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  //AwsFrameInfo *info = (AwsFrameInfo*)arg;
  //if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT){
    const uint8_t size = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<size> json;
    DeserializationError err = deserializeJson(json, data);
    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
      return;
    }
    deserializeJson(json, Serial);


    // it has become a bit copy paste mess relaspin ledpin ledstate
   const char * action = json["action"];
   Serial.println("action");
   Serial.println(action);
    if (action) {
       Serial.println("i am in action");
      if (strcmp(action, "toggle") == 0) {
        //ledPin = !ledPin;
        if (digitalRead(ledPin) == 0) {
          digitalWrite(ledPin, HIGH);
          ledState = "ON";
        } else {
          digitalWrite(ledPin, LOW);
          ledState = "OFF";
        }
        Serial.println(ledState);
        notifyClients();

      }
    }
    Serial.println("off_delay");
    const char * off_delay = json["off_delay"];
     Serial.println(off_delay);


  //}
  }
*/

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {

    const uint8_t size = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<size> json;
    DeserializationError err = deserializeJson(json, data);
    if (err) {
      Serial.print(F("deserializeJson() failed with code "));
      Serial.println(err.c_str());
      return;
    }
    // deserializeJson(json, Serial);


    // it has become a bit copy paste mess relaspin ledpin ledstate
    const char *action = json["action"];
    const char * off_delay = json["off_delay"];


    Serial.print("action="); Serial.println(action);
    if (json["action"] == "toggle") {
      //ledPin = !ledPin;
      if (digitalRead(ledPin) == 0) {
        digitalWrite(ledPin, HIGH);
        ledState = "ON";
      } else {
        digitalWrite(ledPin, LOW);
        ledState = "OFF";
      }
      Serial.println(ledState);
      notifyClients();
    }

    Serial.print("off_delay="); Serial.println(off_delay);
    Serial.print("offdelay="); Serial.println(offdelay);
    if (json["off_delay"]) {
      offdelay  = atoi(off_delay);
      Serial.print("off_delay="); Serial.println(off_delay);
      Serial.print("offdelay="); Serial.println(offdelay);
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket       *server,
             AsyncWebSocketClient *client,
             AwsEventType          type,
             void                 *arg,
             uint8_t              *data,
             size_t                len) {

  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}




void initWebSocket() {
  ws.onEvent(onEvent);
  // ws.onEvent(onWsEvent); // part of fsbrowser example turned off
  server.addHandler(&ws);

}



/*
 * luberth => turned off  part from fs browser example

//////////////////////////////////////////////////////////////
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.printf("ws[%s][%u] connect\n", server->url(), client->id());
    client->printf("Hello Client %u :)", client->id());
    client->ping();
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.printf("ws[%s][%u] disconnect\n", server->url(), client->id());
  } else if (type == WS_EVT_ERROR) {
    Serial.printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t*)arg), (char*)data);
  } else if (type == WS_EVT_PONG) {
    Serial.printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char*)data : "");
  } else if (type == WS_EVT_DATA) {

    AwsFrameInfo * info = (AwsFrameInfo*)arg;
    /////////////////////////////////////////////////////////////////////////////////////////////////
    //handleWebSocketMessage(arg, data, len); //////////////////////// it is i, luberth old line insert
    ///////////////////////////////////////////////////////////////////////////////
    String msg = "";
    if (info->final && info->index == 0 && info->len == len) {
      //the whole message is in a single frame and we got all of it's data
      Serial.printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);

      if (info->opcode == WS_TEXT) {
        for (size_t i = 0; i < info->len; i++) {
          msg += (char) data[i];
          //Serial.print("line 1151 "); Serial.println(char(data[i]));
        }
      } else {
        char buff[3];
        for (size_t i = 0; i < info->len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      Serial.printf("%s\n", msg.c_str());
      Serial.print(msg);


      if (info->opcode == WS_TEXT)
        client->text("I got your text message");
      else
        client->binary("I got your binary message");
    } else {
      //message is comprised of multiple frames or the frame is split into multiple packets
      if (info->index == 0) {
        if (info->num == 0)
          Serial.printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
        Serial.printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
      }

      Serial.printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);

      if (info->opcode == WS_TEXT) {
        for (size_t i = 0; i < len; i++) {
          msg += (char) data[i];
        }
      } else {
        char buff[3];
        for (size_t i = 0; i < len; i++) {
          sprintf(buff, "%02x ", (uint8_t) data[i]);
          msg += buff ;
        }
      }
      Serial.printf("%s\n", msg.c_str());

      if ((info->index + len) == info->len) {
        Serial.printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
        if (info->final) {
          Serial.printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
          if (info->message_opcode == WS_TEXT)
            client->text("I got your text message");
          else
            client->binary("I got your binary message");
        }
      }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //handleWebSocketMessage(arg, data, len); //////////////////////// it is i, luberth old line insert
    ///////////////////////////////////////////////////////////////////////////////
  }
}
////////////////////////////////////////////////////

*/

  // Got it working???
  // Share a video link https://github.com/ldijkman/randomnerd_esp32_wifi_manager/discussions
  // Bet you can do better as me => https://www.youtube.com/user/LuberthDijkman/videos
  // http://paypal.me/LDijkman

// Me NO programmer, just trying, wasting loads of time drinking loads of coffee, but makes more sense to me as solving crossword puzzles
// My Mothers and Fathers Language whas Dutch, Thats what they learned me, That Explains my poor Englisch.
// Partly Made in Portugal &&  Partly Made in Holland
// Electra, Please let me Sleep
//
// Soon Electra will Power a Gazillion Devices
