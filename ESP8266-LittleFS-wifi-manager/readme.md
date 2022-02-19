
make sure u use LittleFS data upload, NOT SPIFFS

https://github.com/ldijkman/randomnerd_esp32_wifi_manager/tree/main/LittleFS_Data_Upload

---

the LAN mDNS scan linked list could be better if it asks the status of the other devices

and show a yellow or gray link button depnding on status

and maybe link to /on /off to switch from other device

like i did on this TFT LCD display https://www.youtube.com/watch?v=3qviv5TOcVo

future? you could place ESP TFT touch displays anywhere in your house that automaticly scan for mDNS and lists it on the buttons<br>

![2022-02-15-045728_1360x768_scrot](https://user-images.githubusercontent.com/45427770/153990182-4e595ad1-138c-45d6-97d7-112c2c0ade88.png)

future? you could place ESP TFT touch displays anywhere in your house that automaticly scan for mDNS and lists it on the buttons<br>

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
      
      
      ``````````````````````````````````````````
