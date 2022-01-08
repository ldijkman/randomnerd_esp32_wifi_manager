#include <WiFi.h>

const char* ssid = "Bangert-30-Andijk";
const char* password =  "ikwilerin";





void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting...");
  }

  Serial.println("Connected with success");

/*
Worldwide  pool.ntp.org
Asia  asia.pool.ntp.org
Europe  europe.pool.ntp.org
North America north-america.pool.ntp.org
Oceania oceania.pool.ntp.org
South America south-america.pool.ntp.org
*/  
 // const char* ntpServer = "time.google.com";
  const char* ntpServer = "europe.pool.ntp.org";
  configTime(0, 3600, ntpServer);
}




void loop()
{
  printTime();
  delay(1000);
}















void printTime() {

  struct tm time;

  if (!getLocalTime(&time)) {
    Serial.println("Could not obtain time info");
    return;
  }

  Serial.println("\n");

  String curdate = tsaz(time.tm_mday) + "/" +  tsaz(time.tm_mon) + "/" +  tsaz(time.tm_year + 1900);
  Serial.println(curdate); 
  
  String curtime = tsaz(time.tm_hour) + ":" +  tsaz(time.tm_min) + ":" +  tsaz(time.tm_sec);
  Serial.println(curtime); 
}


String tsaz(int data)  // to string add zero
{
  String st = "";
  if (data < 10)
  {
    st = "0" + String(data);
  }
  else
  {
    st = String(data);
  }
  return st;
}























