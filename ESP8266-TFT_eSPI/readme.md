want to make an esp8266 touch display for Electra


Will try TFT Touch LCD with NodeMCU ESP8266 TFT_eSPI https://www.google.com/search?q=nodemcu

https://github.com/Bodmer/TFT_eSPI

https://youtu.be/jgfdkedoNfE

ESP8266 NodeMCU 12E TFT connections
- vcc == +5vdc in
- gnd == gnd
- reset == d4
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


ESP8266 NodeMCU 12E tft_espi meters example test

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/ESP8266-TFT_eSPI/20220402_091959.jpg">

