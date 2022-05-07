# Touch Electra

## Easy install Electra Touch TFT on ESP8266 4MByte 12E / 12F from Browser

ESP Web installer https://ldijkman.github.io/randomnerd_esp32_wifi_manager/Touch_Electra-Electra_Touch/
- 4 versions to choose from (at its best with a 480x320 TFT screen) 
- - ILI9341_DRIVER for SPI TFT Touch display.
- - ILI9486_DRIVER  for SPI TFT Touch display. with openweather -> edit config.txt -> from cloudeditor
- - ILI9488_DRIVER  for SPI TFT Touch display. with openweather -> edit config.txt -> from cloudeditor
- - ST7796_DRIVER for SPI TFT Touch display. with openweather -> edit config.txt -> from cloudeditor
- - ESP Web installer https://ldijkman.github.io/randomnerd_esp32_wifi_manager/Touch_Electra-Electra_Touch/
-
- if you delete the file touch_calibrate.txt on the ESP with webeditor ACE js CloudEditor http:// IP or mDNS /edit
- - - editor login == admin / admin (removed the login)
- - then on next reboot a touch calibrate again
- D0==GPIO16 free for relais
- D1, D2 for i2c BME280 temperature / humidity / millibar pressure

want to make an ESP8266 touch display for Electra

Easy Home Automation


 <br>(sorry wil be best for 480x320 TFT displays 14pins SPI resistive touch IC XPT2046)<br>
<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/docs/Touch_Electra-Electra_Touch/img_1_1651851213226.jpg">
<br><br>
<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/docs/Touch_Electra-Electra_Touch/img_2_1651851229852.jpg">
<br
    
---

idea: do a local network scan for other mDNS "Electra" devices: 
- kitchen.local, living.local, garage.local, garden.local Etcetera
- and show touch controlled buttons on screen. button color reveals status of the other devices

---

Will try TFT Touch LCD with ESP8266 NodeMCU 12E TFT_eSPI https://www.google.com/search?q=nodemcu
- also same pinout tested on ESP8266 Wemos D1 R2 12F arduino uno sized == succesfull 

https://github.com/Bodmer/TFT_eSPI

https://youtu.be/jgfdkedoNfE

---

### ESP8266 NodeMCU 12E 12F to 14pins SPI touch TFT connections

- VCC == +5vdc in
- GND == gnd
- CS == D8
- RESET == RST
- DC/RS == D3
- SDI(MOSI) == D7
- SCK == D5
- LED == +3.3vdc  (could make it PWM to set backlight brightness)
- - - ord dim display or turn backliht off att certain times, on at touch    
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

image 14 pins SPI TFT XPT2046 Resistive Touch   
- image from https://protosupplies.com/product/tft-lcd-3-2-240x320-rgb-spi-display-with-touchscreen/
- But Better use a 480x320 for my code
    
<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/TFT-LCD-28-240x320-RGB-ILI9341-with-Touchscreen-Connections.jpg">    
    
---

### make sure to set the right tft driver for your display
- edit user_setup.h located in /home/pi/Arduino/libraries/TFT_eSPI/user_setup.h

ESP8266 NodeMCU 12E tft_espi meters example test

YT video of same tft_espi meters example but running on esp32 https://www.youtube.com/watch?v=pkHV_xGdL-s

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220402_091959.jpg">

# prototype setup
ESP8266 Wemos D1 R2 12F arduino uno sized 
- with arduino mega 2560 proto PCB perf board shield
- and 3,5inch SPI touch TFT
- 
- - PCB Shield https://wiki.keyestudio.com/KS0323_Keyestudio_MEGA2560_Prototype_Circuit_Breakout_Board_PCB_10PCS
- - https://www.google.com/search?q=ESP8266+Wemos+D1+R2+12F+arduino+uno+sized&oq=ESP8266+Wemos+D1+R2+12F+arduino+uno+sized
- - Touch SPI TFT https://www.google.com/search?q=sku+msp3520&oq=sku+msp3520
- - - http://www.lcdwiki.com/3.5inch_SPI_Module_ILI9488_SKU:MSP3520

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220403_084314.jpg">

 prototype setup

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220403_085010.jpg">

# more wires for touch

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220403_210051.jpg">

# Just Stack it

### storm in brain, make GUI scalable for 320x240 and 480x320

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220410_133314.jpg">

see if i can make a scaled gui that will look more or less the same on 320x240 and 480x320

sw x 0 to 1, SH x 0 to 1, got it from touch x/SW, y/SH

the scaled button is from center screen to rightbottom quarter center

on a smaller resolution pixels screen that scaled button will be the same possition from center screen to rightbottom quarter center

topleft will then be on the center off gray rectangle wich is the smaller screen resolution 320x240 this is 480x320

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220411_193140.jpg">


Bodmer openweather test hmmm https://blog.squix.org/2017/07/new-weatherstation-color-version-published.html

Electra touch should have this ;-)

config is now in ino code wivh is not handy
- - would like to include this with Electra so it can be installed from Brower
- - - not the arduino loads off library nerdy stuff, make it easy for normal people 
- openweather api key https://openweathermap.org/
- timezone
- locaction Latitude and Longitude Finder https://www.latlong.net/

could make a config.txt in litlefs
- and edit the config.txt file with inbrowser ace js cloud-web editor  

https://github.com/ldijkman/OpenWeather

<img src="https://user-images.githubusercontent.com/45427770/163704146-f62e8802-f3ac-44c4-85fa-6cd028bad5b5.jpg">

https://github.com/ldijkman/OpenWeather

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220417_101552.jpg">

Mixed copy paste mesh

Electra's OpenWeatherMap browser installed on ESP

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220427_054226.jpg">

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220430_140351.jpg">

---

# EasyEDA Design a PCB inbrowser and order it inbrowser Cheap at JLCPCB
- https://easyeda.com/search?wd=arduino+mega+shield+pcb&indextype=components
- wemos d1 r2 shield https://easyeda.com/component/1130d6e76349418f8add4e80361826aa

---




## Electra Needs a Case
- 3D Printed ;-)

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220416_073834.jpg">

arduino ide settings
- "fqbn": "esp8266:esp8266:generic:xtal=160,vt=flash,exception=legacy,ssl=all,ResetMethod=nodemcu,CrystalFreq=26,FlashFreq=40,FlashMode=dout,eesz=4M2M,led=2,sdk=nonosdk_190703,ip=lm2f,dbg=Disabled,lvl=None____,wipe=all,baud=115200",
  

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220402_115032.jpg">

arduino ide settings

nodemcu pinout

![NodeMcu-V21-CP2102-Lua-ESP8266-pinout-mischianti-high-resolution](https://user-images.githubusercontent.com/45427770/155881391-281d12c5-810a-437b-9245-e10ef1266067.png)
picture https://www.mischianti.org/

![NodeMcu-V3-CH340-Lua-ESP8266-pinout-mischianti-low-resolution](https://user-images.githubusercontent.com/45427770/155927695-04cdb781-7502-487b-8685-b1340a4bf61a.jpg)
picture https://www.mischianti.org/

---

## Wemos D1 R2 pinout arduino uno sized board ESP8266 12F 32mbit==4MByte

https://www.google.com/search?q=Wemos+D1+R2+pinout+arduino+uno+sized+board&oq=Wemos+D1+R2+pinout+arduino+uno+sized+board

![wemos_d1_r2_pinout](https://user-images.githubusercontent.com/45427770/161381406-6ab25a4e-1d82-4d2e-8db5-e0682ff61cc4.jpg)
picture https://protosupplies.com/product/esp8266-d1-r2-wifi-processor-with-uno-footprint/

---

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

# All you need is Electra
