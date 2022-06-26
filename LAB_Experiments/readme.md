## BrainStorm

## drag drop HTML elements even touch on phone 
- next is nice http://sortablejs.github.io/Sortable/#grid
- maybe nice for ordering div iframes

Platformio visual studio
- https://m1cr0lab-esp32.github.io/remote-control-with-websocket/platformio-ide/
- - trying platformio https://github.com/ldijkman/Electra_ESP32 


---

With a little HTML knowledge or Guts, you can change the looks of Electra's Switch webpages
- Easy, each device has its own web/cloud editor

---


garage.local/button.html 
- shows automatic mdns scan 
- - iframed other swithes in the local network 
- - for view control 
- - and text link to the switchpages
- future will be on main page of each switch page automatic mdnsscan to show,control,link other swithes in network in an iframe
- - all html / script so end user can play with it with ace js cloud editor (not like an app with no edit)

https://www.youtube.com/shorts/rXHRWjgCcls

https://youtube.com/shorts/WvGHbuReKzs?feature=share

https://youtube.com/shorts/alNpCHc8wV4?feature=share

https://youtube.com/shorts/IJEgNqhAxaU?feature=share


## Imagene imageButton 
- => http:// mdns_name or IP /button.html     (processor %???% code for/and button.html added to the ESP32 Version)

# button.html
https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/LAB_Experiments/button.html

```
<!-- HTML Javascript button.html -->
<!-- each wifi relais switch has a button.html -->
<!-- for showing wifi relais status and control it by image button -->

<!-- u can load it in an iframe on other webpage in the local netwok like used in framed.html -->

<!-- %MDNSNAME% is processed on webserver upload ad filled in with a variable -->
<!-- always use the %percent sign in pairs, like i have to put another not to break the processor / html code % -->
<!-- thats tricky when % is used in style or other elements % -->
```

![2022-06-25-043356_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175755061-8548368c-9d7e-4f13-9516-50c0f48be436.png)

---


### SO HANDY, the ACE js web cloud editor, 
### for editing the html webserver HTML files on the ESP devices

# IFRAME code to use on other pages
- change the src="http:// ??? /button.html" url link to yours / for android better use IP number links
- - https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/LAB_Experiments/button.html
- 
```

<iframe id="inlineFrameExample"
    title="Inline Frame Example"
    width="120"
    height="150"
    src="http://garage.local/button.html"
    style="border:none; -ms-transform: scale(0.5, 0.5); transform: scale(0.5, 0.5)">
</iframe>


```
could place a bulb on each auto scanned discovered mdns url / each switch device in local network

view and control other switches


## Google Please make mDNS work on Android?
- looks like Google obays to Electra's pleas ;-)
- https://www.androidpolice.com/android-mdns-local-hostname/

use ip numbers button html links for adroid?

---

# framed.html
https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/LAB_Experiments/framed.html

```
 <!-- HTML Javascript listens for a json wesocket ip's and url name -->
 <!-- and shows a iframe of a remote image button.html -->
 <!-- for showing other wifi relais status and control it  -->

 <!-- %MDNSNAME% is processed on webserver upload ad filled in with a variable -->
 <!-- always use the %percent sign in pairs, like i have to put another not to break the processor / html code % -->
 <!-- thats tricky when % is used in style or other elements % -->
```

![2022-06-25-071533_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175759539-f0389bb0-c6b2-462f-b958-6936870b601b.png)

---

## add mDNS wifi relais devices and they automaticly appear in the scanned mDNS list 

---

![2022-06-25-071909_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175759503-5dff943a-b0aa-46cb-b581-cc5c48b2bd54.png)



---

Scanning for available WiFi Networks
```
//First request will return 0 results unless you start scan from somewhere else (loop/setup)
//Do not request more often than 3-5 seconds
server.on("/scan", HTTP_GET, [](AsyncWebServerRequest *request){
  String json = "[";
  int n = WiFi.scanComplete();
  if(n == -2){
    WiFi.scanNetworks(true);
  } else if(n){
    for (int i = 0; i < n; ++i){
      if(i) json += ",";
      json += "{";
      json += "\"rssi\":"+String(WiFi.RSSI(i));
      json += ",\"ssid\":\""+WiFi.SSID(i)+"\"";
      json += ",\"bssid\":\""+WiFi.BSSIDstr(i)+"\"";
      json += ",\"channel\":"+String(WiFi.channel(i));
      json += ",\"secure\":"+String(WiFi.encryptionType(i));
      //////json += ",\"hidden\":"+String(WiFi.isHidden(i)?"true":"false");
      json += "}";
    }
    WiFi.scanDelete();
    if(WiFi.scanComplete() == -2){
      WiFi.scanNetworks(true);
    }
  }
  json += "]";
  request->send(200, "application/json", json);
  json = String();
});
```
![2022-06-25-051605_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175756151-f91e6607-4a5a-4d05-a1de-a271ec58efe6.png)

---

# Timed switching
### Each wifi relais its own schedule webpage
# Easy to Set & Overview switch times
### https://ldijkman.github.io/Electra/schedule.html
### https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/LAB_Experiments/schedule.html

![2022-06-25-073621_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175759905-9d23a332-9426-4aaa-b31b-28b407465df0.png)

## https://ldijkman.github.io/Electra/schedule.html


# yes got a monday time in minutes websocket

websocket.send(JSON.stringify({'monday': convertH2M(fruits[0])+","+convertH2M(fruits[1])+","+convertH2M(fruits[2])+","+convertH2M(fruits[3])+","+convertH2M(fruits[4])+","+convertH2M(fruits[5])}));

makes socket json send on, off, on, off, on, off,  and  time in minutes  

{"monday":"0,600,660,780,1147,1396"}

next gets wich slider  from wicch.id

websocket.send(JSON.stringify({times :wich.id+","+ convertH2M(fruits[0])+","+convertH2M(fruits[1])+","+convertH2M(fruits[2])+","+convertH2M(fruits[3])+","+convertH2M(fruits[4])+","+convertH2M(fruits[5])}));

- {"times":"monday,214,470,609,780,1140,1380"}
- {"times":"tuesday,60,646,1080,1140,1260,1410"}
- {"times":"wednesday,8,360,960,1080,1200,1365"}	
- etcetera
- {"times":"everyday,157,360,960,1080,1200,1365"}	
- {"times":"weekdays,211,360,960,1080,1200,1365"}
- {"times":"weekends,202,360,960,1080,1200,1365"}	
- {"times":"userdefined,208,360,960,1080,1200,1365"}

esp32 void handleWebSocketMessage( 
- Serial.print(serializeJsonPretty(json, Serial));
- result in serial monitor
```
{
 "times": "wednesday,300,504,960,1080,1200,1365"
}
```   
![2022-06-25-111126_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175766689-68990cc0-fc7a-4ffc-9742-3fc6f0f1914c.png)

## Chromium inspect Network WS (websocket) (show only send)
## json websockets send wich day and day checkbox enabled or not

![2022-06-26-071316_1920x1080_scrot](https://user-images.githubusercontent.com/45427770/175800392-bdb07501-bb47-4670-9c36-451e2f3d5b24.png)

# want red marker on each time slider showing actual NTP time from ESP wifi relais switch

# All You Need is Electra!

https://ldijkman.github.io/Electra
