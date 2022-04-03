# Touch Electra!

want to make an ESP8266 touch display for Electra

---

idea: do a local network scan for other mDNS "Electra" devices
- and show a touch control butoon on screen. button color reveals status of the other device

---

Will try TFT Touch LCD with ESP8266 NodeMCU 12E TFT_eSPI https://www.google.com/search?q=nodemcu
-also same pinout tested on ESP8266 Wemos D1 R2 12F arduino uno sized == succesfull 

https://github.com/Bodmer/TFT_eSPI

https://youtu.be/jgfdkedoNfE

ESP8266 NodeMCU 12E TFT connections
- VCC == +5vdc in
- GND == gnd
- CS == D8
- RESET == D4
- DC/RS == D3
- SDI(MOSI) == D7
- SCK == D5
- LED == +3.3vdc  (could make it PWM to set backlight brightness)
- SDO(MISO) == D6
-
- touch not tested yet
- TIRQ == not used
- T_DO == shared with SDO(MISO)
- T_DIN == shared with SDI(MOSI)
- T_CS == D2
- T_CLK == shared with SCK
-
- as defined in tft_espi user_setup.h
- #define TFT_MISO     PIN_D6
- #define TFT_MOSI     PIN_D7
- #define TFT_SCLK     PIN_D5
- #define TFT_CS       PIN_D8      // Chip select control pin
- #define TFT_DC       PIN_D3      // Data Command control pin
- // #define TFT_RST   4           // Reset pin (could connect to RST pin)
- #define TFT_RST      PIN_D4      // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST
-
- #define TOUCH_CS PIN_D2           // Chip select pin (T_CS) of touch screen

### make sure to set the right tft driver for your display

ESP8266 NodeMCU 12E tft_espi meters example test

same tft_espi meters example but running on esp32 https://www.youtube.com/watch?v=pkHV_xGdL-s

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220402_091959.jpg">

# prototype setup
ESP8266 Wemos D1 R1 12F arduino uno sized with arduino mega proto pcb perf board shield and 3,5inch SPI touch TFT
- PCB Shield https://wiki.keyestudio.com/KS0323_Keyestudio_MEGA2560_Prototype_Circuit_Breakout_Board_PCB_10PCS
- https://www.google.com/search?q=ESP8266+Wemos+D1+R2+12F+arduino+uno+sized&oq=ESP8266+Wemos+D1+R2+12F+arduino+uno+sized
- Touch SPI TFT https://www.google.com/search?q=sku+msp3520&oq=sku+msp3520

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220402_135300.jpg">

arduino ide settings

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220402_115032.jpg">

arduino ide settings

nodemcu pinout

![NodeMcu-V21-CP2102-Lua-ESP8266-pinout-mischianti-high-resolution](https://user-images.githubusercontent.com/45427770/155881391-281d12c5-810a-437b-9245-e10ef1266067.png)
picture https://www.mischianti.org/

![NodeMcu-V3-CH340-Lua-ESP8266-pinout-mischianti-low-resolution](https://user-images.githubusercontent.com/45427770/155927695-04cdb781-7502-487b-8685-b1340a4bf61a.jpg)
picture https://www.mischianti.org/

wemos d1 r2 pinout
![wemos_d1_r2_pinout](https://user-images.githubusercontent.com/45427770/161381406-6ab25a4e-1d82-4d2e-8db5-e0682ff61cc4.jpg)

---

# Electra Touch

<p align="center">         
<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/Electra.jpg">
</p> 

### Soon Electra wil Power a Gazillion Devices!
