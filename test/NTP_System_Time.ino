// https://gist.github.com/Tech500/bc4bd77a357b8d401cd13487ef6de800
// https://github.com/ldijkman/randomnerd_esp32_wifi_manager/tree/main/test
//
//  NTP_System_Time.ino
//schufti  --of ESP8266.com Forum provided source for NTP time.
//Developer of code not given

#include <WiFi.h>
#include <WiFiUdp.h>
#include <sys/time.h>                                                                                    
#include <time.h>

/*
  Found this reference on setting TZ: http://www.gnu.org/software/libc/manual/html_node/TZ-Variable.html
  Here are some example TZ values, including the appropriate Daylight Saving Time and its dates of applicability. 
  In North American Eastern Standard Time (EST) and Eastern Daylight Time (EDT), the normal offset from UTC is 5 hours; 
  since this is west of the prime meridian, the sign is positive. Summer time begins on March's second Sunday at 
  2:00am, and ends on November's first Sunday at 2:00am.
  
*/

#define TZ "EST+5EDT,M3.2.0/2,M11.1.0/2"

//****************************************************************************
/*
  Need an event scheduler?  "if" conditional statements can be used to schedule events; place in void loop(), for example:
  getDateTime();  
  
  if((HOUR % 1 == 0) && (MINUTE == 0) && (SECOND == 0))  //Event 1
  {
    delay(1000);//wait for next second
    Serial.println("This event occurs every hour on the hour.");
  }
  if((MINUTE % 15 == 0) && (SECOND == 0))  //Event 2
  {
    delay(1000);  //wait for next second
    
    Serial.println("This event occurs every 15 minutes and 0 seconds")
  }
  if((MINUTE % 1== 0) && (SECOND == 0))  //Event 3
  {
    delay(1000);  //wait for next second
    
    Serial.println("This event occurs every 1 minute and 0 seconds");  
  }
  
  //DOW = 0 Sunday
  //DOW  0-6   HOUR 0-23  MINUTE 0-59   SECOND 0-59
  if((DOW == 0) && (HOUR == 0) && (MINUTE == 0) && (SECOND == 0))  //Event 4
  { 
    delay(1000);
    
    Serial.println("Event 4 occurs every Sunday");
  }
  
  "%" Arithmetic operator reference:  https://www.arduino.cc/reference/en/language/structure/arithmetic-operators/remainder/
*/ 

//****************************************************************************

// Replace with your network details
const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

//setting the addresses
IPAddress ip(10, 0, 0, 6);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

WiFiClient client;

///Are we currently connected?
boolean connected = false;

WiFiUDP udp;
// local port to listen for UDP packets
//Settings pertain to NTP time servers
const int udpPort = 1337;
//NTP Time Servers
const char * udpAddress1 = "us.pool.ntp.org";
const char * udpAddress2 = "time.nist.gov";
char incomingPacket[255];
char replyPacket[] = "Hi there! Got the message :-)";

int DOW, MONTH, DATE, YEAR, HOUR, MINUTE, SECOND;
//String = (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
String weekDay;

int lc = 0;
time_t tnow;

char strftime_buf[64];

String dtStamp(strftime_buf);

void setup(void)
{
  Serial.begin(115200);

  while (!Serial);

  WiFi.persistent( false ); // for time saving

  // Connecting to local WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.begin(ssid, password);
  delay(10);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nWiFi connected");
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("Server IP:  ");
  Serial.println(WiFi.localIP());

  //set up TimeZone in local environment
  configTime(0, 0, udpAddress1, udpAddress2);
  setenv("TZ", "EST+5EDT,M3.2.0/2,M11.1.0/2", 3);   // this sets TZ to Indianapolis, Indiana
  tzset();

  Serial.print("wait for first valid timestamp ");

  while (time(nullptr) < 100000ul)
  {
    Serial.print(".");
    delay(5000);
  }
  
  Serial.println(" time synced");
  Serial.println("");

}

void loop()
{

  //udp only send data when connected
  if (connected)
  {
    //Send a packet
    udp.beginPacket(udpAddress1, udpPort);
    udp.printf("Seconds since boot: %u", millis() / 1000);
    udp.endPacket();
  }

  getDateTime();

  if((HOUR % 1 == 0) && (MINUTE == 0) && (SECOND == 0))  //Event 1
  {

    delay(1000);//wait for next second

    Serial.println("Event 1 occurs every hour on the hour."); 

    //Code to do something...  

  }

  if((MINUTE % 15 == 0) && (SECOND == 0))  //Event 2
  {

    delay(1000);  //wait for next second
    
    Serial.println("Event 2 occurs every 15 minutes and 0 seconds"); 

    //Code to do something...  

  }

  if((MINUTE % 1== 0) && (SECOND == 0))  //Event 3
  {

    delay(1000);  //wait for next second
    
    Serial.println("Event 3 occurs every 1 minute and 0 seconds"); 

    //Code to do something... 

  }
  
  //DOW = 0 Sunday
  //DOW  0-6   HOUR 0-23  MINUTE 0-59   SECOND 0-59
  if((DOW == 0) && (HOUR == 0) && (MINUTE == 0) && (SECOND == 0))  //Event 4
  { 

    delay(1000);
    
    Serial.println("Event 4 occurs every Sunday");
    
    //Code to do something... 

  }

  getDateTime();

  Serial.println(dtStamp);

  delay(1000);

}

String getDateTime()
{
  struct tm *ti;

  tnow = time(nullptr) + 1;
  ti = localtime(&tnow);
  DOW = ti->tm_wday;
  YEAR = ti->tm_year + 1900;
  MONTH = ti->tm_mon + 1;
  DATE = ti->tm_mday;
  HOUR  = ti->tm_hour;
  MINUTE  = ti->tm_min;
  SECOND = ti->tm_sec;

  strftime(strftime_buf, sizeof(strftime_buf), "%a , %m/%d/%Y , %H:%M:%S %Z", localtime(&tnow));
  dtStamp = strftime_buf;
  return (dtStamp);

}
// https://gist.github.com/Tech500/bc4bd77a357b8d401cd13487ef6de800
// https://github.com/ldijkman/randomnerd_esp32_wifi_manager/tree/main/test
