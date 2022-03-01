control your local devices from touch screens (also)

mDNS scan for devices in local network

create buttons from mDNS data

use url/on url/off for on / off

use url/status for button color

each tft touch can also be a relais switch that joins/shares in the mdns devices in the local network
 
 https://www.youtube.com/watch?v=3qviv5TOcVo
 
<img src="https://user-images.githubusercontent.com/45427770/153990182-4e595ad1-138c-45d6-97d7-112c2c0ade88.png">

 https://www.youtube.com/watch?v=3qviv5TOcVo


=====================

BIT of code from that tft lcd program to get the status of a switch

```````````````````````````````
esp32


      HTTPClient http;

      http.begin(sonoffaddress[1] + "/value");                            // Specify the URL
      //Serial.println(sonoffaddress[i] + "/value");
      http.setConnectTimeout(100);
      int httpCode = http.GET();                                         // Make the request
      sonoffstatus[1] = 2;                                               // if not changed status is 2 = error
      if (httpCode > 0) {                                                // Check for the returning code

        String payload = http.getString();
        payload.trim();                                        // trim the white space off the string:  other wise the 0 or 1 compare does not work
        //Serial.println(httpCode);
        Serial.print("payload >"); Serial.print(payload); Serial.print("<"); Serial.println("-");
        if (payload == "0") {
          sonoffstatus[1] = 0;
        }
        if (payload == "1") {
          sonoffstatus[1] = 1;
        }

        payload = "-";

      }
      else {
        Serial.println("Error on HTTP request");

      }

      http.end(); //Free the resources
      
```
'''
"""
---
/```
```````````````````````````````


-
