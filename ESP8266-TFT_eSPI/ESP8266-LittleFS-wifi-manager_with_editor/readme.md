# Touch Electra == Electra with tft touch display


this version uses a fork of the espasyncwebserver for LittleFSBrowser ACE js webeditor / cloudeditor 
- (edit the ESP8266 LittleFS webserver files inbrowser)

make sure u use LittleFS data upload, NOT SPIFFS

---

### ESP8266 to 14pins SPI touch TFT connections

ESP8266 NodeMCU 12E 12F TFT connections
- VCC == +5vdc in
- GND == gnd
- CS == D8
- RESET == RST
- DC/RS == D3
- SDI(MOSI) == D7
- SCK == D5
- LED == +3.3vdc  (could make it PWM to set backlight brightness)
- SDO(MISO) == (not used/needed and Do not share / connect on ILI9488, if shared with T_DO touch will not work on ILI9488)
-
- touch is tested tftespi touch_calibrate example with ili9341 ili9488
- TIRQ == not used
- T_DO == D6
- T_DIN == shared with SDI(MOSI) == D7
- T_CS == D4    
- T_CLK == shared with SCK == D5
-
- as defined in tft_espi user_setup.h /home/pi/Arduino/libraries/TFT_eSPI/user_setup.h
- #define TFT_MISO     PIN_D6
- #define TFT_MOSI     PIN_D7
- #define TFT_SCLK     PIN_D5
- #define TFT_CS       PIN_D8      // Chip select control pin
- #define TFT_DC       PIN_D3      // Data Command control pin
-                                  // Reset pin (could connect to RST pin)
- #define TFT_RST      -1          // Set TFT_RST to -1 if display RESET is connected to ESP board RST
-
- #define TOUCH_CS     PIN_D4      // Chip select pin (T_CS) of touch screen
-
- - D1, D2 free for i2c BME280?! And/Or i2c i/o extender more inputs/outputs and/or whatever i2c device
- - D0 == GPIO16 for Relais (but is high at boot, wich is no problem for me)

---


<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220430_140351.jpg">

the LAN mDNS scan linked list could be better if it asks the status of the other devices

and show a yellow or gray link button depnding on status

and maybe link to /on /off to switch from other device

like i did on this TFT LCD display https://www.youtube.com/watch?v=3qviv5TOcVo

- red = 2 cannot get a status value from switch url
- green = light=on 1 a status value from switch url
- gray = light=off 0 a status value from switch url

future? you could place ESP TFT touch displays anywhere in your house that automaticly scan for mDNS and lists it on the buttons<br>

![2022-02-15-045728_1360x768_scrot](https://user-images.githubusercontent.com/45427770/153990182-4e595ad1-138c-45d6-97d7-112c2c0ade88.png)

future? you could place ESP TFT touch displays anywhere in your house that automaticly scan for mDNS and lists it on the buttons<br>

like i did on this TFT LCD display https://www.youtube.com/watch?v=3qviv5TOcVo


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

esp8266 espasyncwebserver littlefs fsbrowser inbrowser filemanager editor / web editor / esp8266 webserver manager editor

![2022-02-14-050521_1360x768_scrot](https://user-images.githubusercontent.com/45427770/153995945-d61782d0-ca96-4251-aa6f-e1b0894bfecd.png)

esp8266 espasyncwebserver littlefs fsbrowser inbrowser filemanager editor / web editor / esp8266 webserver manager editor


2 browser windows side by side, Easy Edit
- left browser is editing index.html file on esp8266 webserver
- right browser is showing result of index.html served from esp8266 webserver

https://www.youtube.com/watch?v=xB29f0v1zLc

https://www.youtube.com/user/LuberthDijkman/videos

---

https://jsfiddle.net/luberth/hftvs72o/show

---

https://github.com/esp8266/Arduino/issues/1939

https://codepen.io/marcruecker/pen/YWwWem

https://sumn2u.github.io/realtime-html-server/  =======   https://sumn2u.github.io/realtime-html-server/

https://shellyln.github.io/mdne/

http://superblogger3.blogspot.com/2021/06/how-to-build-your-own-codepen-style.html

![2022-02-15-172738_1360x768_scrot](https://user-images.githubusercontent.com/45427770/154131558-36e44ea1-dc44-4e5d-9e36-244f83d8a7be.png)



error 404 page served from esp8266 = index.htm without l

![2022-02-15-200504_1360x768_scrot](https://user-images.githubusercontent.com/45427770/154131612-115b9fc0-1a83-439c-b9c2-06c3615ab155.png)

<pre>
Ace Editor Keyboard Shortcuts
showSettingsMenu : Ctrl-,
goToNextError : Alt-E
goToPreviousError : Alt-Shift-E
selectall : Ctrl-A
gotoline : Ctrl-L
fold : Alt-L|Ctrl-F1
unfold : Alt-Shift-L|Ctrl-Shift-F1
toggleFoldWidget : F2
toggleParentFoldWidget : Alt-F2
foldOther : Alt-0
unfoldall : Alt-Shift-0
findnext : Ctrl-K
findprevious : Ctrl-Shift-K
selectOrFindNext : Alt-K
selectOrFindPrevious : Alt-Shift-K
find : Ctrl-F
overwrite : Insert
selecttostart : Ctrl-Shift-Home
gotostart : Ctrl-Home
selectup : Shift-Up
golineup : Up
selecttoend : Ctrl-Shift-End
gotoend : Ctrl-End
selectdown : Shift-Down
golinedown : Down
selectwordleft : Ctrl-Shift-Left
gotowordleft : Ctrl-Left
selecttolinestart : Alt-Shift-Left
gotolinestart : Alt-Left|Home
selectleft : Shift-Left
gotoleft : Left
selectwordright : Ctrl-Shift-Right
gotowordright : Ctrl-Right
selecttolineend : Alt-Shift-Right
gotolineend : Alt-Right|End
selectright : Shift-Right
gotoright : Right
selectpagedown : Shift-Pagedown
gotopagedown : Pagedown
selectpageup : Shift-Pageup
gotopageup : Pageup
scrollup : Ctrl-Up
scrolldown : Ctrl-Down
selectlinestart : Shift-Home
selectlineend : Shift-End
togglerecording : Ctrl-Alt-E
replaymacro : Ctrl-Shift-E
jumptomatching : Ctrl-\|Ctrl-P
selecttomatching : Ctrl-Shift-\|Ctrl-Shift-P
expandToMatching : Ctrl-Shift-M
removeline : Ctrl-D
duplicateSelection : Ctrl-Shift-D
sortlines : Ctrl-Alt-S
togglecomment : Ctrl-/
toggleBlockComment : Ctrl-Shift-/
modifyNumberUp : Ctrl-Shift-Up
modifyNumberDown : Ctrl-Shift-Down
replace : Ctrl-H
undo : Ctrl-Z
redo : Ctrl-Shift-Z|Ctrl-Y
copylinesup : Alt-Shift-Up
movelinesup : Alt-Up
copylinesdown : Alt-Shift-Down
movelinesdown : Alt-Down
del : Delete
backspace : Shift-Backspace|Backspace
cut_or_delete : Shift-Delete
removetolinestart : Alt-Backspace
removetolineend : Alt-Delete
removetolinestarthard : Ctrl-Shift-Backspace
removetolineendhard : Ctrl-Shift-Delete
removewordleft : Ctrl-Backspace
removewordright : Ctrl-Delete
outdent : Shift-Tab
indent : Tab
blockoutdent : Ctrl-[
blockindent : Ctrl-]
transposeletters : Alt-Shift-X
touppercase : Ctrl-U
tolowercase : Ctrl-Shift-U
expandtoline : Ctrl-Shift-L
openCommandPallete : F1
addCursorAbove : Ctrl-Alt-Up
addCursorBelow : Ctrl-Alt-Down
addCursorAboveSkipCurrent : Ctrl-Alt-Shift-Up
addCursorBelowSkipCurrent : Ctrl-Alt-Shift-Down
selectMoreBefore : Ctrl-Alt-Left
selectMoreAfter : Ctrl-Alt-Right
selectNextBefore : Ctrl-Alt-Shift-Left
selectNextAfter : Ctrl-Alt-Shift-Right
toggleSplitSelectionIntoLines : Ctrl-Alt-L
alignCursors : Ctrl-Alt-A
findAll : Ctrl-Alt-K
showKeyboardShortcuts : Ctrl-Alt-H
</pre>

# Electra Touch

<p align="center">         
<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/Electra.jpg">
</p> 
<h1><b>
<p align="center"> 
Soon Electra wil Power a Gazillion Devices! 
</p>
</b></h1>
https://github.com/ldijkman/randomnerd_esp32_wifi_manager
