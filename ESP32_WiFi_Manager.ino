/*********
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
  started with the example from
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-wi-fi-manager-asyncwebserver/
  you need to upload the data directory to spiffs => Arduino IDE => Tools => ESP32 Sketch Data Upload (turn serial monitor off else failure)
    howto add to Arduino IDE and use spiffs upload tool  https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
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
*********/

// https://github.com/ldijkman/Hey_Electra/blob/main/ESP32/RandomNerd/ESP32_WiFi_Manager.ino

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>            // https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncTCP.h>                     // https://github.com/me-no-dev/AsyncTCP
#include "SPIFFS.h"
#include <ESPmDNS.h>
//#include <NoDelay.h>                   // nonblocking delay https://www.arduino.cc/reference/en/libraries/nodelay/
#include <AsyncElegantOTA.h>             // https://github.com/ayushsharma82/AsyncElegantOTA

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


// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";
const char* subnetPath = "/subnet.txt";
const char* mdnsPath = "/mdns.txt";
const char* relaispinPath = "/relaispin.txt";
const char* dhcpcheckPath = "/dhcpcheck.txt";

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
const int ledPin = 5;    // wemos uno sized esp32 board
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
String processor(const String& var) {
  if (var == "STATE") {
    if (digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return ledState;
    return String();
  }
  else if (var == "MDNSNAME") {
    return String(mdnsdotlocalurl);
  }
  return String();
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  initSPIFFS();

  // Set GPIO 2 as an OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

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
      request->send(200, "text/txt", str);
    });

    AsyncElegantOTA.begin(&server);    // Start ElegantOTA
    server.begin();
  }
  else {
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

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



          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      request->send(200, "text/html", "<h1>Done. ESP restart,<br> connect router <br>go to: " + ip + " <br><a href=\"http://" + mdnsdotlocalurl + ".local\">http://" + mdnsdotlocalurl + ".local</a> Android use BonjourBrowser App</h1>");
      delay(3000);
      ESP.restart();
    });
    server.begin();
  }
}

unsigned long startmillis = 0;

void loop() {

  /*
    if (millis() - startmillis >= 10000) {    // non blocking delay 10 seconds
      startmillis = millis();
      browseService("http", "tcp");
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

void browseService(const char * service, const char * proto) {
  Serial.printf("Browsing for service _%s._%s.local. ... ", service, proto);
  int n = MDNS.queryService(service, proto);
  if (n == 0) {
    Serial.println("no services found");
  } else {
    Serial.print(n);
    Serial.println(" service(s) found");
    for (int i = 0; i < n; ++i) {
      // Print details for each service found
      Serial.print("  ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(MDNS.hostname(i));
      Serial.print(" (");
      Serial.print(MDNS.IP(i));
      Serial.print(":");
      Serial.print(MDNS.port(i));
      Serial.println(")");
    }
  }
  Serial.println();


  // got it working???
  // share a video link https://github.com/ldijkman/Hey_Electra/discussions
  // http://paypal.me/LDijkman
}
