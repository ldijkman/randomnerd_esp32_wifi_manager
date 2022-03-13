// hello
// https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft
// https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat
// http://www.Arduino.TK
//
// https://m.facebook.com/groups/2643123052617990
// https://www.facebook.com/groups/esp32smartthermostat
//
// *****************************************************************************
// GNU General Public License,
// which basically means that you may freely copy, change, and distribute it,
// but you may not impose any restrictions on further distribution,
// and you must make the source code available.
// *****************************************************************************
//
// i have treid this program on various ESP32 38-Pin devices
// 38-Pin ESP32 WROOM 32   (one had a reset switch that does not work)
// 38-Pin ESP32 WROOM 32D
// 38-Pin ESP32 WROOM 32U  (External antenne)
// 38-Pin ESP32 WROVER     (one had a blob off solder (near G22) connecting two pins of ESP32Chip wich prevented programming)
//
// probably will also work on 30-32 pin ESP32 Devices
//
// on first startup the screen is for 10 to 20 seconds snowy / blank (a format message now)
// think its formatting the filesystem during that time
//
// TFT white screen / blank screen
// make sure u set the file
// ......................../arduino/libraries/TFT_eSPI/User_Setup.h
// Correct to match your TFT screen driver and hardware
//
// my example User_Setup.h settings at http://Arduino.TK
//
//
//
//

//
//
//
//
//
//
//
//
//
//
//

//********************************************************************************
// 21 december 2020 switched to BME280 temp, mbar, humid, sensor == much better
//********************************************************************************

// ART ESP32 Thermostat by luberth dijkman
// https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft
// https://create.arduino.cc/editor/luberth/becc77e8-4000-4673-9412-dbaac0a3b268/preview

// https://www.youtube.com/user/LuberthDijkman

// https://m.facebook.com/luberth.dijkman

// 320x240 screen or bigger but then the display is 320x240
// under construction
//
// https://youtu.be/CM0h_ad7ETU by Fabio Mastrotto, He got me into this trouble


// ART ESP32Thermostat by luberth dijkman
// https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft


// under construction
// Thank you for the Coffee!
//           https://paypal.me/LDijkman
 #include <ArduinoJson.h>
#include<EEPROM.h>
#include <WiFi.h>
#include <WebServer.h>
WebServer server(80);
#include <HTTPClient.h>   //http get 
#include <ESPmDNS.h> 


#include <WiFiClient.h>
// some say do not use spaces in broadcasted wifi router name
const char* ssid     = "Bangert_30_Andijk";  // wifi router name broadcasted in the air by your wifi router
const char* password = "ookikwilerin";          // your wifi router password


#include <NTPClient.h>               // Include NTPClient library          https://github.com/arduino-libraries/NTPClient     sketch include lib install from zip
#include <TimeLib.h>                 // Include Arduino time library       https://github.com/PaulStoffregen/Time             sketch include lib install from zip
WiFiUDP ntpUDP;

//#include <moonPhase.h>              // http://github.com/CelliesProjects/moonPhase-esp32   download zip, and install library from zip

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
byte NTP_Offset = 2;                                                                                // NTP time offset in hours + or -
//NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", NTP_Offset * 60 * 60, 24 * 60 * 60 * 1000);   // offset in seconds, 24 hour update
NTPClient timeClient(ntpUDP, "time.google.com", NTP_Offset * 60 * 60, 24 * 60 * 60 * 1000);       // offset in seconds, 24 hour update
//NTPClient timeClient(ntpUDP, "time.nist.gov", NTP_Offset * 60 * 60, 24 * 60 * 60 * 1000);           // offset in seconds, 24 hour update
int last_second = 0, second_ = 0, minute_ = 0, hour_ = 0, day_ = 0, month_ = 0, year_ = 0;          // some variables for NTP time
unsigned long unix_epoch;


#include "FS.h"                 // i guess File System
#include <SPI.h>                // i guess Serial Peripheral Interface
#include <TFT_eSPI.h>           // Hardware-specific TFT SPI library https://github.com/Bodmer/TFT_eSPI
TFT_eSPI tft = TFT_eSPI();      // Invoke custom TFT library

// The SPIFFS (FLASH filing system) is used to hold touch screen calibration data
// This is the file name used to store the calibration data file, name must start with "/".
#define CALIBRATION_FILE "/TouchCalData"

//#define FORMAT_SPIFFS_IF_FAILED 0

// Set REPEAT_CAL to true instead of false or 1 or 0 to run calibration
byte REPEAT_CAL = 0;     // repeat call flag for calibration

byte drawgreendot = 1;  // draw touch position with a greendot


// IMPORTANTE!
// set to 0 if RTClock is programmed and program arduino again with this set to 0
byte Force_DateTimeRewrite = 0;  // if 1 write time and date to DS3231 RTClock // 1= each reboot will set the time and date of first program loading
// you can set time and date on tft now

#include <Wire.h>

#define I2C_SDA 33    // Gpio 33 non standard i2c adress
#define I2C_SCL 32    // Gpio 32 non standard i2c adress  

#include "RTClib.h" // https://github.com/adafruit/RTClib
RTC_DS3231 rtc;    // download zip from above and install library from zip
// Sketch=>include library=>Add ZIP Library

#include <Adafruit_Sensor.h>  // used zip from https://github.com/adafruit/Adafruit_Sensor 
#include <Adafruit_BME280.h>  // used zip from https://github.com/adafruit/Adafruit_BME280_Library
// Sketch=>include library=>Add ZIP Library
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 BME280; // I2C
bool BME280_status;

const int ledPin = 17;            // corresponds to GPIO17 PWM for backlight brightness
// connect to LED of SPI TFT display
// setting PWM properties
const int freq = 4000;           // hz
const int ledChannel = 0;        // think channel 0 is in use by buzzer
const int resolution = 8;        // 8 bit = 0 to 255

byte backgroundlightval = 127;      // not below 5 and upto to 255 backlight brightness better not totaly black
byte nightbackgroundlightval = 10;

// Color definitions
#define BLACK       0x0000
#define BLUE        0x001F
#define RED         0xF800
#define GREEN       0x07E0
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define GRAY        0xBE18
#define DARKGREY    0x4208
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F

#define dutchorange 0xfbc0
#define iceblue     0x1dfb
// pitty you can not enter a colorcode on next page RGB565 colours: https://chrishewett.com/blog/true-rgb565-colour-picker/
unsigned long templong; 
unsigned long TempLong;           // some variables for storing millis
unsigned long touchtime;
unsigned long runTime;
unsigned long runTime2;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

const int heat_relais_pin = 26;          // Gpio 26 relais Heat for control central heating
const int cool_relais_pin = 25;         //  Gpio 25 relais Cool for aico / fan

float TempCelsius = 20;

byte HeatState = 0;
byte CoolState = 0;

// name "mode" should be changed its colored orange allready used by Arduino or library?
// changed name "mode" to "modus"
byte modus = 1;              // start with eco modus that is safest
byte oldmodus;

double decrement_step = 0.1;     // steps for + and - button
double temp_setpoint = 20;

double normal_setpoint = 21;    // save our planet
double auto_setpoint = 20;     // save our planet
double eco_setpoint = 15;     // save our planet
double cool_setpoint = 25;   // save our planet

int time_in_minutes;

float CalibrationOffset = 0.0;  // correction for actual temperature +or-
float switchbelowset = 0.2;     // switch point below
float switchaboveset = 0.2;     // switch poit above

// some things for sleepless nights
// float lowtempalarm = 5;
// float hightempalarm = 35;
// int timetosetpointtolong = 30; // min
// int timeheatontolong = 60;     // minutes
// int minumumheatontime = 4;     // minutes can imagine if not getting hot condesation corrosion
// int maximumheatontime = 60;    // desired temperature not reached within .. minutes


int oldminute;
int X;

const char *monthName[12] = {"Januari", "Februari", "March", "April", "May", "Juni",
                             "Juli", "Augustus", "September", "October", "November", "December"
                            };
char dayname[7][12] = {"Sunday ", "Monday ", "Tuesday ", "Wednesday ", "Thursday ", "Friday ", "Saturday "};

float HeatONhour[20], HeatONminute[20], tempON[20];
float HeatOFFhour[20], HeatOFFminute[20], tempOFF[20];

uint16_t x, y;
uint16_t calibrationData[5];
uint8_t calDataOK = 0;



byte out = 0;                                   // a flag,  goto label: did not work

byte fullscreenactive = 0;                      // flag fullscreen 0 or 1
int secondstoswitchtofullscreen = 20;          // seconds to go fullscreen with barometer and humdity
int bordercolor = dutchorange;

byte DOW;                                     // my week 1=monday 7=sunday = yes = real weekends

byte BlinkState;

// reprogrammed sonoff wifi basic smart switch or esp8266 wemos d1 mini remote light switch
String sonoffaddress[10]={
"http://10.10.100.100", 
"http://10.10.100.102", 
"http://10.10.100.101", 
"http://10.10.100.1", 
"http://10.10.100.1", 
"http://10.10.100.1",
"http://10.10.100.118"
};

int sonoffstatus[10];

String buttontext[15] = {"Sonoff 1","Sonoff 2","Sonoff 3","Sonoff 4","Sonoff 5","Bedroom"};

//String buttontext[1] = "Sonoff 2"; 
//String buttontext[2] = ;
//String buttontext[3] = ;
//String buttontext[4] = ;
//String buttontext[5] = ;
String button7text = "<<";
String button8text = ">>";
String button9text = "edit";
String button10text = "exit";
String button11text = "s";

char q_checkbox[97];

int remotelightoninminutes = 6*60; // 19 hour x minutes Relais_1_on
int remotelightoffinminutes = 22*60+32; // 23 hour x minutes+30 Relais_1_off

bool editsettingsthree=0;


const char* soft_ap_ssid = "ART Thermostat Access Point"; // AP wifi name broadcasted in the air
const char*  soft_ap_password = "";

void setup(void) {

  EEPROM.begin(4096);

  // configure LED PWM functionalitites          // screen brightness background light
  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
  ledcWrite(ledChannel, backgroundlightval);                  // 100 +/- halfbright 0-255 PWM screen brightness background light
  // Jo less energy



  Wire.begin(I2C_SDA, I2C_SCL);                               // start i2c on non stndard i2c pins

  pinMode(heat_relais_pin, OUTPUT);
  pinMode(cool_relais_pin, OUTPUT);
  digitalWrite(heat_relais_pin, HIGH);       // HIGH = heat output relais off
  digitalWrite(cool_relais_pin, HIGH);       // HIGH = cool output relais off


  // times must be from 00:00 to 23:59 following sequence??? maybe left 00:00 if not used

  // 3 on/off switch times a day monday to friday
  //5:30 to 6:30

  HeatONhour[0] = 5, HeatONminute[0] = 30, tempON[0] = 21;
  HeatOFFhour[0] = 6, HeatOFFminute[0] = 30, tempOFF[0] = 14;
  //11:00 to 12:30
  HeatONhour[1] = 11, HeatONminute[1] = 00, tempON[1] = 20;
  HeatOFFhour[1] = 12, HeatOFFminute[1] = 30, tempOFF[1] = 16;
  //16:00 to 23:00
  HeatONhour[2] = 16, HeatONminute[2] = 00, tempON[2] = 20;
  HeatOFFhour[2] = 23, HeatOFFminute[2] = 00, tempOFF[2] = 12;



  // 3 on/off switch times a day saturday to sunday
  //8:00 to 9:00
  HeatONhour[10] = 8, HeatONminute[10] = 00, tempON[10] = 21;
  HeatOFFhour[10] = 9, HeatOFFminute[10] = 00, tempOFF[10] = 14;
  //11:00 to 13:00
  HeatONhour[11] = 11, HeatONminute[11] = 00, tempON[11] = 20;
  HeatOFFhour[11] = 13, HeatOFFminute[11] = 00, tempOFF[11] = 16;
  //15:00 to 23:30
  HeatONhour[12] = 15, HeatONminute[12] = 00, tempON[12] = 20;
  HeatOFFhour[12] = 23, HeatOFFminute[12] = 30, tempOFF[12] = 12;



  Serial.begin(115200);   // serial monitor

  tft.init();             // tft_espi

  tft.setRotation(1);     // TFT SPI setrotation before touch calibration


  tft.fillScreen(TFT_BLACK);                          // Clear the screen
  tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);     // show screen size on bigger display
  tft.setCursor(0, 60);
  tft.setTextColor(LIGHTGREY);  tft.setTextSize(2);
  tft.println("Format FileSystem");                   // if its a new blank chip show a message
  tft.println("10 to 20 seconds?");
  tft.setTextSize(1); tft.setCursor(20, 230);
  tft.println("Made by Luberth Dijkman Andijk The Netherlands");


  touch_calibrate();      // TFT Calibrate the touch screen and retrieve the scaling factors

  tft.fillScreen(TFT_BLACK);                          // Clear the screen
  tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);     // show screen size on bigger display
  tft.setCursor(0, 60);
  tft.setTextColor(LIGHTGREY);  tft.setTextSize(3);
  tft.println("  ART Thermostat");
  tft.println("   The ART of");
  tft.println("   Temperature");
  tft.println("   Controlled");
  tft.setTextSize(1); tft.setCursor(20, 230);
  tft.println("Made by Luberth Dijkman Andijk The Netherlands");

  // 8 second delay with countdown on screen
  TempLong = millis();  // store millis() counter in temporary variable TempLong
  while (1 == 1) {                                    // 1 wil always be 1   so forever
    if ((millis() - TempLong)  > 8000)break;          // after 8 seconds break while loop
    tft.setCursor(155, 200); tft.setTextSize(3);
    tft.setTextColor (LIGHTGREY, BLACK);
    //tft.print(8 - ((millis() - TempLong) / 1000)); tft.print(" ");      // tft print the countdown

    tft.drawRoundRect(8 , 170, 304, 16, 8, GREEN);                                            // illusion progress loadbar outline
    tft.fillRoundRect(10, 172, map((millis() - TempLong), 0, 8000, 10, 300), 12, 5, GREEN);   // illusion progress loadbar
  }


  if (! rtc.begin()) {
    tft.fillScreen(RED);
    tft.setTextColor(YELLOW);  tft.setTextSize(3);
    while (! rtc.begin()) {
      Serial.println("Could not find RTC, i2c DS3231 realtimeclock not found");
      tft.setCursor(0, 30);
      tft.println(" DS3231 RTC & BME280");
      tft.println(" Not Found");
      tft.println(" RTC i2c on pin");
      tft.println(" SDA=G33 SCL=G32");
      tft.println(" VCC=3.3V & GND");
    }
    tft.fillScreen(GREEN);
    tft.setTextColor(BLACK);
    tft.setCursor(0, 80);
    tft.print("  YES found RTC");
    delay(10000);
  }
  tft.setTextColor(LIGHTGREY);

  BME280_status = BME280.begin(0x76);
  if (!BME280_status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    tft.fillScreen(RED); tft.setTextSize(3);
    tft.setCursor(10, 30);
    tft.setTextColor(YELLOW);
    tft.println("BME280 Not Found");
    delay(20000);
  }



  // set the time from PC to DS3231 RTC
  if (rtc.lostPower() || Force_DateTimeRewrite == 1) {   // means OR
    tft.fillScreen(MAROON);
    tft.setCursor(0, 80);
    tft.setTextSize(2);
    tft.print(" RTC Setting xTime/Date");
    tft.setTextSize(3);
    delay(5000);               // 5 seconds delay
    // if you uncomment above if, forcing to program time date
    // then every time you reboot the thermostat
    // time is set to the time when you loaded the program into the arduino
    //
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // This line sets the RTC with an explicit date & time, for example to set
    //           2020 juli 24 20:15:00 you would call:
    //   rtc.adjust(DateTime(2020, 7, 24, 20, 15, 0));
  }


  drawmainscreen();           // jump to tab file drawmainscreen

  tft.print(" ");
  /*draw a grid
    tft.fillRect(1, 1, 4, 4, YELLOW);     // yellow origin xy
    tft.fillRect(316, 236, 4, 4, GREEN);  // green max xy
    //draw gridlines 20x20pixels
    for (int i = 0; i <= 320; i = i + 20) {
    tft.fillRect(i, 1, 1, 319, 0x1111);
    }
    for (int i = 0; i <= 320; i = i + 20) {
    tft.fillRect(1, i, 320, 1, 0x1111);
    }
  */
  tft.setTextColor(GREEN, BLACK);
  tft.setCursor(15, 30);

  WiFi.disconnect();                                                // not needed?

  WiFi.mode(WIFI_AP_STA);                                              // Connect to your wifi
  WiFi.softAP(soft_ap_ssid, soft_ap_password);
  WiFi.begin(ssid, password);                                       // Start the Wi-Fi services
  Serial.println("Connecting to WiFi : " + String(ssid));
  tft.println("Connecting to WiFi : " + String(ssid));


  TempLong = millis();                                              // store millis() counter in variable TempLong

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {             // Wait for WiFi to connect
    tft.setCursor(20, 40);
    tft.print(60 - ((millis() - TempLong) / 1000)); tft.print(" ");
    if ((millis() - TempLong)  > 60000)break;                       // timeout exit if it takes to lomg 60 seconds = nowifi
  }
  Serial.println(" Connected to : " + String(ssid));                // serial print broadcasted router wifi name
  tft.setCursor(15, 30);
  tft.println("                  " + String(ssid) + "     ");        // tft print broadcasted router wifi name
  tft.setCursor(120, 40);
  tft.println(WiFi.localIP());                                      // tft print ip adres

  Serial.println("Use IP address: ");              // IP address assigned to your ESP32
  Serial.println( WiFi.localIP());

  //----------------------------------------------------------------
  server.on("/", handleRoot);               // This displays the main webpage, when you open a client connection browser
  server.on("/temp", handleTEMP);           // To update Temperature called by the function getSensorData
  server.on("/humid", handleHUMID);         // To update Humidity called by the function getSensorData
  server.on("/pressure", handlePRESS);      // To update Pressure called by the function getSensorData
  server.on("/modus", handlemodus);         // To update modus called by the function getSensorData

  server.on("/modus0", handlemodus0);       // To update modus0 called by the function getSensorData
  server.on("/modus1", handlemodus1);       // To update modus1 called by the function getSensorData
  server.on("/modus2", handlemodus2);       // To update modus2 called by the function getSensorData
  server.on("/modus3", handlemodus3);       // To update modus3 called by the function getSensorData
  //----------------------------------------------------------------

  server.begin();                     // Start the webserver

  // timeClient.begin();                 // start NTP?

  delay(2000);



    while (!MDNS.begin("art")) {             // Start the mDNS responder for http://art.local
    Serial.println("Error setting up MDNS responder!");
  }
  Serial.print("mDNS responder started http://");
  Serial.print("art");
  Serial.println(".local");
  
  MDNS.addService("http", "tcp", 80);

}





void loop() {

  DateTime now = rtc.now();  // DS3231 RTC RealTimeClock



  server.handleClient();     // webserver Keep checking for a client connection


  unix_epoch = timeClient.getEpochTime();    // Get Unix epoch time from the NTP server

  second_ = second(unix_epoch);
  if (last_second != second_) {

    if (!timeClient.update()) {                            // NTP time
      Serial.print("problem at line 472 time update ");
    }

    // do next only once each new second
    Serial.print("GetFormattedTime "); Serial.println(timeClient.getFormattedTime());   // NTP

    tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(1);
    tft.setCursor(120, 50);
    tft.println("NTP Time: " + timeClient.getFormattedTime());

    Serial.print("DayOfWeek "); Serial.println(timeClient.getDay());                    // ntp
    Serial.print("seconds since 1-1-1970 "); Serial.println(timeClient.getEpochTime()); // ntp

    Serial.print("hour "); Serial.println(hour(unix_epoch));                            // ntp
    Serial.print("minute "); Serial.println(minute(unix_epoch));                        // ntp
    Serial.print("second "); Serial.println(second(unix_epoch));                        // ntp

    Serial.print("day "); Serial.println(day(unix_epoch));                              // ntp
    Serial.print("month "); Serial.println(month(unix_epoch));                          // ntp
    Serial.print("year "); Serial.println(year(unix_epoch));                            // ntp

    Serial.print("Task running on core ");                                              // am i using only 1 core of dual core ESP32?
    Serial.println(xPortGetCoreID());


   TempCelsius = BME280.readTemperature();                                             // get temp from BME280
    TempCelsius = TempCelsius + CalibrationOffset;

    // Serial.print("Fahrenheit = "); Serial.print(Tf, 1);
    Serial.print(" Celsius = "); Serial.println(TempCelsius, 1);
    // https://www.google.com/search?q=3+fahrenheit+to+celsius


    //tft.setCursor(165, 65);
    tft.setTextColor(LIGHTGREY, BLACK);
    // tft.setTextSize(5);
    // tft.println(TempCelsius, 1); // print actual temperature to the screen
    tft.setTextSize(1);
    tft.drawString(String(TempCelsius, 1), 165, 65, 7); // print actual temperature to the screen


    Serial.print("Temperature = ");
    Serial.print(TempCelsius);
    Serial.println(" *C");
    // Convert temperature to Fahrenheit
    // Serial.print("Temperature = ");
    // Serial.print(1.8 * BME280.readTemperature() + 32);
    // Serial.println(" *F");
    Serial.print("Pressure = ");
 //   Serial.print(BME280.readPressure() / 100.0F);
    Serial.println(" hPa");
    Serial.print("Approx. Altitude = ");
//    Serial.print(BME280.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
    Serial.print("Humidity = ");
//    Serial.print(BME280.readHumidity());
    Serial.println(" %");
    Serial.println();


    tft.setTextSize (2);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.setCursor(30, 100);
    if (now.hour() < 10)tft.print(" ");        // print 01 to 09 as 1 to 9
    tft.print(now.hour());
    tft.print(":");
    if (now.minute() < 10)tft.print("0");      // print 1 to 9 as 01 to 09
    tft.print(now.minute());
    tft.print(":");
    if (now.second() < 10)tft.print("0");      // print 1 to 9 as 01 to 09
    tft.print(now.second());

    tft.setTextSize (1);
    tft.setTextColor (DARKGREY, BLACK);
    tft.setCursor(15, 2);
    tft.print("Day ");
    tft.print(now.dayOfTheWeek());             // prints daynumber of the week, weekend sux, sunday=0, saturday=6
    tft.print(" DOW ");
    tft.print(DOW);                            // prints my DayOfWeek with a real weekend 1=monday ... 6=saturday 7=sunday

    tft.setTextSize (2);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.setCursor(17, 130);
    tft.print(dayname[now.dayOfTheWeek()]);
    tft.print(now.day());
    tft.print(" ");
    tft.print(monthName[now.month() - 1]);
    tft.print("   ");
    //tft.print(now.year());
    //tft.print("  ");


    oldminute = now.minute();

    last_second = second_;

  }  // end last_second not is  second_







  // Jo energy saving Backlight
  if (now.hour() < 8) {
    ledcWrite(ledChannel, 10);
  } else {
    ledcWrite(ledChannel, backgroundlightval);
  }
  if (now.hour() >= 20) {
    ledcWrite(ledChannel, 10);  // dim backround light display if hour >= 22uur            //backgroundlightval);
  }

  if (((millis() - touchtime) / 1000) <= 60) {
    ledcWrite(ledChannel, backgroundlightval);  // if display is touched keep it bright for 60 seconds
  }




  while (! rtc.begin() || rtc.lostPower() == 1) {            // lost RTC DS3231 Realtimeclock
    // Glitch?
    delay(100);
    while (! rtc.begin() || rtc.lostPower() == 1) { // doublecheck try it again
      tft.fillScreen(RED);
      tft.setTextColor(YELLOW);  tft.setTextSize(2);
      delay(200);
      Serial.println("Couldn't find RTC i2c realtimeclock not found");
      tft.setCursor(0, 70);
      tft.println  ("  RTC realtimeclock lost");
      tft.println  (" RTC i2c on SDA SCL 20 21");
      tft.println  ("  or power on RTC lost   ");
      tft.println  ("    ");
      tft.println  ("  ShutDown Heat relais ");
      delay(500);
      tft.fillScreen(BLACK);
      tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);     // show screen size on bigger display
      digitalWrite(heat_relais_pin, LOW);       // heat output off
    }
  }


  // alike arduino blink with no delay        heartbeat not realy needed anymore, because there is seconds display now
  currentMillis = millis();
  if (currentMillis - previousMillis >= 500) {  // half second on off
    previousMillis = currentMillis;
    if (BlinkState == 0) {
      tft.setTextColor(RED, BLACK);
      BlinkState = 1;
    } else {
      tft.setTextColor( BLACK, BLACK);
      BlinkState = 0;
    }
    tft.setTextSize(1);
    tft.setCursor(310, 3);
    tft.println("o");              // tft.println(char(3));     // heart symbol           // Alive HEARTBEAT
  }



  if (millis() - runTime >= 1000) {                         // Execute every 1000ms

    runTime = millis();                                     // store millis() counter in variable runtime



    
    if (now.hour() * 60 + now.minute() == (remotelightoninminutes) && now.second() <= 10 ) {
      HTTPClient http;
      http.begin(sonoffaddress[0] + "/on"); //Specify the URL
      int httpCode = http.GET();                                                  //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }

      else {
        Serial.println("Error on HTTP request");
      }

      http.end(); //Free the resources
    }
    if (now.hour() * 60 + now.minute()  == (remotelightoffinminutes) && now.second() <= 10 ) {
      HTTPClient http;
      http.begin(sonoffaddress[0] + "/off"); //Specify the URL
      int httpCode = http.GET();                                                  //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }

      else {
        Serial.println("Error on HTTP request");
      }

      http.end(); //Free the resources
    }











//////////////////////////////////////////////////////////////////////////////
  
    
    IPAddress serverIp = MDNS.queryHost("kitchen");
    Serial.print("IP address of server: ");
    Serial.println(serverIp.toString());

      HTTPClient http;
      http.begin("http://"+serverIp.toString()+"/LED=ON"); //Specify the URL
      int httpCode = http.GET();                                                  //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }

      else {
        Serial.println("Error on HTTP request");
      }

      http.end(); //Free the resources





/////////////////////////////////////////////////////////////////////////









    server.handleClient();                                  // Keep checking for a client connection

    time_in_minutes = (now.hour() * 60 + now.minute());     //time to minutes makes it easier to switch on a time


    //test hardcoded switch on day / time array
    // stupid start the week with sunday => no more weekends
    // in The Netherlands the week starts with monday, we have weekends

    // lets make real weekends
    DOW = now.dayOfTheWeek();           // sux 0=sunday  saturday=6   = only saturday weekend, that sux
    if (DOW == 0) DOW = 7;              // make sunday = 0 to sunday = 7    = yes = real weekends

    // monday to friday
    if (DOW >= 1 && DOW <= 5  ) {      // 1=monday to 5=friday
      Serial.println("it is a weekday");

      // timeinminutes is more easy to work switch with versus hours:minutes
      // timeinseconds is not needed minutes is accurate enough
      // 24x60=1440 minutes a day

      for (X = 0; X <= 2; X++) {
        //Serial.println(X);
        if (time_in_minutes >= HeatOFFhour[X] * 60 + HeatOFFminute[X] ) {
          auto_setpoint = tempOFF[X];
        }
        if (time_in_minutes >= HeatONhour[X] * 60 + HeatONminute[X] && time_in_minutes < HeatOFFhour[X] * 60 + HeatOFFminute[X]) {
          auto_setpoint = tempON[X];
          goto JumpOver;           // programmers do not like GOTO, i liked gwbasic ;-)
        }

      }
    }// end weekday >=1 && <=5 mon...fri



    // saturday sunday;
    // stupid start the week with sunday => no more weekends
    // in The Netherlands the week starts with monday, we have weekends


    if (DOW == 6 || DOW == 7) {      // 6=saturday 7=sunday;
      Serial.println("hieperdepiep hoera weekend");

      // timeinminutes is more easy to work switch with versus hours:minutes
      // timeinseconds is not needed minutes is accurate enough
      // 24x60=1440 minutes a day

      for (X = 10; X <= 12; X++) { // <= smaller or equal, x++ means x=x+1
        //Serial.println(X);
        if (time_in_minutes >= HeatOFFhour[X] * 60 + HeatOFFminute[X] ) {
          auto_setpoint = tempOFF[X];
        }
        if (time_in_minutes >= HeatONhour[X] * 60 + HeatONminute[X] && time_in_minutes < HeatOFFhour[X] * 60 + HeatOFFminute[X]) {
          auto_setpoint = tempON[X];
          goto JumpOver;           // programmers do not like GOTO, i liked gwbasic ;-)
        }
      }

    }// end DOW 6 || 7 sat sun






JumpOver:
    Serial.println("i just jumped over");
    redraw_modus_button();


    OUTSUB();


  } // end Execute every 1000ms=1second








  tft.setTextColor (DARKGREY, BLACK);
  tft.setTextSize(1);
  tft.setCursor(250, 2);
  tft.print(((millis() - touchtime) / 1000));                              // last touch secondstoswitchtofullscreen seconds ago, go fullscreen
  if ((millis() - touchtime) / 1000 < 2)tft.print("        ");             // erase old countertext after reset counter
  if ((fullscreenactive == 0) && (((millis() - touchtime) / 1000) >= secondstoswitchtofullscreen)) {
    fullscreenactive = 1;                                                         // show fullscreen with milibar and humidity
    oldmodus = modus;                                                             // if modus changes online redraw buttons
    tft.fillRoundRect(5, 155, 310, 80, 1, BLACK);                                 // erase  buttons for fullscreen barometer en humidity text

  }




  if (tft.getTouch(&x, &y)) {
    touchtime = millis();         // store touch time millis() for future screen aninmation if touch is longer as ?? time ago


    //print touch xy position to serial monitor
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
    tft.setCursor(140 , 2);
    tft.print("X="); tft.print(x); tft.print("  ");
    tft.setCursor(180, 2);
    tft.print("Y="); tft.print(y); tft.print("  ");
    if (drawgreendot)tft.drawPixel(x, y, GREEN);


    // press on mainscreen / top of screen opens settings menu
    if (x > 0 && x < 320 && y > 0 && y < 140) {
      settings_three_screen();    // open settings menu
      fullscreenactive = 0;
      drawmainscreen();         // restore main screen

    }

    if (fullscreenactive == 1) {
      // touch in bottomscreen makes buttons visible and active
      if (x > 0 && x < 320 && y > 165 && y < 240) {
        fullscreenactive = 0;                                        // show fullscreen with milibar and humidity
        delay(250);                                                  // better should be wait for touchrelease
        x = 0; y = 0;                                                // otherwise it could be seen as a button press
        tft.fillRoundRect(5, 155, 310, 80, 1, BLACK);                // erase old barometer and humidity text
      }
    }

    if (fullscreenactive == 0) {                                       // if not fullscreen touch buttons should not react to touch when in fullscreen

      // modus touch button
      if (x > 100 && x < 200 && y > 165 && y < 240) {

        modus = modus + 1;             // if mode button is touched switch to next mode
        if (modus > 3)modus = 0;       // 0=normal 1=eco 2=auto 3=Cool




        if (modus == 0) { // nomal continu modus at comfort temperature

          tft.fillRoundRect(117, 162, 86, 66, 12, BLACK); // erase old button text
          tft.setCursor(130, 173);
          tft.setTextColor(LIGHTGREY);  tft.setTextSize(2);
          tft.println("NORMAL");
          tft.setCursor(130, 200);
          tft.println("modus");

          tft.setTextSize(4);
          delay(750);

          OUTSUB();
        }



        if (modus == 1) { // eco  continu modus at goosebumbs temperature

          tft.fillRoundRect(117, 162, 86, 66, 12, BLACK); // erase old button text
          tft.setCursor(144, 173);
          tft.setTextColor(GREEN);  tft.setTextSize(2);
          tft.println("ECO");
          tft.setCursor(130, 200);
          tft.println("modus");

          tft.setTextSize(4);
          delay(750);

          OUTSUB();
        }


        if (modus == 2) {  // 2=automodus switch temperature by time program

          tft.fillRoundRect(117, 162, 86, 66, 12, BLACK); // erase old button text
          tft.setCursor(135, 173);
          tft.setTextColor(dutchorange);  tft.setTextSize(2);
          tft.println("AUTO");
          tft.setCursor(130, 200);
          tft.println("modus");

          tft.setTextSize(4);
          delay(750);

          OUTSUB();
        }


        if (modus == 3) {  // 3=cool modus airco modus

          tft.fillRoundRect(117, 162, 86, 66, 12, BLACK); // erase old button text
          tft.setCursor(135, 173);
          tft.setTextColor(iceblue);  tft.setTextSize(2);
          tft.println("COOL");
          tft.setCursor(130, 200);
          tft.println("modus");

          tft.setTextSize(4);
          delay(750);

          OUTSUB();
        }
      }




      // - touch button
      if (x > 0 && x < 90 && y > 165 && y < 240) {

        // 0=normal 1=eco 2=auto 3=Cool
        tft.setTextSize(4);                                       // 0=normal 1=eco 2=auto 3=Cool
        tft.setCursor(35, 65);
        if (modus == 0) {                                         // normal
          normal_setpoint = (normal_setpoint - decrement_step);
          if (normal_setpoint < 10)normal_setpoint = 10;
          tft.setTextColor(LIGHTGREY, BLACK);
          tft.print(normal_setpoint, 1);
        }
        if (modus == 1) {                                         // eco
          eco_setpoint = (eco_setpoint - decrement_step);
          if (eco_setpoint < 10)eco_setpoint = 10;
          tft.setTextColor(GREEN, BLACK);
          tft.print(eco_setpoint, 1);
        }
        if (modus == 2) {                                         // auto
          auto_setpoint = (auto_setpoint - decrement_step);       // does not work in automode because it wil pop back to programmed value
          if (auto_setpoint < 10)auto_setpoint = 10;
          tft.setTextColor(dutchorange, BLACK);
          tft.print(auto_setpoint, 1);
        }
        if (modus == 3) {                                         // cool
          cool_setpoint = (cool_setpoint - decrement_step);
          if (cool_setpoint < 10)cool_setpoint = 10;
          tft.setTextColor(iceblue, BLACK);
          tft.print(cool_setpoint, 1);
        }

        delay(50);

      }



      // + touch button
      if (x > 220 && x < 320 && y > 165 && y < 240) {

        tft.setTextSize(4);                                        // 0=normal 1=eco 2=auto 3=Cool
        tft.setCursor(35, 65);
        if (modus == 0) {                                         // normal
          normal_setpoint = (normal_setpoint + decrement_step);
          if (normal_setpoint > 30)normal_setpoint = 30;
          tft.setTextColor(LIGHTGREY, BLACK);
          tft.print(normal_setpoint, 1);
        }
        if (modus == 1) {                                         // eco
          eco_setpoint = (eco_setpoint + decrement_step);
          if (eco_setpoint > 30)eco_setpoint = 30;
          tft.setTextColor(GREEN, BLACK);
          tft.print(eco_setpoint, 1);
        }
        if (modus == 2) {                                         // auto
          auto_setpoint = (auto_setpoint + decrement_step);       // does not work in automode because it wil pop back to programmed value
          if (auto_setpoint > 30)auto_setpoint = 30;
          tft.setTextColor(dutchorange, BLACK);
          tft.print(auto_setpoint, 1);
        }
        if (modus == 3) {                                         // cool
          cool_setpoint = (cool_setpoint  + decrement_step);
          if (cool_setpoint > 30)cool_setpoint = 30;
          tft.setTextColor(iceblue, BLACK);
          tft.print(cool_setpoint, 1);
        }

        delay(50);

      }
    }           // end if not fullscreen touch buttons should not react to touch when in fullscreen
  }             // end if (tft.getTouch(&x, &y))

}               // end loop






void OUTSUB() {
  runTime2 = millis();


  // 0=normal 1=eco 2=auto 3=Cool
  if (modus == 0) {                                         // normal
    CoolState = 0;
    if (TempCelsius > (normal_setpoint + switchaboveset))HeatState = 0;
    if (TempCelsius < (normal_setpoint - switchbelowset))HeatState = 1;
  }
  if (modus == 1) {                                         // eco
    CoolState = 0;
    if (TempCelsius > (eco_setpoint + switchaboveset))HeatState = 0;
    if (TempCelsius < (eco_setpoint - switchbelowset))HeatState = 1;
  }
  if (modus == 2) {                                         // auto
    CoolState = 0;
    if (TempCelsius > (auto_setpoint + switchaboveset))HeatState = 0;
    if (TempCelsius < (auto_setpoint - switchbelowset))HeatState = 1;
  }
  if (modus == 3) {                                          // cool
    HeatState = 0;
    if (TempCelsius > (cool_setpoint + switchaboveset)) CoolState = 1;
    if (TempCelsius < (cool_setpoint - switchbelowset)) CoolState = 0;
  }







  if (HeatState == 0 ) {

    if (!fullscreenactive) {
      tft.drawRoundRect(10, 10, 300, 140, 8, BLUE);
    }
    if (fullscreenactive) {
      tft.drawRoundRect(10, 10, 300, 220, 8, BLUE);
    }
    tft.setTextSize (1);
    tft.setTextColor (BLUE, BLACK);
    tft.setCursor(130, 13);
    tft.print("  ");
    tft.print(rtc.getTemperature());
    tft.print(char(247)); // C degree sign
    tft.print(" C  ");

    digitalWrite(heat_relais_pin, HIGH);       // HIGH = heat output relais off
  }



  if (HeatState == 1 ) {
    bordercolor = dutchorange;

    if (!fullscreenactive) {
      tft.drawRoundRect(10, 10, 300, 140, 8, bordercolor);
    }
    if (fullscreenactive) {
      tft.drawRoundRect(10, 10, 300, 220, 8, bordercolor);
    }
    tft.setTextSize (1);
    tft.setTextColor (dutchorange, BLACK);
    tft.setCursor(130, 13);
    tft.print("  ");
    tft.print(rtc.getTemperature());
    tft.print(char(247)); // C degree sign
    tft.print(" C  ");

    digitalWrite(heat_relais_pin, LOW);          // LOW = heat output relais on
  }

  if (CoolState == 0 ) {
    if (modus == 3) {

      if (!fullscreenactive) {
        tft.drawRoundRect(10, 10, 300, 140, 8, BLUE);
      }
      if (fullscreenactive) {
        tft.drawRoundRect(10, 10, 300, 220, 8, BLUE);
      }
      tft.setTextSize (1);
      tft.setTextColor (iceblue, BLACK);
      tft.setCursor(130, 13);
      tft.print("  ");
      tft.print(rtc.getTemperature());
      tft.print(char(247)); // C degree sign
      tft.print(" C  ");
    }
    digitalWrite(cool_relais_pin, HIGH);          // HIGH = airco / fan output relais off
  }

  if (CoolState == 1 ) {
    if (modus == 3) {

      if (!fullscreenactive) {
        tft.drawRoundRect(10, 10, 300, 140, 8, iceblue);
      }
      if (fullscreenactive) {
        tft.drawRoundRect(10, 10, 300, 220, 8, iceblue);
      }
      tft.setTextSize (1);
      tft.setTextColor (iceblue, BLACK);
      tft.setCursor(130, 13);
      tft.print("  ");
      tft.print(rtc.getTemperature());
      tft.print(char(247)); // C degree sign
      tft.print(" C  ");

      digitalWrite(cool_relais_pin, LOW);          // LOW = airco / fan output relais on
    }
  }




}             // end outsub













void waitfortouchanywhere() {
  // DONE => should be a timeout for return on this "forever" while loop
  //          TempLong = millis();  //reset innactive time counter (store count)
  //          if ((millis() - TempLong)  > 20000)break;
  // for safety i will turn off the heat now
  // digitalWrite(heat_relais_pin, LOW);       // heat output off
  TempLong = millis();  // store millis() counter in variable TempLong



  while (1 == 1) {                  // 1 wil always be 1   so forever
    if (tft.getTouch(&x, &y)) break; // touch anywhere on the screen to break while loop
    // pinMode(XM, OUTPUT);
    // pinMode(YP, OUTPUT);


    if ((millis() - TempLong)  > 20000)break; // compare stored TempLong to current millis() counter
    // after 20 seconds inactivetie timer break while loop timeout
    tft.setCursor(0, 200);
    tft.setTextColor (RED);
    tft.print(" Touch to Continue, or ");
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.print(20 - ((millis() - TempLong) / 1000)); tft.print(" ");
  }
  delay(200);

}







void timeout() {

  TempLong = millis();  // store millis() counter in variable TempLong

  while (1 == 1) {                  // 1 wil always be 1   so forever



    if ((millis() - TempLong)  > 60000)break; // compare stored TempLong to current millis() counter
    // after 20 seconds inactivetie timer break while loop timeout
    tft.setCursor(290, 200);

    tft.setTextColor (LIGHTGREY, BLACK);
    tft.print(60 - ((millis() - TempLong) / 1000)); tft.print(" ");
  }
  delay(200);

}

void readFile(fs::FS & fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return;
  }

  Serial.println("- read from file:");
  while (file.available()) {
    file.read();
  }
}







// The End == NO!
// for Copy/Paste people
// This is not realy The End
// There are TAB files


// No time 2 sleep, Please let me sleep.
// https://youtu.be/XzO9jGPtrhc


// Thank you for the Coffee!
//           https://www.paypal.me/LDijkman

//bye
