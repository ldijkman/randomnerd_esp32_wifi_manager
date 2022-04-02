# Touch Electra!

want to make an ESP8266 touch display for Electra

Will try TFT Touch LCD with ESP8266 NodeMCU 12E TFT_eSPI https://www.google.com/search?q=nodemcu
-also same pinout tested on ESP8266 Wemos D1 R2 12F arduino uno sized == succesfull 

https://github.com/Bodmer/TFT_eSPI

https://youtu.be/jgfdkedoNfE

ESP8266 NodeMCU 12E TFT connections
- vcc == +5vdc in
- gnd == gnd
- reset == d4
- cs == d8
- dc/rs == d3
- sdi(mosi) == d7
- sck == d5
- led == +3.3vdc  (could make it PWM to set backlight brightness)
- sdo(miso) == d6
-
- as defined in tft_espi user_setup.h
- #define TFT_MISO  PIN_D6
- #define TFT_MOSI  PIN_D7
- #define TFT_SCLK  PIN_D5
- #define TFT_CS   PIN_D8  // Chip select control pin
- #define TFT_DC     PIN_D3  // Data Command control pin
- // #define TFT_RST   4  // Reset pin (could connect to RST pin)
- #define TFT_RST   PIN_D4  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

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
