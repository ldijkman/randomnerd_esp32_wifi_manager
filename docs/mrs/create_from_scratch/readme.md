

https://ldijkman.github.io/randomnerd_esp32_wifi_manager/mrs/create_from_scratch/index.html


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

