/*
esp32 
Electra maybe a bitch to get it compiled
used esp board manager setting < 2
modifeid tjpeg decoder h in arduino libraries so that littlefs for esp32 works example tab file
tft espi arduino libs user setup h used as example tab file

install binaries from browser 
https://ldijkman.github.io/Electra/

 not all working
 it is a mesh

 help me make it better / clean it up?
 at the moment i am directeur hoofd programming, hardware design, website designer ugh, publisher, video editor, photoshopper, head promotion / advertising, catering 
 research, development, test and debug, etcetera etcetera
*/

// openweathermap copy paste mesh
// playing with a 4inch ST7796_DRIVER 320x480 screen == sorry i go for 480x320
// having some problems rebooting every time == looks like it is solved
// Bodmer says heap and stack collision, hmmm, maybe i need to do a cleanup on variables defined how and where
// i do not understand this all
// https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram
// if you are a better programmer as me == let me know what to change???
// to optimose memory / stack use
//
//***********************************************
// want to make a screen2.txt file for a second screen
// with more lightbulbs locations
// for example
// http://garden.local/on /off /status    iconchoice maybe raindrops images for garden watering
// http://bedroom.local/on /off /status
// http://kitchen.local/on /off /status
//
// so that the enduser can edit the text file with webeditor Ace js  http:// ip /edit
// and so edit the lightswitch screen on tft touch
// so not hardcoded but enduser editable touch screen
//******************************************************

// Electra Touch == with tft touch screen designed for 320x240 - 480x320 pixels
// https://github.com/ldijkman/randomnerd_esp32_wifi_manager/tree/main/ESP8266-TFT_eSPI
/*
  ##################################################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE Arduino TFT_eSPI LIBRARY directory ######
  raspberry pi /home/pi/Arduino/libraries/TFT_eSPI/User_Setup.h
  windows your arduino location
  my settings https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/user_setup.h
  https://github.com/ldijkman/randomnerd_esp32_wifi_manager/tree/main/ESP8266-TFT_eSPI
  ##################################################################################################
*/
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

//#include <time.h>

// Time zone correction library:
// https://github.com/JChristensen/Timezone
#include <Timezone.h>

TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     //Central European Summer Time
TimeChangeRule  CET = {"CET ", Last, Sun, Oct, 3, 60};      //Central European Standard Time
Timezone euCET(CEST, CET);
#define TIMEZONE euCET // See NTP_Time.h tab for other "Zone references", UK, usMT etc
TimeChangeRule *tz1_Code;   // Pointer to the time change rule, use to get the TZ abbrev, e.g. "GMT"

time_t utc = 0;

//#include "Hash.h"         // otherwise error sha1???? websockets


///#define SERIAL_MESSAGES // For serial output weather reports    maybe espSYNCWESERVER DOESNT LIKE IT TO BE LEFT FROM LOOP TO LONG?????????????

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; // I2C

unsigned BME280status;




//#include <ESP8266WiFi.h>

#include <WiFi.h>
//#include <ESPAsyncTCP.h>                  // https://github.com/me-no-dev/ESPAsyncTCP
#include <AsyncTCP.h>
//#include <ESP8266mDNS.h>
#include <ESPmDNS.h>

#include <FS.h>

//#include <LittleFS.h>
#include "LITTLEFS.h"      // unpack in arduino libraries https://github.com/lorol/LITTLEFS/archive/refs/heads/master.zip

//#define MYFS LittleFS
#define MYFS LITTLEFS
#include <SPIFFSEditor.h>

#include <ESPAsyncWebServer.h>
//this one uses a fork from ESPASYNC library
//https://github.com/lorol/ESPAsyncWebServer
//or
//https://github.com/ldijkman/ESPAsyncWebServer

#include <ArduinoJson.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library 
// https://github.com/Bodmer/TFT_eSPI
// download zip and install lib from zip => sketch => include library => add zip library
// https://github.com/Bodmer/TFT_eSPI/archive/refs/heads/master.zip

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library


#define CALIBRATION_FILE "/Touch_Calibrate.txt"
byte REPEAT_CAL = 0;     // repeat call flag for calibration
uint16_t x, y; //touch x y


// Additional functions
#include "GfxUi.h"
// check All_Settings.h for adapting to your needs
#include "All_Settings.h"  // Attached to this sketch // part of config is in config.txt

#include <JSON_Decoder.h> // https://github.com/Bodmer/JSON_Decoder

#include <OpenWeather.h>  // Latest here: https://github.com/Bodmer/OpenWeather

#define AA_FONT_SMALL "fonts/NSBold15" // 15 point Noto sans serif bold
#define AA_FONT_LARGE "fonts/NSBold36" // 36 point Noto sans serif bold

OW_Weather ow;      // Weather forecast library instance

OW_current *current; // Pointers to structs that temporarily holds weather data
OW_hourly  *hourly;  // Not used
OW_daily   *daily;

boolean booted = true;
boolean goreboot = 0;
boolean gocalibrate = 0;

GfxUi ui = GfxUi(&tft); // Jpeg and bmpDraw functions TODO: pull outside of a class

unsigned long lastDownloadUpdate = millis();

/***************************************************************************************
**                          Declare prototypes
***************************************************************************************/
void updateData();
void drawProgress(uint8_t percentage, String text);
void drawTime();
void drawCurrentWeather();
void drawForecast();
void drawForecastDetail(uint16_t x, uint16_t y, uint8_t dayIndex);
const char* getMeteoconIcon(uint16_t id, bool today);
void drawAstronomy();
void drawSeparator(uint16_t y);
void fillSegment(int x, int y, int start_angle, int sub_angle, int r, unsigned int colour);
String strDate(time_t unixTime);
String strTime(time_t unixTime);
void printWeather(void);
int leftOffset(String text, String sub);
int rightOffset(String text, String sub);
int splitIndex(String text);



// Color definitions
#define BLACK       0x0000
#define BLUE        0x001F
//#define RED         0xF800
#define GREEN       0x07E0
//#define CYAN        0x07FF
//#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
//#define NAVY        0x000F
//#define DARKGREEN   0x03E0
//#define DARKCYAN    0x03EF
//#define MAROON      0x7800
//#define PURPLE      0x780F
//#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define GRAY        0xBE18
//#define DARKGREY    0x4208
//#define ORANGE      0xFD20
//#define GREENYELLOW 0xAFE5
//#define PINK        0xF81F

//#define dutchorange 0xfbc0
//#define iceblue     0x1dfb
// pitty you can not enter a colorcode on next page RGB565 colours: https://chrishewett.com/blog/true-rgb565-colour-picker/



WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com");   // do not know how to make this variable yet

//Week Days
String weekDays[7]  = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]   = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

String reboots;         // reboot counter?  maybe char Byte or int better?

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");

//const char* http_username = "";
//const char* http_password = "";  // login for ace js cloudeditor   at /edit was admin / admin

unsigned long startmillis = 0;
unsigned long lamponstart;
unsigned long lampontime; //inching
unsigned long OFFcountdown;
int flag;
float T = 0.0, H = 0.0, P = 0.0;
int lastSecond = 0;
int t ;
int h ;
int p ;
int currentHour ;
int currentMinute ;
int currentSecond ;
struct button {
  int x;
  int y;
  int w;
  int h;
  String t;
  int ox;
  int oy;
};  // mixed types array

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
// https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
const char* ssidPath  PROGMEM = "/ssid.txt";
const char* passPath  PROGMEM = "/pass.txt";
const char* ipPath   PROGMEM = "/ip.txt";
const char* gatewayPath   PROGMEM = "/gateway.txt";
const char* subnetPath   PROGMEM = "/subnet.txt";
const char* mdnsPath   PROGMEM = "/mdns.txt";
const char* dhcpcheckPath   PROGMEM = "/dhcpcheck.txt";
const char* relaispinPath   PROGMEM = "/relaispin.txt";
const char* statusledpinPath   PROGMEM = "/statusledpin.txt";
const char* buttonpinPath   PROGMEM = "/buttonpin.txt";
const char* ntpserverPath   PROGMEM = "/ntpserver.txt";
const char* ntptimeoffsetPath   PROGMEM = "/ntptimeoffset.txt";
const char* offdelayPath   PROGMEM = "/offdelay.txt";

int postsuccesfull = 0;
int notify = 0;

const char* http_username = "";             // empty/no password for ace js web cloud editor
const char* http_password = "";

// next used in /config.txt
String  api_key;
// Set the forecast longitude and latitude to at least 4 decimal places
String latitude;// =  "52.735434"; // 90.0000 to -90.0000 negative for Southern hemisphere
String longitude;// = "5.179017"; // 180.000 to -180.000 negative for West

uint8_t lastMinute = 0;
bool rebooted = 1;
String formattedTime;


String mdnsdotlocalurl ;

IPAddress localIP(0, 0, 0, 0);
IPAddress gatewayIP(0, 0, 0, 0);
IPAddress subnetMask(0, 0, 0, 0);

unsigned long last = 0;
//unsigned long epochTime, unixTime;
struct tm *ptm;
String weekDay;
int monthDay ;
int currentMonth ;
String currentMonthName;
int currentYear;
String currentDate;



// Timer variables
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
//const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds) removed did not work on esp8266 wifi connect crash reboot

String scanstr = "";  // %MDNSSCAN%


// Set LED GPIO
int ledPin = 16;             // wemos uno sized esp32 board  gpio16 is D0
// Stores LED state

String ledState = "OFF";

//https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram
#define SERIAL_BUFFER_SIZE 32  // normal 64



bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
  // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // Return 1 to decode next block
  return 1;
}



// Initialize LittleFS
void initLittleFS() {

  // if (!LittleFS.begin()) {
  if (MYFS.begin()) {

    Serial.println(F("FS mounted"));
  } else {
    Serial.println(F("FS mount fail"));
  }


}

// Read File from LittleFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);
  tft.setCursor(10, 15);
  tft.print(F("Read: ")); tft.print(path); tft.println(F("       "));

  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    Serial.println(F("- fail 2 open file 4 reading"));
    return String();
  }

  String fileContent;
  while (file.available()) {
    fileContent = file.readStringUntil('\n');
    break;
  }
  file.close();
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, "w");
  if (!file) {
    Serial.println(F("- fail 2 open file 4 writing"));
    return;
  }
  if (file.print(message)) {
    Serial.println(F("- file written"));
  } else {//this one uses a fork from ESPASYNC library
    //https://github.com/lorol/ESPAsyncWebServer
    //or
    //https://github.com/ldijkman/ESPAsyncWebServer
    Serial.println(F("- Write failed"));
  }
  file.close();
}





// Initialize WiFi
bool initWiFi() {
  if (ssid == "" /*|| ip == ""*/) {  // no ip // made it DHCP
    Serial.println(F("SSID ?"));
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
      Serial.println(F("STA Fail config"));
      return false;
    }
  }

  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println(F("Connect to WiFi..."));
  tft.println(F("Connect to WiFi. "));

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if (i >= 20) {
      Serial.println(F("Fail connect. in 20sec"));
      tft.println(F("Connect fail 20sec"));
      return false;
    }
    delay(1000);
    Serial.print(i); Serial.print(' ');
    tft.print(i);
    i++;
  }
  delay(500);
  Serial.println("");
  Serial.println(WiFi.localIP());


  if (!MDNS.begin(mdnsdotlocalurl.c_str())) {
    Serial.println(F("Error MDNS responder!"));
    while (1) {
      delay(1000);
    }
  }


  MDNS.addService("http", "tcp", 80);

  Serial.print(F("http://"));
  Serial.print(mdnsdotlocalurl);
  Serial.println(F(".local"));

  tft.println(F(" Connected"));
  tft.println(WiFi.localIP());
  tft.print(mdnsdotlocalurl);
  tft.println(F(".local"));
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
    mystring += "NTP Offset: " + ntptimeoffset + " hour <br>";
    mystring += "Reboots: " + reboots + "<br>";
    return mystring;
  }

  return String();
}









void setup()
{

  Serial.begin(57600);        // Serial port for debugging purposes

  initLittleFS();
  initWebSocket();

  tft.init();
  tft.setRotation(1);

  // this blocks the program if no touch is done == moved it to the webpage
  // touch_calibrate();  // changed it to start calibrate from homepage  http://ip/calibrate so that it does not block the boot if no screen is present

  tft.fillScreen(TFT_BLACK);

  TJpgDec.setJpgScale(1);
  TJpgDec.setCallback(tft_output);
  TJpgDec.setSwapBytes(true); // May need to swap the jpg colour bytes (endianess)
  String imagefile = F("/electra_ohm_law.jpg"); // saves 20 bytes ????
  TJpgDec.drawFsJpg(0, 0, imagefile, MYFS);  // Draw splash screen
  tft.setTextFont(2);
  tft.setTextSize(1);

  tft.setCursor(80, 260);
  tft.setTextColor(YELLOW, TFT_BLACK);
  tft.println(F("Hey Electra"));
  delay(3000);

  tft.fillScreen(TFT_BLACK);






  //draw gridlines 20x20pixels
  for (int i = 0; i <= 480; i = i + 20) {
    tft.drawRect(i, 1, 1, 320, 0x2104); // https://chrishewett.com/blog/true-rgb565-colour-picker/
    delay(100);
  }

  for (int i = 0; i <= 320; i = i + 20) {
    tft.drawRect(1, i, 480, 1, 0x2104); // https://chrishewett.com/blog/true-rgb565-colour-picker/
    delay(100);
  }
  //draw gridlines 20x20pixels

  tft.drawRoundRect(1, 1, 319, 239, 2, 0x5AEB); // screen size outline
  tft.drawRoundRect(1, 1, 479, 319, 2, TFT_GREEN); // screen size outline

  tft.setCursor(15, 100);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println(F("edit the file config.txt"));
  tft.println(F("openweathermap api key and location"));
  tft.println(F("with online ace js cloudeditor http://ip or mdns/edit"));
  tft.println("");
  tft.println(F("Start a Calibrate Touch from WebPage"));



  tft.setTextColor(BLUE , TFT_BLACK);
  tft.setCursor(tft.width() - 75, tft.height() - 25);
  tft.println(F("== Help! =="));
  tft.setTextColor(YELLOW, TFT_BLACK);
  tft.setCursor(tft.width() - 75, tft.height() - 15);
  tft.println(F("= Ukraine ="));

  tft.setCursor(20, 0);

  //for (int i = 0; i <= 255; i++) {
  //  tft.print(char(i));
  // }
  //delay(20000);

  tft.setTextFont(2);
  tft.setTextSize(1);


  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println(F("Touch Electra, Electra Touch"));

  tft.setCursor(10, tft.height() - 20);
  tft.print(tft.width()); tft.print("x"); tft.println(tft.height());

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

  String configtxt = F("/config.txt"); // saves 12 bytes ???
  if (MYFS.exists(configtxt) == true) {          // config.txt holds openweathermap api key en lat long location
    File file = MYFS.open(configtxt, "r");
    delay(100);
    api_key = file.readStringUntil('\n');
    latitude = file.readStringUntil('\n');
    longitude = file.readStringUntil('\n');
    file.close();

    Serial.print(F("config.txt api key ")); Serial.println(api_key);
    Serial.print(F("Lat = ")); Serial.println(latitude);
    Serial.print(F("Lon = ")); Serial.println(longitude);
    Serial.println("");
    Serial.println(F("location lat lon from littlefs config.txt"));
    Serial.print(F("https://www.google.com/search?q=")); Serial.print(latitude); Serial.print(","); Serial.println(longitude);
  }

  // reboot counter file
  reboots = readFile(MYFS, "/reboots.txt");
  reboots = (reboots.toInt()) + 1;                  // strings and chars i do not get it, drives me nuts
  writeFile(MYFS, "/reboots.txt", reboots.c_str());
  // reboot counter file


  // Set GPIO ledPin as an OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);





  Serial.println(F("BME280 test"));
  if (ledPin == 4 || ledPin == 5) {   // 4 5 normal i2c pins but used on some boards for relais
    Wire.begin(14, 12);               // use 14 and 12 for i2c on d5 d6
  }
  BME280status = bme.begin(0x76);   // The device's I2C address is either 0x76 or 0x77.
  if (!BME280status) {
    Serial.println(F("No BME280 sensor, check wiring, address, sensor ID!"));
    Serial.print(F("SensorID was: 0x")); Serial.println(bme.sensorID(), 16);
    // while (1)
    //delay(5000);
  }






  if (initWiFi()) {

    events.onConnect([](AsyncEventSourceClient * client) {
      client->send("hello!", NULL, millis(), 1000);
    });
    server.addHandler(&events);

#ifdef ESP32
    server.addHandler(new SPIFFSEditor(MYFS, http_username, http_password));
#elif defined(ESP8266)
    server.addHandler(new SPIFFSEditor(http_username, http_password, MYFS));
#endif

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(MYFS, "/index.html", "text/html", false, processor);
      notify = 1;
    });

        // Route for button.html web page
    server.on("/button.html", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(MYFS, "/button.html", "text/html", false, processor);
      notify = 1;
    });

    //server.serveStatic("/", LittleFS, "/");
    server.serveStatic("/", MYFS, "/").setDefaultFile("/index.htm");

    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
      Relays_ON();
      // digitalWrite(ledPin, HIGH);
      // ledState = "ON";
      request->send(MYFS, "/index.html", "text/html", false, processor);
      notify = 1;
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
      Relays_OFF();
      // digitalWrite(ledPin, LOW);
      // ledState = "OFF";
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
      MYFS.remove("/ssid.txt");
      MYFS.remove("/pass.txt");
      String str = "";
      str += F("<h1>deleted wifi credentials ssid.txt and pass.txt<br>");
      str += F("Done...ESP restart,<br>");
      str += F("connect to AP access point ESP WIFI MANAGER <br>");
      str += F("to configure wifi settings again<br>");
      str += F("<a href=\"http://192.168.4.1\">http://192.168.4.1</a></h1>");
      request->send(200, "text/html", str);
      goreboot = 1;
    });

    //  /reboot
    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest * request) {
      String str = "";
      str += F("<meta http-equiv=\"refresh\" content=\"15; url=http://");
      str += WiFi.localIP().toString();
      str += F("\"><h1>Huh, Reboot Electra, Restart ESP<br><a href=\"http://");
      str += WiFi.localIP().toString();
      str += F("\">http://");
      str += WiFi.localIP().toString();
      str += F("</a></h1>");
      request->send(200, "text/html",  str );
      goreboot = 1;
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
            Serial.print(F("offdelay set to: "));
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
        Serial.println(F("Error mount LittleFS"));
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
      //str += "\r\n";
      //str += F("totalBytes   ");
      //str += LittleFS.totalBytes();
      //str += "\r\n";
      //str += F("usedBytes    ");
      //str += LittleFS.usedBytes();
      //str += "\r\n";
      //str += F("freeBytes??? ");
      //str += LittleFS.totalBytes()-LittleFS.usedBytes();
      //str += "\r\n";
      request->send(200, "text/txt", str);
    });


    server.on("/heap", HTTP_GET, [](AsyncWebServerRequest * request) {
      request->send(200, "text/plain", String(ESP.getFreeHeap()));
    });




    server.on("/calibrate", HTTP_GET, [](AsyncWebServerRequest * request) {
      String str = "";
      str += F("<meta http-equiv=\"refresh\" content=\"15; url=http://");
      str += WiFi.localIP().toString();
      str += F("\"><h1>Huh, Calibrate and then Reboot Electra, Restart ESP<br><a href=\"http://");
      str += WiFi.localIP().toString();
      str += F("\">http://");
      str += WiFi.localIP().toString();
      str += F("</a></h1>");
      request->send(200, "text/html",  str );
      gocalibrate = 1;
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
    String broadcastintheair = String("ESP-WIFI-MANAGER-");// + ESP.getChipId();              // esp8266 want a unique broadcast id for each device

    tft.println(F("connect wifi direct"));
    tft.println(String("ESP-WIFI-MANAGER-"));// + ESP.getChipId());
    tft.println(F("and browse to 192.168.4.1"));

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
  Serial.print(F("ntptimeoffset sec ")); Serial.println(offset);

  NTPClient timeClient(ntpUDP, ntpserver.c_str());   // do not know how to make this variable yet
  Serial.println(ntpserver.c_str());


  timeClient.begin();



}








// loop // // loop // // loop // // loop // // loop // // loop // // loop // // loop // // loop //
void loop() {

  if (millis() - last > 500UL)
  {
    timeClient.update();
    ws.cleanupClients();
    //MDNS.update();   // looks like this is needed only for esp8266 otherwise i dont see mdns url in bonjourbrowser not needed for esp32

    last = millis();
  }

  //Serial.println("namillis");

  if (WiFi.status() == 6) {
    tft.setCursor(20 , 20);
    tft.println(F("connect wifi direct"));
    //tft.println(String("ESP-WIFI-MANAGER-") + ESP.getChipId()); //not ok for esp32
    tft.println(F("and browse to 192.168.4.1"));
    tft.println("");
    tft.println(F("Start a Calibrate Touch from WebPage"));
  }

  //Serial.println("nawifistaus");


  if (goreboot == 1) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(YELLOW, TFT_BLACK);
    tft.setTextFont(1);
    tft.setTextSize(3);
    tft.setCursor(110, 90);
    tft.println(F("Going to Reboot!"));
    delay(5000);
    ESP.restart();
  }
  //Serial.println("nagoreboot");
  if (gocalibrate == 1) {
    gocalibrate = 0;
    REPEAT_CAL = 1;
    touch_calibrate();           // calibrate tft touch screen start from html url
    goreboot = 1;
  }
  //Serial.println("nagocalibrate");


  //is second changed????

  if (timeClient.getSeconds() != lastSecond) {
    lastSecond = timeClient.getSeconds();

    tft.setCursor(300, 0);
    tft.print(timeClient.getFormattedTime());
    tft.setCursor(400, 0);
    tft.print(F("Reboots ")); tft.print(reboots);
    tft.setCursor(300, 20);
    // tft.print("IP: "); tft.print(WiFi.localIP());
    tft.setCursor(300, 35);
    // tft.print(F("Http://")); tft.print(mdnsdotlocalurl); tft.print(F(".local"));


    // https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/

    unsigned long epochTime = timeClient.getEpochTime();


    //unixTime = epochTime;
    //Get a time structure
    tm *ptm = gmtime ((time_t *)&epochTime);
    formattedTime = timeClient.getFormattedTime();
    currentHour = timeClient.getHours();
    currentMinute = timeClient.getMinutes();
    currentSecond = timeClient.getSeconds();
    weekDay = weekDays[timeClient.getDay()];
    monthDay = ptm->tm_mday;
    currentMonth = ptm->tm_mon + 1;
    currentMonthName = months[currentMonth - 1];
    currentYear = ptm->tm_year + 1900;
    currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);

    // Serial.print("Epoch Time: "); Serial.println(epochTime);           // Epoch Time: 164466241
    // Serial.print("Formatted Time: "); Serial.println(formattedTime);  // Formatted Time: 10:40:16
    // Serial.print("Hour: "); Serial.println(currentHour);
    // Serial.print("Minutes: "); Serial.println(currentMinute);
    //  Serial.print("Seconds: "); Serial.println(currentSecond);
    //  Serial.print("Week Day: "); Serial.println(weekDay);
    //  Serial.print("Month day: "); Serial.println(monthDay);
    //  Serial.print("Month: "); Serial.println(currentMonth);
    //  Serial.print("Month name: "); Serial.println(currentMonthName);
    //  Serial.print("Year: "); Serial.println(currentYear);
    // Serial.print("Current date: "); Serial.println(currentDate);









  }
  /*
          Epoch Time: 1651252703
          Formatted Time: 17:18:23
          Hour: 17
          Minutes: 18
          Seconds: 23
          Week Day: Friday
          Month day: 29
          Month: 4
          Month name: April
          Year: 2022
          Current date: 2022-4-29
  */

  // https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/

  /*
      //Serial.print("Temperature = ");
      //Serial.print(bme.readTemperature());
      // Serial.println(" *C");
      // Serial.print("Pressure = ");
      // Serial.print(bme.readPressure() / 100.0F);
      //  Serial.println(" hPa");
      // Serial.print("Approx. Altitude = ");
      // Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
      // Serial.println(" m");
      // Serial.print("Humidity = ");
      // Serial.print(bme.readHumidity());
      // Serial.println(" %");
      // tft.fillRoundRect(135, 110, 50, 10, 0, BLACK);  // erase old text
      tft.setCursor(350, 205);
      if (OFFcountdown < 100)tftprintspace();  // keep print to the right side
      if (OFFcountdown < 10)tftprintspace();  // keep print to the right side
      tft.println(OFFcountdown);
      //openweather
      // Check if we should update weather information
      if (booted)
      {
       // updateData();
       TJpgDec.drawFsJpg(325, 70, "/OFF.jpg", MYFS);
      }
      if (millis() - lastDownloadUpdate > 1000UL * UPDATE_INTERVAL_SECS)
      {
       // updateData();
        lastDownloadUpdate = millis();
      }
      // If minute has changed then request new time from NTP server
      if (booted || timeClient.getMinutes() != lastMinute)
      {
        // Update displayed time first as we may have to wait for a response
        drawTime();
        lastMinute = timeClient.getMinutes();
        // Request and synchronise the local clock
        //syncTime();
        booted = false;
      }
      //openweather
    }
    if (tft.getTouch(&x, &y)) {           //  gets x, y and only print to serial monitor i there is a touch
      //Serial.print(x);                    //  print touch xy position to serial monitor for debug
      //Serial.print(",");
      //Serial.println(y);
      tft.setTextColor(GRAY, BLACK);                    // draw text to tft screen for debug
      tft.setCursor(260 , 305);
      tft.print("X="); tft.print(x); tftprintspace();
      tft.setCursor(340, 305);
      tft.print("Y="); tft.print(y); tftprintspace();
      // i have 320x240 and 480x320 screens, would like to have a gui that scales itself
      // me no programmer, just puzzleing
      tft.setCursor(260 , 285);
      tft.print("X/SW "); tft.print(float(x) / tft.width()); tftprintspace(); // maybe a position for scaling small bigger screen, will be 0 to 1 on width and height
      tft.setCursor(340, 285);                                             // result SW x scaling = position for small and bigger screens
      tft.print("Y/SH "); tft.print(float(y) / tft.height()); tftprintspace(); // maybe a position for scaling small bigger screen
      //tft.drawPixel(x, y, TFT_GREEN);         // draw touch position pixel
    }
    // think this does not make it any easier ;-) but draw and touch can use same parameters
    // well i am no programmer, just playing
    // struct button {
    //   int x;
    //   int y;
    //   int w;
    //   int h;
    //   String t;
    //   int ox;
    //   int oy;
    // };  // mixed types array
    button but1 = {200, 100, 60, 30, "BUTTON", 7, 7};          // topleft x, y, width, height(down from y), buttontext textoffset x, y
    //button same on different screen sizes test
    int sw = tft.width();
    int sh = tft.height();
    button but2 = {200, 100, 60, 30, "BUTTON", 7, 7};//{0.65 * sw, 0.18 * sh, 0.8 * sw - 0.65 * sw, 0.47 * sh - 0.18 * sh, "", 20, 20};       // topleft x, y, width, height(down from y), buttontext textoffset x, y
    button but3 = {200, 100, 60, 30, "BUTTON", 7, 7};//{0.65 * sw, 0.5 * sh, 0.85 * sw - 0.65 * sw, 0.75 * sh - 0.5 * sh, "scaled", 20, 20};
    // drawButton(but1.x, but1.y, but1.w, but1.h, but1.t, but1.ox, but1.oy);
    drawButton(but2.x, but2.y, but2.w, but2.h, but2.t, but2.ox, but2.oy);
    drawButton(but3.x, but3.y, but3.w, but3.h, but3.t, but3.ox, but3.oy);
    if (TouchButton(but1.x, but1.y, but1.w, but1.h)) {
      if (ledState == "OFF") {
        Relays_ON();
        delay(250);
        return;
      }
      if (ledState == "ON") {
        Relays_OFF();
        delay(250);
        return;
      }
    }
    if (TouchButton(but2.x, but2.y, but2.w, but2.h)) {
      if (ledState == "OFF") {
        Relays_ON();
        delay(250);
        return;
      }
      if (ledState == "ON") {
        Relays_OFF();
        delay(250);
        return;
      }
    }
    if (TouchButton(but3.x, but3.y, but3.w, but3.h)) {
      if (ledState == "OFF") {
        Relays_ON();
        delay(250);
        return;
      }
      if (ledState == "ON") {
        Relays_OFF();
        delay(250);
        return;
      }
    }
  */

  lampontime = offdelay.toInt() * 1000;
  if ((millis() - lamponstart)  > lampontime ) { // turn lamp off 2 minutes after start from webbutton     compare stored TempLong to current millis() counter  screen timeout
    Relays_OFF(); // Turn relaispin OFF
  } else {
    OFFcountdown = (lampontime / 1000 - (millis() - lamponstart) / 1000);
    if (ledState == "OFF")OFFcountdown = 0;
    if ((millis() / 500) % 2) {
      // Serial.println("1");
      if (flag == 0) {
        notifyClients();                     // send countdown once every half second
        flag = 1;
      }
    } else {                                 // not half second reset sendonce flag
      // Serial.println("0");
      flag = 0;
    }
  }
  // if ( digitalread hardware_button.pressed()) {
  // while  ( digitalread hardware_button.pressed()) {//bounce}
  // }
  // toggle state
  // notifyClients();
  // }






  if (postsuccesfull == 1) {
    postsuccesfull = 0;
    delay(5000);
    Serial.println(F("Restart"));
    ESP.restart();
  }

  if (notify == 1) {        // switch from url /on / off notifyClients
    notify = 0;
    //delay(100);
    notifyClients();
  }






  if (millis() - startmillis >= 10000UL) {    // non blocking delay 10 seconds
    startmillis = millis();                 // scan for mdns devices urls every ??? seconds

    browseService("http", "tcp");           // scan for other mdns devices urls in local network

    //Serial.print(F("ntpserver ")); Serial.println(ntpserver.c_str());
    //Serial.print(F("ntptimeoffset sec ")); Serial.println((ntptimeoffset.toInt() * 3600));
    Serial.print("Formatted Time: "); Serial.println(formattedTime);  // Formatted Time: 10:40:16
    // Serial.print("Hour: "); Serial.println(currentHour);
    // Serial.print("Minutes: "); Serial.println(currentMinute);
    //  Serial.print("Seconds: "); Serial.println(currentSecond);
    //  Serial.print("Week Day: "); Serial.println(weekDay);
    //  Serial.print("Month day: "); Serial.println(monthDay);
    //  Serial.print("Month: "); Serial.println(currentMonth);
    //  Serial.print("Month name: "); Serial.println(currentMonthName);
    //  Serial.print("Year: "); Serial.println(currentYear);
    Serial.print("Current date: "); Serial.println(currentDate);

    Serial.println(WiFi.localIP());
    Serial.print(mdnsdotlocalurl);
    Serial.println(F(".local"));
    Serial.printf("Total heap: %d\n", ESP.getHeapSize());
    Serial.printf("Free heap: %d\n", ESP.getFreeHeap());
    Serial.printf("Total PSRAM: %d\n", ESP.getPsramSize());
    Serial.printf("Free PSRAM: %d\n", ESP.getFreePsram());

    if (BME280status) {
      t = (bme.readTemperature() * 10);
      h = (bme.readHumidity() * 10);
      p = bme.readPressure() / 100.0F;
      T = (t / 10); // to get 1 decimal place
      H = (h / 10);
      P = p;
    }
  }


  //Serial.println("endloop");
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

















void tftprintspace() {
  tft.print(F(" "));
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
          Serial.print(F("SSID set to: "));
          Serial.println(ssid);
          // Write file to save value
          writeFile(MYFS, ssidPath, ssid.c_str());
        }
        // HTTP POST pass value
        const char* PARAM_INPUT_2 = "pass";                 // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_2) {
          pass = p->value().c_str();
          Serial.print(F("Password set to: "));
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
          Serial.print(F("IP Address set to: "));
          Serial.println(ip);
          writeFile(MYFS, ipPath, ip.c_str());            // Write file to save value
        }
        // HTTP POST gateway value
        const char* PARAM_INPUT_4 = "gateway";              // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_4) {
          gateway = p->value().c_str();
          Serial.print(F("gateway Address set to: "));
          Serial.println(gateway);
          writeFile(MYFS, gatewayPath, gateway.c_str());          // Write file to save value
        }

        // HTTP POST subnet value
        const char* PARAM_INPUT_5 = "subnet";               // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_5) {
          subnet = p->value().c_str();
          Serial.print(F("subnet Address set to: "));
          Serial.println(subnet);
          writeFile(MYFS, subnetPath, subnet.c_str());            // Write file to save value
        }
        // HTTP POST mdns value
        const char* PARAM_INPUT_6 = "mdns";                 // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_6) {
          mdnsdotlocalurl = p->value().c_str();
          Serial.print(F("mdnsdotlocalurl Address set to: "));
          Serial.println(mdnsdotlocalurl);
          writeFile(MYFS, mdnsPath, mdnsdotlocalurl.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_7 = "dhcp";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_7) {
          dhcpcheck = p->value().c_str();
          Serial.print(F("dhcpcheck set to: "));
          Serial.println(dhcpcheck);
          writeFile(MYFS, dhcpcheckPath, dhcpcheck.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_8 = "relaispin";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_8) {
          relaispin = p->value().c_str();
          Serial.print(F("relaispin set to: "));
          Serial.println(relaispin);
          writeFile(MYFS, relaispinPath, relaispin.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_9 = "statusledpin";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_9) {
          statusledpin = p->value().c_str();
          Serial.print(F("statusledpin set to: "));
          Serial.println(statusledpin);
          writeFile(MYFS, statusledpinPath, statusledpin.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_10 = "buttonpin";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_10) {
          buttonpin = p->value().c_str();
          Serial.print(F("buttonpin set to: "));
          Serial.println(buttonpin);
          writeFile(MYFS, buttonpinPath, buttonpin.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_11 = "ntpserver";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_11) {
          ntpserver = p->value().c_str();
          Serial.print(F("ntpserver set to: "));
          Serial.println(ntpserver);
          writeFile(MYFS, ntpserverPath, ntpserver.c_str());            // Write file to save value
        }
        // HTTP POST dhcp value on
        const char* PARAM_INPUT_12 = "ntptimeoffset";                // Search for parameter in HTTP POST request
        if (p->name() == PARAM_INPUT_12) {
          ntptimeoffset = p->value().c_str();
          Serial.print(F("ntptimeoffset set to: "));
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


void Relays_ON() {
  digitalWrite(ledPin, HIGH);
  if (ledState == "ON")return;
  ledState = "ON";
  lamponstart = millis();
  notifyClients();
  TJpgDec.drawFsJpg(325, 70, "/ON.jpg", MYFS);
  return;
}

void Relays_OFF() {
  digitalWrite(ledPin, LOW);
  if (ledState == "OFF")return;
  ledState = "OFF";
  OFFcountdown = 0;
  notifyClients();
  TJpgDec.drawFsJpg(325, 70, "/OFF.jpg", MYFS);
  return;
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
      scanstr += "<p><a href=\"http://";
      scanstr += MDNS.IP(i).toString() + ":";
      scanstr += MDNS.port(i);
      scanstr += "\">";
      scanstr += MDNS.hostname(i);
      scanstr += ".local</a><p>";        // esp32 does it different without.local???
      //scanstr += "</a></p>";           // esp8266 does it different with .local???
    }
  }
  Serial.print(scanstr);
  Serial.println("");
  Serial.println(F("Soon Electra will Power a Gazillion Devices"));
  //  Serial.println("");
  /*
    Serial.print(F("WiFi.status == "));
    Serial.print(WiFi.status());
    Serial.print(": ");
    switch (WiFi.status()) {
      case 0:
        Serial.println(F("WL_IDLE_STATUS"));
        break;
      case 1:
        Serial.println(F("WL_NO_SSID_AVAIL"));
        break;
      case 2:
        Serial.println(F("WL_SCAN_COMPLETED"));
        break;
      case 3:
        Serial.println(F("WL_CONNECTED"));
        break;
      case 4:
        Serial.println(F("WL_CONNECT_FAILED"));
        break;
      case 5:
        Serial.println(F("WL_CONNECTION_LOST"));
        break;
      case 6:
        Serial.println(F("WL_DISCONNECTED"));
        break;
      default:
        // if nothing else matches, do the default
        // default is optional
        Serial.println(F("donotknow"));
        break;
    }
    Serial.println("ok");
  */
  // notifyClients();

}

// ----------------------------------------------------------------------------
// WebSocket initialization
// ----------------------------------------------------------------------------
// copyed code from https://github.com/m1cr0lab-esp32/remote-control-with-websocket
// copyed code from https://github.com/rheinz/remote-control-with-websocket

void notifyClients() {
  const unsigned int size = JSON_OBJECT_SIZE(8);//i do not know
  StaticJsonDocument<size> json;

  json["status"] = ledState.c_str(); // relais status
  json["time"] = formattedTime.c_str();
  json["offdelay"] = offdelay.c_str();
  json["offcnt"] = OFFcountdown;
  json["T"] = T;
  json["H"] = H;
  json["P"] = P;
  json["scan"] = scanstr.c_str();   // mdnsscan


  char buffer[1000];   //i do not know
  size_t len = serializeJson(json, buffer); //print to serial monitor
  ws.textAll(buffer, len);

}


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
      //if (digitalRead(ledPin) == 0) {
      if (ledState == "OFF") {
        Relays_ON();
        //digitalWrite(ledPin, HIGH);
        //ledState = "ON";
      } else {
        Relays_OFF();
        //digitalWrite(ledPin, LOW);
        //ledState = "OFF";
      }
      Serial.println(ledState);
      notifyClients();
    }

    Serial.print(F("off_delay=")); Serial.println(off_delay);
    Serial.print(F("offdelay=")); Serial.println(offdelay);
    if (json["off_delay"]) {
      offdelay  = atoi(off_delay);
      Serial.print(F("off_delay=")); Serial.println(off_delay);
      Serial.print(F("offdelay=")); Serial.println(offdelay);
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
    default:
      Serial.print("Unknown error "); Serial.println(p);
  }
}




void initWebSocket() {
  ws.onEvent(onEvent);
  // ws.onEvent(onWsEvent); // part of fsbrowser example turned off
  server.addHandler(&ws);

}


// Code to run a screen calibration, not needed when calibration values set in setup()
void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;
  Serial.println(F("function calibrate"));

  if (!MYFS.begin()) {
    Serial.println(F("Error mount LittleFS"));
    return;
  }

  if (MYFS.exists(CALIBRATION_FILE)) {  // check if calibration file exists and size is correct
    if (REPEAT_CAL)
    {
      // Delete if we want to re-calibrate
      MYFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = MYFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(1);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(30, 30);
    tft.println(F("Touch corners as indicated"));

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      //tft.println(F("Set REPEAT_CAL to false"));
      //tft.println(F("to stop this running again!"));
    }

    tft.calibrateTouch(calData, TFT_GREEN, TFT_BLACK, 25);

    tft.fillScreen(TFT_BLACK);
    tft.drawRoundRect(1, 1, 479, 319, 2, TFT_DARKGREY);
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setCursor(30, 110);
    tft.println(F("Calibration complete!"));
    delay(4000);
    tft.fillScreen(TFT_BLACK);

    // store data
    File f = MYFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}










void drawButton(int x, int y, int w, int h, String buttontext, int xoffset, int yoffset)
{
  if (ledState == "OFF") {
    tft.drawRoundRect(x, y, w, h, 3, LIGHTGREY); // outter button color
    tft.setTextColor(LIGHTGREY, TFT_BLACK);
  }
  if (ledState == "ON") {
    tft.drawRoundRect(x, y, w, h, 3, GREEN); // outter button color
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  }
  tft.setCursor(x + xoffset, y + yoffset);
  tft.print(buttontext);
}



void freeheap()
{
  Serial.print(F("FreeHeap          "));// Serial.println(ESP.getFreeHeap(), DEC);
  //Serial.print(F("MaxFreeBlockSize  ")); Serial.println(ESP.getMaxFreeBlockSize(), DEC);
  //Serial.print(F("HeapFragmentation ")); Serial.println(ESP.getHeapFragmentation(), DEC);
}


byte TouchButton(int xx, int yy, int ww, int hh)
{
  //tft.getTouch(&x, &y);
  if (x > xx && x < xx + ww && y > yy && y < yy + hh) {
    tft.drawRoundRect(xx, yy, ww, hh, 4, GREEN);                // bit off visual touch
    //tft.drawRoundRect(xx + 1, yy + 1, ww - 2, hh - 2, 4, GREEN); // bit off visual touch
    delay(50);
    tft.drawRoundRect(xx, yy, ww, hh, 4, BLACK);                // bit off visual touch
    //tft.drawRoundRect(xx + 1, yy + 1, ww - 2, hh - 2, 4, BLACK); // bit off visual touch
    delay(50);
    tft.drawRoundRect(xx, yy, ww, hh, 4, WHITE);                // bit off visual touch
    // tft.drawRoundRect(xx + 1, yy + 1, ww - 2, hh - 2, 4, LIGHTGREY); // bit off visual touch
    x = 0;
    y = 0;
    return 1;
  } else {
    return 0;
  }
}





/***************************************************************************************
**                          Fetch the weather data  and update screen
***************************************************************************************/
// Update the Internet based information and update screen
void updateData() {
  // booted = true;  // Test only
  // booted = false; // Test only

  if (booted) drawProgress(20, "Updating time...");
  else fillSegment(22, 22, 0, (int) (20 * 3.6), 16, YELLOW);

  if (booted) drawProgress(50, "Updating conditions...");
  else fillSegment(22, 22, 0, (int) (50 * 3.6), 16, YELLOW);

  // Create the structures that hold the retrieved weather
  current = new OW_current;
  daily =  new  OW_daily;
  //hourly =  new OW_hourly;


  // Serial.print("Lat = "); Serial.print(latitude);
  // Serial.print(", Lon = "); Serial.println(longitude);
  // Serial.println("");
  // Serial.println("location lat lon from littlefs config.txt");
  Serial.print(F("https://www.google.com/search?q=")); Serial.print(latitude); Serial.print(","); Serial.println(longitude);
  //Serial.println("");

  // ESP8266 4MByte 12E 12F
  //bool parsed = ow.getForecast(current, hourly, daily, api_key, latitude, longitude, units, language, true); // looks like this causes reboots with Electra/Bodmer OW combined code
  bool parsed = ow.getForecast(current, hourly, daily, api_key, latitude, longitude, units, language, false); // last parameter == secure was true == looks like no reboots
  // bodmer says heap and stack collision, hmmm, maybe i need to do a cleanup on vaiables defined how and where
  // i do not understand this all
  // https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram



  freeheap();

  //Serial.print("sunrise    : "); Serial.println(strTime(current->sunrise));
  //Serial.print("sunset     : "); Serial.println(strTime(current->sunset));
  //Serial.print("sunrise    : "); Serial.println(current->sunrise);
  //Serial.print("sunset     : "); Serial.println(current->sunset);

  //printWeather(); // For debug, turn on output with #define SERIAL_MESSAGES

  if (booted)
  {
    drawProgress(100, "Done...");
    delay(2000);
    tft.fillScreen(TFT_BLACK);
  }
  else
  {
    fillSegment(22, 22, 0, 360, 16, TFT_NAVY);
    fillSegment(22, 22, 0, 360, 22, TFT_BLACK);
  }

  if (parsed)
  {
    Serial.println(F("Weather received"));
    tft.loadFont(AA_FONT_SMALL, MYFS);
    drawCurrentWeather();
    drawForecast();
    drawAstronomy();
    tft.unloadFont();

    // Update the temperature here so we don't need to keep
    // loading and unloading font which takes time
    tft.loadFont(AA_FONT_LARGE, MYFS);
    tft.setTextDatum(TR_DATUM);
    tft.setTextColor(TFT_YELLOW, TFT_BLACK);

    // Font ASCII code 0xB0 is a degree symbol, but o used instead in small font
    tft.setTextPadding(tft.textWidth(" -88")); // Max width of values

    String weatherText = "";
    weatherText = String(current->temp, 0);  // Make it integer temperature
    tft.drawString(weatherText, 215, 95); //  + "°" symbol is big... use o in small font
    tft.unloadFont();
  }
  else
  {
    Serial.println(F("Failed to get weather"));
  }

  // Delete to free up space
  delete current;
  //delete hourly;
  delete daily;
  freeheap();
}

/***************************************************************************************
**                          Update progress bar
***************************************************************************************/
void drawProgress(uint8_t percentage, String text) {
  tft.loadFont(AA_FONT_SMALL, MYFS);
  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setTextPadding(240);
  tft.drawString(text, 120, 260);

  ui.drawProgressBar(10, 269, 240 - 20, 15, percentage, TFT_WHITE, TFT_BLUE);

  tft.setTextPadding(0);
  tft.unloadFont();
}

/***************************************************************************************
**                          Draw the clock digits
***************************************************************************************/
void drawTime() {
  tft.loadFont(AA_FONT_LARGE, MYFS);

  // Convert UTC to local time, returns zone code in tz1_Code, e.g "GMT"
  //time_t local_time = TIMEZONE.toLocal(now(), &tz1_Code);                // changed timesource

  String timeNow = "";

  if (timeClient.getHours() < 10) timeNow += "0";     // changed timesource
  timeNow += timeClient.getHours();
  timeNow += ":";
  if (timeClient.getMinutes() < 10) timeNow += "0";   // changed timesource
  timeNow += timeClient.getMinutes();

  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextPadding(tft.textWidth(" 44:44 "));  // String width + margin
  tft.drawString(timeNow, 120, 53);

  drawSeparator(51);

  tft.setTextPadding(0);

  tft.unloadFont();
}

/***************************************************************************************
**                          Draw the current weather
***************************************************************************************/
void drawCurrentWeather() {
  String date = "Updated: " + strDate(current->dt);
  String weatherText = "None";

  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  //tft.setTextPadding(tft.textWidth(" Updated: Mmm 44 44:44 "));  // String width + margin
  tft.drawString(date, 120, 16);

  String weatherIcon = "";

  String currentSummary = current->main;
  currentSummary.toLowerCase();

  weatherIcon = getMeteoconIcon(current->id, true);

  //uint32_t dt = millis();
  //ui.drawBmp("/icon/" + weatherIcon + ".bmp", 0, 53);
  TJpgDec.drawFsJpg( 0, 53, "/icon/" + weatherIcon + ".jpg", MYFS);


  //Serial.print("Icon draw time = "); Serial.println(millis()-dt);

  // Weather Text
  if (language == "en")
    weatherText = current->main;
  else
    weatherText = current->description;

  tft.setTextDatum(BR_DATUM);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);

  int splitPoint = 0;
  int xpos = 235;
  splitPoint =  splitIndex(weatherText);

  tft.setTextPadding(xpos - 100);  // xpos - icon width
  if (splitPoint) tft.drawString(weatherText.substring(0, splitPoint), xpos, 69);
  else tft.drawString(" ", xpos, 69);
  tft.drawString(weatherText.substring(splitPoint), xpos, 86);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextDatum(TR_DATUM);
  tft.setTextPadding(0);
  if (units == "metric") tft.drawString("oC", 237, 95);
  else  tft.drawString("oF", 237, 95);

  //Temperature large digits added in updateData() to save swapping font here

  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  weatherText = String(current->wind_speed, 0);

  if (units == "metric") weatherText += " m/s";
  else weatherText += " mph";

  tft.setTextDatum(TC_DATUM);
  tft.setTextPadding(tft.textWidth("888 m/s")); // Max string length?
  tft.drawString(weatherText, 124, 136);

  if (units == "imperial")
  {
    weatherText = current->pressure;
    weatherText += " in";
  }
  else
  {
    weatherText = String(current->pressure, 0);
    weatherText += " hPa";
  }

  tft.setTextDatum(TR_DATUM);
  tft.setTextPadding(tft.textWidth(" 8888hPa")); // Max string length?
  tft.drawString(weatherText, 230, 136);



  int windAngle = (current->wind_deg + 22.5) / 45;
  if (windAngle > 7) windAngle = 0;
  String wind[] = {"N", "NE", "E", "SE", "S", "SW", "W", "NW" };
  tft.drawString(wind[windAngle], 150, 70); //luberth draw wind direction in text == arrow confuse me == going or comming
  //ui.drawBmp("/wind/" + wind[windAngle] + ".bmp", 101, 86);
  TJpgDec.drawFsJpg(  101, 86, "/wind/" + wind[windAngle] + ".jpg", MYFS);

  drawSeparator(153);

  tft.setTextDatum(TL_DATUM); // Reset datum to normal
  tft.setTextPadding(0);      // Reset padding width to none
}

/***************************************************************************************
**                          Draw the 4 forecast columns
***************************************************************************************/
// draws the three forecast columns
void drawForecast() {
  int8_t dayIndex = 1;

  drawForecastDetail(  8, 171, dayIndex++);
  drawForecastDetail( 66, 171, dayIndex++); // was 95
  drawForecastDetail(124, 171, dayIndex++); // was 180
  drawForecastDetail(182, 171, dayIndex  ); // was 180
  drawSeparator(171 + 69);
}

/***************************************************************************************
**                          Draw 1 forecast column at x, y
***************************************************************************************/
// helper for the forecast columns
void drawForecastDetail(uint16_t x, uint16_t y, uint8_t dayIndex) {

  if (dayIndex >= MAX_DAYS) return;

  String day = shortDOW[weekday(TIMEZONE.toLocal(daily->dt[dayIndex], &tz1_Code))];
  day.toUpperCase();

  tft.setTextDatum(BC_DATUM);

  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setTextPadding(tft.textWidth("WWW"));
  tft.drawString(day, x + 25, y);

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextPadding(tft.textWidth("-88   -88"));
  String highTemp = String(daily->temp_max[dayIndex], 0);
  String lowTemp  = String(daily->temp_min[dayIndex], 0);
  tft.drawString(highTemp + " " + lowTemp, x + 25, y + 17);

  String weatherIcon = getMeteoconIcon(daily->id[dayIndex], false);

  //ui.drawBmp("/icon50/" + weatherIcon + ".bmp", x, y + 18);
  TJpgDec.drawFsJpg( x, y + 18, "/icon50/" + weatherIcon + ".jpg", MYFS);

  tft.setTextPadding(0); // Reset padding width to none
}

/***************************************************************************************
**                          Draw Sun rise/set, Moon, cloud cover and humidity
***************************************************************************************/
void drawAstronomy() {

  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextPadding(tft.textWidth(" Last qtr "));


  time_t local_time = TIMEZONE.toLocal(current->dt, &tz1_Code);
  uint16_t y = year(local_time);
  uint8_t  m = month(local_time);
  uint8_t  d = day(local_time);
  uint8_t  h = hour(local_time);


  int      ip;
  uint8_t icon = moon_phase(y, m, d, h, &ip);

  tft.drawString(moonPhase[ip], 120, 319);
  //ui.drawBmp("/moon/moonphase_L" + String(icon) + ".bmp", 120 - 30, 318 - 16 - 60);
  TJpgDec.drawFsJpg( 120 - 30, 318 - 16 - 60, "/moon/moonphase_L" + String(icon) + ".jpg", MYFS);

  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setTextPadding(0); // Reset padding width to none
  tft.drawString(sunStr, 40, 270);

  tft.setTextDatum(BR_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextPadding(tft.textWidth(" 88:88 "));

  String rising = strTime(current->sunrise) + " ";
  int dt = rightOffset(rising, ":"); // Draw relative to colon to them aligned
  tft.drawString(rising, 40 + dt, 290);

  String setting = strTime(current->sunset) + " ";
  dt = rightOffset(setting, ":");
  tft.drawString(setting, 40 + dt, 305);

  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.drawString(cloudStr, 195, 260);

  String cloudCover = "";
  cloudCover += current->clouds;
  cloudCover += "%";

  tft.setTextDatum(BR_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextPadding(tft.textWidth(" 100%"));
  tft.drawString(cloudCover, 210, 277);

  tft.setTextDatum(BC_DATUM);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.drawString(humidityStr, 195, 300 - 2);

  String humidity = "";
  humidity += current->humidity;
  humidity += "%";

  tft.setTextDatum(BR_DATUM);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextPadding(tft.textWidth("100%"));
  tft.drawString(humidity, 210, 315);

  tft.setTextPadding(0); // Reset padding width to none
}

/***************************************************************************************
**                          Get the icon file name from the index number
***************************************************************************************/
const char* getMeteoconIcon(uint16_t id, bool today)
{
  if ( today && id / 100 == 8 && (current->dt < current->sunrise || current->dt > current->sunset)) id += 1000;

  if (id / 100 == 2) return "thunderstorm";
  if (id / 100 == 3) return "drizzle";
  if (id / 100 == 4) return "unknown";
  if (id == 500) return "lightRain";
  else if (id == 511) return "sleet";
  else if (id / 100 == 5) return "rain";
  if (id >= 611 && id <= 616) return "sleet";
  else if (id / 100 == 6) return "snow";
  if (id / 100 == 7) return "fog";
  if (id == 800) return "clear-day";
  if (id == 801) return "partly-cloudy-day";
  if (id == 802) return "cloudy";
  if (id == 803) return "cloudy";
  if (id == 804) return "cloudy";
  if (id == 1800) return "clear-night";
  if (id == 1801) return "partly-cloudy-night";
  if (id == 1802) return "cloudy";
  if (id == 1803) return "cloudy";
  if (id == 1804) return "cloudy";

  return "unknown";
}

/***************************************************************************************
**                          Draw screen section separator line
***************************************************************************************/
// if you don't want separators, comment out the tft-line
void drawSeparator(uint16_t y) {
  tft.drawFastHLine(10, y, 240 - 2 * 10, 0x4228);
}

/***************************************************************************************
**                          Determine place to split a line line
***************************************************************************************/
// determine the "space" split point in a long string
int splitIndex(String text)
{
  uint16_t index = 0;
  while ( (text.indexOf(' ', index) >= 0) && ( index <= text.length() / 2 ) ) {
    index = text.indexOf(' ', index) + 1;
  }
  if (index) index--;
  return index;
}

/***************************************************************************************
**                          Right side offset to a character
***************************************************************************************/
// Calculate coord delta from end of text String to start of sub String contained within that text
// Can be used to vertically right align text so for example a colon ":" in the time value is always
// plotted at same point on the screen irrespective of different proportional character widths,
// could also be used to align decimal points for neat formatting
int rightOffset(String text, String sub)
{
  int index = text.indexOf(sub);
  return tft.textWidth(text.substring(index));
}

/***************************************************************************************
**                          Left side offset to a character
***************************************************************************************/
// Calculate coord delta from start of text String to start of sub String contained within that text
// Can be used to vertically left align text so for example a colon ":" in the time value is always
// plotted at same point on the screen irrespective of different proportional character widths,
// could also be used to align decimal points for neat formatting
int leftOffset(String text, String sub)
{
  int index = text.indexOf(sub);
  return tft.textWidth(text.substring(0, index));
}

/***************************************************************************************
**                          Draw circle segment
***************************************************************************************/
// Draw a segment of a circle, centred on x,y with defined start_angle and subtended sub_angle
// Angles are defined in a clockwise direction with 0 at top
// Segment has radius r and it is plotted in defined colour
// Can be used for pie charts etc, in this sketch it is used for wind direction
#define DEG2RAD 0.0174532925 // Degrees to Radians conversion factor
#define INC 2 // Minimum segment subtended angle and plotting angle increment (in degrees)
void fillSegment(int x, int y, int start_angle, int sub_angle, int r, unsigned int colour)
{
  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x1 = sx * r + x;
  uint16_t y1 = sy * r + y;

  // Draw colour blocks every INC degrees
  for (int i = start_angle; i < start_angle + sub_angle; i += INC) {

    // Calculate pair of coordinates for segment end
    int x2 = cos((i + 1 - 90) * DEG2RAD) * r + x;
    int y2 = sin((i + 1 - 90) * DEG2RAD) * r + y;

    tft.fillTriangle(x1, y1, x2, y2, x, y, colour);

    // Copy segment end to segment start for next segment
    x1 = x2;
    y1 = y2;
  }
}

/***************************************************************************************
**                          Print the weather info to the Serial Monitor
***************************************************************************************/
void printWeather(void)
{

#ifdef SERIAL_MESSAGES
  Serial.println("Weather from OpenWeather\n");

  Serial.println("Current weather\n");
  Serial.print("dt (time)  : "); Serial.println(strDate(current->dt));
  Serial.print("sunrise    : "); Serial.println(strDate(current->sunrise));
  Serial.print("sunset     : "); Serial.println(strDate(current->sunset));
  Serial.print("main       : "); Serial.println(current->main);
  Serial.print("temp       : "); Serial.println(current->temp);
  Serial.print("humidity   : "); Serial.println(current->humidity);
  Serial.print("pressure   : "); Serial.println(current->pressure);
  Serial.print("wind_speed : "); Serial.println(current->wind_speed);
  Serial.print("wind_deg   : "); Serial.println(current->wind_deg);
  Serial.print("clouds     : "); Serial.println(current->clouds);
  Serial.print("id         : "); Serial.println(current->id);
  Serial.println();

  Serial.println("Daily weather\n");
  Serial.println();

  for (int i = 0; i < 5; i++)
  {
    Serial.print("dt (time) : "); Serial.println(strDate(daily->dt[i]));
    Serial.print("id        : "); Serial.println(daily->id[i]);
    Serial.print("temp_max  : "); Serial.println(daily->temp_max[i]);
    Serial.print("temp_min  : "); Serial.println(daily->temp_min[i]);
    Serial.println();
  }

#endif
}
/***************************************************************************************
**             Convert Unix time to a "local time" time string "12:34"
***************************************************************************************/
String strTime(time_t unixTime)
{
  time_t local_time = TIMEZONE.toLocal(unixTime, &tz1_Code);

  String localTime = "";

  if (hour(local_time) < 10) localTime += "0";
  localTime += hour(local_time);
  localTime += ":";
  if (minute(local_time) < 10) localTime += "0";
  localTime += minute(local_time);

  return localTime;
}



/***************************************************************************************
**  Convert Unix time to a local date + time string "Oct 16 17:18", ends with newline
***************************************************************************************/
/*String strDate(time_t unixTime)
  {
  //time_t local_time = TIMEZONE.toLocal(unixTime, &tz1_Code);
  //Get a time structure
  unsigned long epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime ((time_t *)&epochTime);
  String localDate = "";
   localDate += ptm->tm_mon + 1;
   localDate += " ";
   localDate += ptm->tm_mday;
   localDate += " " + strTime(unixTime);
  return localDate;
  }
*/
/***************************************************************************************
**  Convert Unix time to a local date + time string "Oct 16 17:18", ends with newline
***************************************************************************************/
String strDate(time_t unixTime)
{
  time_t local_time = TIMEZONE.toLocal(unixTime, &tz1_Code);

  String localDate = "";

  localDate += monthShortStr(month(local_time));
  localDate += " ";
  localDate += day(local_time);
  localDate += " " + strTime(unixTime);

  return localDate;
}

/**The MIT License (MIT)
  Copyright (c) 2015 by Daniel Eichhorn
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
  AUTHORS OR COPYBR_DATUM HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
  See more at http://blog.squix.ch
*/

//  Changes made by Bodmer:

//  Minor changes to text placement and auto-blanking out old text with background colour padding
//  Moon phase text added (not provided by OpenWeather)
//  Forecast text lines are automatically split onto two lines at a central space (some are long!)
//  Time is printed with colons aligned to tidy display
//  Min and max forecast temperatures spaced out
//  New smart splash startup screen and updated progress messages
//  Display does not need to be blanked between updates
//  Icons nudged about slightly to add wind direction + speed
//  Barometric pressure added

//  Adapted to use the OpenWeather library: https://github.com/Bodmer/OpenWeather
//  Moon phase/rise/set (not provided by OpenWeather) replace with  and cloud cover humidity
//  Created and added new 100x100 and 50x50 pixel weather icons, these are in the
//  sketch data folder, press Ctrl+K to view
//  Add moon icons, eliminate all downloads of icons (may lose server!)
//  Adapted to use anti-aliased fonts, tweaked coords
//  Added forecast for 4th day
//  Added cloud cover and humidity in lieu of Moon rise/set
//  Adapted to be compatible with ESP32


//*************************************************************************
//
// https://github.com/ldijkman/OpenWeather
// https://github.com/ldijkman/randomnerd_esp32_wifi_manager/tree/main/ESP8266-TFT_eSPI
// https://ldijkman.github.io/randomnerd_esp32_wifi_manager/Touch_Electra-Electra_Touch/
//
//  4 electa read some settings from /data littlefs /config.txt
// so that you can change it in future from ace js inbrowser cloud web editor
// so that it can/will become part of electra touch tft browser install ESP8266 4mbyte ESP12E ESP12F
// luberth
//************************************************************************




//luberth => turned off  part from fs browser example

/*
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
// i don't wanna stop until Electra reaches the top
