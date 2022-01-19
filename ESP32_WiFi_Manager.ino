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

  you need to upload the data directory to spiffs => Arduino IDE => Tools => ESP32 Sketch Data Upload (turn serial monitor off else failure)
    howto add to Arduino IDE and use spiffs upload tool  https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
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
          maybe this will survive spiffs sketch data upload or ota file system upload


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
#include <WiFi.h>
#include <ESPAsyncWebServer.h>            // https://github.com/me-no-dev/ESPAsyncWebServer
// download zip from above->Arduino IDE->menu->tab->sketch->include library->add ZIP library
#include <AsyncTCP.h>                     // https://github.com/me-no-dev/AsyncTCP
// download zip from above->Arduino IDE->menu->tab->sketch->include library->add ZIP library
#include "SPIFFS.h"
#include <ESPmDNS.h>
//#include <NoDelay.h>                    // nonblocking delay https://www.arduino.cc/reference/en/libraries/nodelay/
#include <AsyncElegantOTA.h>              // https://github.com/ayushsharma82/AsyncElegantOTA
// download zip from above->Arduino IDE->menu->tab->sketch->include library->add ZIP library


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);




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
String ntptime;
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
const char* ntptimePath = "/ntptime.txt";
const char* ntptimeoffsetPath = "/ntptimeoffset.txt";
const char* offdelayPath = "/offdelay.txt";

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
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)

// Set LED GPIO
int ledPin = 5;    // wemos uno sized esp32 board
// Stores LED state

String ledState;

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");
}

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
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

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("- failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {
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

  unsigned long currentMillis = millis();
  previousMillis = currentMillis;

  while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Failed to connect.");
      return false;
    }
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
// replaces the text between %match% in spiffs index.html on upload with actual variables
String processor(const String& var) {
  if (var == "STATE") {                 // in index.html noted as &STATE&
    if (digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return ledState;
    return String();
  }
  else if (var == "MDNSNAME") {                  // in index.html noted as &MDNSNAME&
    return String(mdnsdotlocalurl);
  } else if (var == "IP") {                      // in index.html noted as &IP&
    return ssid+"<br>"+WiFi.localIP().toString() + " DHCP: " + dhcpcheck ;
  } else if (var == "GATEWAY") {                // in index.html noted as &GATEWAY&
    return WiFi.gatewayIP().toString();
  } else if (var == "SUBNET") {                  // in index.html noted as &SUBNET&
    return WiFi.subnetMask().toString() + "<br>DNS: " + WiFi.dnsIP().toString() + "<br>MAC: " + WiFi.macAddress();
  } else if (var == "OFFDELAY") {                  // in index.html noted as &OFFDELAY&
    return offdelay.c_str();
  } else if (var == "NTPTIME") {                  // in index.html noted as &NTPTIME&
    String mystring = "time ntp";
    return mystring;
  }

  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initSPIFFS();



  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  Serial.println(ssid);
  pass = readFile(SPIFFS, passPath);
  Serial.println(pass);
  ip = readFile(SPIFFS, ipPath);
  Serial.println(ip);
  gateway = readFile(SPIFFS, gatewayPath);
  Serial.println(gateway);
  subnet = readFile(SPIFFS, subnetPath);
  Serial.println(subnet);
  mdnsdotlocalurl = readFile(SPIFFS, mdnsPath);
  Serial.println(mdnsdotlocalurl);
  dhcpcheck = readFile(SPIFFS, dhcpcheckPath);
  Serial.println(dhcpcheck);
  relaispin = readFile(SPIFFS, relaispinPath);
  Serial.println(relaispin);

  ledPin = relaispin.toInt();
  Serial.println(relaispin);

  statusledpin = readFile(SPIFFS, statusledpinPath);
  Serial.println(statusledpin);
  buttonpin = readFile(SPIFFS, buttonpinPath);
  Serial.println(buttonpin);
  ntptime = readFile(SPIFFS, ntptimePath);
  Serial.println(ntptime);
  ntptimeoffset = readFile(SPIFFS, ntptimeoffsetPath);
  Serial.println(ntptimeoffset);


  offdelay = readFile(SPIFFS, offdelayPath);
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
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });
    server.serveStatic("/", SPIFFS, "/");

    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
      digitalWrite(ledPin, HIGH);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
      digitalWrite(ledPin, LOW);
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });

    //  /status returns text 0 ro 1 for remote monitoring
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest * request) {
      int readval = digitalRead(ledPin);
      request->send(200, "text/txt", String(readval));
    });


    //  /resetwifitoap
    server.on("/resetwifitoap", HTTP_GET, [](AsyncWebServerRequest * request) {
      SPIFFS.remove("/ssid.txt");
      SPIFFS.remove("/pass.txt");
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
            writeFile(SPIFFS, offdelayPath, offdelay.c_str());
            offdelayint = offdelay.toInt();
            Serial.println(offdelayint);
          }
        }
      }
      request->send(SPIFFS, "/index.html", "text/html", false, processor);
    });


    server.on("/list", HTTP_GET, [](AsyncWebServerRequest * request) {    // /list files in spiffs on webpage
      if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
      }

      File root = SPIFFS.open("/");
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
      str += SPIFFS.totalBytes();
      str += "\r\n";
      str += "usedBytes    ";
      str += SPIFFS.usedBytes();
      str += "\r\n";
      str += "freeBytes??? ";
      str += SPIFFS.totalBytes()-SPIFFS.usedBytes();
      str += "\r\n";
      request->send(200, "text/txt", str);
    });

    AsyncElegantOTA.begin(&server);    // Start ElegantOTA
    server.begin();
  }
  else {
    // Connect to Wi-Fi network with SSID and password == setup an AP AccessPoint for wifi direct connect
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    String broadcastintheair = String("ESP-WIFI-MANAGER-") + WiFi.macAddress().c_str();  // want a unique broadcast id for each device
    WiFi.softAP(broadcastintheair.c_str(), NULL);                                        // i do not know, strings and chars thing drive me nuts
                                                                                         // i have seen all errors possible, getting this working ;-)

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(SPIFFS, "/wifimanager.html", "text/html");
    });

    server.serveStatic("/", SPIFFS, "/");

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
            writeFile(SPIFFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          const char* PARAM_INPUT_2 = "pass";                 // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(SPIFFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          const char* PARAM_INPUT_3 = "ip";                   // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_3) {
            dhcpcheck = "off";
            writeFile(SPIFFS, dhcpcheckPath, "off");          //dhcp unchecked . if we recieve post with ip set dhcpcheck.txt file to off
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            writeFile(SPIFFS, ipPath, ip.c_str());            // Write file to save value
          }
          // HTTP POST gateway value
          const char* PARAM_INPUT_4 = "gateway";              // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("gateway Address set to: ");
            Serial.println(gateway);
            writeFile(SPIFFS, gatewayPath, gateway.c_str());          // Write file to save value
          }

          // HTTP POST subnet value
          const char* PARAM_INPUT_5 = "subnet";               // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_5) {
            subnet = p->value().c_str();
            Serial.print("subnet Address set to: ");
            Serial.println(subnet);
            writeFile(SPIFFS, subnetPath, subnet.c_str());            // Write file to save value
          }
          // HTTP POST mdns value
          const char* PARAM_INPUT_6 = "mdns";                 // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_6) {
            mdnsdotlocalurl = p->value().c_str();
            Serial.print("mdnsdotlocalurl Address set to: ");
            Serial.println(mdnsdotlocalurl);
            writeFile(SPIFFS, mdnsPath, mdnsdotlocalurl.c_str());            // Write file to save value
          }
          // HTTP POST dhcp value on
          const char* PARAM_INPUT_7 = "dhcp";                // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_7) {
            dhcpcheck = p->value().c_str();
            Serial.print("dhcpcheck set to: ");
            Serial.println(dhcpcheck);
            writeFile(SPIFFS, dhcpcheckPath, dhcpcheck.c_str());            // Write file to save value
          }
          // HTTP POST dhcp value on
          const char* PARAM_INPUT_8 = "relaispin";                // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_8) {
            relaispin = p->value().c_str();
            Serial.print("relaispin set to: ");
            Serial.println(relaispin);
            writeFile(SPIFFS, relaispinPath, relaispin.c_str());            // Write file to save value
          }
          // HTTP POST dhcp value on
          const char* PARAM_INPUT_9 = "statusledpin";                // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_9) {
            statusledpin = p->value().c_str();
            Serial.print("statusledpin set to: ");
            Serial.println(statusledpin);
            writeFile(SPIFFS, statusledpinPath, statusledpin.c_str());            // Write file to save value
          }
          // HTTP POST dhcp value on
          const char* PARAM_INPUT_10 = "buttonpin";                // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_10) {
            buttonpin = p->value().c_str();
            Serial.print("buttonpin set to: ");
            Serial.println(buttonpin);
            writeFile(SPIFFS, buttonpinPath, buttonpin.c_str());            // Write file to save value
          }
          // HTTP POST dhcp value on
          const char* PARAM_INPUT_11 = "ntptime";                // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_11) {
            ntptime = p->value().c_str();
            Serial.print("ntptime set to: ");
            Serial.println(ntptime);
            writeFile(SPIFFS, ntptimePath, ntptime.c_str());            // Write file to save value
          }
          // HTTP POST dhcp value on
          const char* PARAM_INPUT_12 = "ntptimeoffset";                // Search for parameter in HTTP POST request
          if (p->name() == PARAM_INPUT_12) {
            ntptimeoffset = p->value().c_str();
            Serial.print("ntptimeoffset set to: ");
            Serial.println(ntptimeoffset);
            writeFile(SPIFFS, ntptimeoffsetPath, ntptimeoffset.c_str());            // Write file to save value
          }



          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      if (dhcpcheck == "on") {
        ip = "dhcp ip adress";
      }
      request->send(200, "text/html", "<h1>Done. ESP restart,<br> connect router <br>go to: <a href=\"http://" + ip + "\">" + ip + "</a><br><a href=\"http://" + mdnsdotlocalurl + ".local\">http://" + mdnsdotlocalurl + ".local</a> Android use BonjourBrowser App</h1>");
      delay(5000);
      ESP.restart();
    });
    server.begin();
  }
}

unsigned long startmillis = 0;

void loop() {


  if (millis() - startmillis >= 10000) {    // non blocking delay 10 seconds
    startmillis = millis();                 // scan for mdns devices urls every ??? seconds
    browseService("http", "tcp");
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


// next only works/shows its great usefulness if there are more ESP mDNS URL devices on the local network
// scanned mdns url linked list should be on main webpage refreshed every ?? seconds
// for now prints to serial monitor
// https://github.com/ldijkman/Hey_Electra/blob/main/ESP32/ESP32_mDNS_list.ino

String scanstr = "";

void browseService(const char * service, const char * proto) {
  //scanstr += ("Browsing for service _%s._%s.local. ... ", service, proto);
  int n = MDNS.queryService(service, proto);
  scanstr = "";
  if (n == 0) {
    scanstr += "no other Dervices found in local network<br>program more devices with this software<br>and see the power off Electra ;-)<br>\n\r";
  } else {
    scanstr += "\n\r";
    scanstr += n;
    scanstr += " Other Device(s) found on local network";
    scanstr += "\n\r";
    Serial.print(scanstr);
    scanstr = "";
    for (int i = 0; i < n; i++) {
      scanstr += "  ";
      scanstr += i + 1;
      scanstr += ": <a href=\"http://";
      scanstr += MDNS.IP(i).toString();
      scanstr += "\">http://";
      scanstr += MDNS.hostname(i);
      scanstr += ".local</a><br>";
      //scanstr += MDNS.port(i);
      scanstr += "\n\r";
    }
  }
  Serial.print(scanstr);
  scanstr = "";
  
  Serial.print("WiFi.status == ");
  Serial.println(WiFi.status());



  // Got it working???
  // Share a video link https://github.com/ldijkman/Hey_Electra/discussions
  // Bet you can do better as me => https://www.youtube.com/watch?v=mrQwdB_dm_U
  // http://paypal.me/LDijkman
}
