Touch friendly visual timeslot scheduler for timed on/off switching?

view index.html live

https://ldijkman.github.io/randomnerd_esp32_wifi_manager/mrs/create_from_scratch/index.html

---


video served from ESP32 ace editor websockets

https://youtu.be/17K2TtYPI_A


![visual-scheduler](https://github.com/ldijkman/randomnerd_esp32_wifi_manager/assets/45427770/8d5c3759-62eb-47bd-a3eb-2dfc7969ff97)


---

esp32 espasyncwebserver ace editor create (copy/paste from plnkr or codepen) to timeslot.html

![2023-08-19-152535_1920x1080_scrot](https://github.com/ldijkman/randomnerd_esp32_wifi_manager/assets/45427770/5bd9862e-b719-47d0-8cb7-a080b1d39672)


---

schedule timeslots.html WS Websocket inspect

Chrome inspect => Network => WS

ESP32 Webserver mDNS is named http://attick.local

and now ????

![2023-08-19-152706_1920x1080_scrot](https://github.com/ldijkman/randomnerd_esp32_wifi_manager/assets/45427770/d95aecb2-7b6b-47b9-8115-702e0e6bc48d)


---

looks like i have an ws upload save  or delete on tuesday change

 websocket.send(JSON.stringify( timeslot_to_ESP ));

![2023-08-19-160308_1920x1080_scrot](https://github.com/ldijkman/randomnerd_esp32_wifi_manager/assets/45427770/54e53bad-eee9-4585-a307-91d4aa13201f)

---

WS upload on wednesday change

![2023-08-19-161131_1920x1080_scrot](https://github.com/ldijkman/randomnerd_esp32_wifi_manager/assets/45427770/3640b499-951a-4e6a-b420-60440c178ee4)


---

show only outgoing websocket messages in chrome inspect

![2023-08-19-162307_1920x1080_scrot](https://github.com/ldijkman/randomnerd_esp32_wifi_manager/assets/45427770/27d85aae-7609-4699-85b2-92b7d2ac1f76)


### ok now i should write some code on the arduino ESP8266 / ESP32 side

https://arduinojson.org/v6/assistant/#/step2

websocket message when save or delete button on tuesday is clicked
<pre>
 var dy=daytext;
 var ts=timeslots;
 timeslot_to_ESP = {dy,ts};

* websocket message {"dy":"Tue","ts":[0,60,300,360,600,660,900,960,1200,1260]}
* deserialize {"dy":"Tue","ts":[0,60,300,360,600,660,900,960,1200,1260]}
 
 https://arduinojson.org/v6/assistant/#/step2
 result arduino code

 
// Stream& input; {"dy":"Tue","ts":[0,60,300,360,600,660,900,960,1200,1260]}

StaticJsonDocument<256> doc;

DeserializationError error = deserializeJson(doc, input);

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

const char* dy = doc["dy"]; // "Tue"

JsonArray ts = doc["ts"];
int ts_0 = ts[0]; // 0
int ts_1 = ts[1]; // 60
int ts_2 = ts[2]; // 300
int ts_3 = ts[3]; // 360
int ts_4 = ts[4]; // 600
int ts_5 = ts[5]; // 660
int ts_6 = ts[6]; // 900
int ts_7 = ts[7]; // 960
int ts_8 = ts[8]; // 1200
int ts_9 = ts[9]; // 1260

 
</pre>

### Does it make Sense, i do not know

video served from ESP32 ace editor websockets

https://youtu.be/17K2TtYPI_A
