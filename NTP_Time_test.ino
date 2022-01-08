
//https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/
//https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/

// http://www.cplusplus.com/reference/ctime/strftime/

#include <WiFi.h>
#include "time.h"
/*
 * Area HostName
Worldwide pool.ntp.org
Asia  asia.pool.ntp.org
Europe  europe.pool.ntp.org
North America north-america.pool.ntp.org
Oceania oceania.pool.ntp.org
South America south-america.pool.ntp.org
*/

 */
const char* ssid       = "Bangert-30-Andijk";
const char* password   = "ikwilerin";

const char* ntpServer = "time.google.com";
const long  gmtOffset_sec = 3600;     //sec
const int   daylightOffset_sec = 3600; //sec

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");  // Saturday, January 08 2022 10:23:37
                                                       //http://www.cplusplus.com/reference/ctime/strftime/

}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
