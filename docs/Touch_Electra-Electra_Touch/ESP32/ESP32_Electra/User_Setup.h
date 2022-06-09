 // https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft 
// https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat 
// http://www.Arduino.TK

// https://www.facebook.com/groups/esp32smartthermostat
   
// Shortened TFT_eSPI Graphic_Library User_Setup.h to match Art's Hardware ESP32 38Pin SPI Touch TFT Settings    
    
// This  filelocation => /home/pi/Arduino/libraries/TFT_eSPI/User_Setup.h
// windows user_setup.h file location = I do not now  programfiles/arduino....  or documents/arduino.....
// online original User_Setup.h file = https://github.com/Bodmer/TFT_eSPI/blob/master/User_Setup.h

//%%%%%%%%%%%%%%%%%
// define only one screen driver, the other ones must be commented out
//%%%%%%%%%%%%%%%%
// #define ILI9341_DRIVER     // My, Luberth tested ok, 2.8 inch & 3.2 inch SPI TFT display 320x240
// #define ILI9488_DRIVER     // My, Luberth tested ok, 3.5 inch SPI TFT display 480x320 will work, Future Big Art
#define ST7796_DRIVER         // My, Luberth tested ok, 4 inch SPI TFT display 480x320 will work, Future Big Art

// SPI section http://www.lcdwiki.com/Main_Page // has more info on SPI Displays

// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   ######

//TFT LED could be +3.3Vdc or gpio pin?? for PWM backlight brightness control, see my code for used GpioPinName
#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS   15  
#define TFT_DC    2 
#define TFT_RST   4 
/////////////////// #define TFT_RST  -1  // Set TFT_RST to -1 if display RESET is connected to ESP32 board RST

#define TOUCH_CS 21     // Chip select pin (T_CS) of touch screen

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
////// #define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT

#define SPI_FREQUENCY  40000000

#define SPI_READ_FREQUENCY  20000000    // luberth i do not use read, i think

#define SPI_TOUCH_FREQUENCY  2000000

#define USE_HSPI_PORT                  // 
