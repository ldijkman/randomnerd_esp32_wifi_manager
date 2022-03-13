# ART-ESP32-Touch-TFT-Thermostat

ART ESP32 SPI TFT Touch Clock Thermostat	

Manual by Touch TFT and WIFI(Future) clock thermostat

10 dollar DIY NEST thermostat	

Art, A Better NEST	

&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

GNU General Public License,

which basically means that you may freely copy, change, and distribute it,

but you may not impose any restrictions on further distribution,

and you must make the source code available.

&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft	


https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat	


https://www.youtube.com/user/LuberthDijkman/videos


https://m.facebook.com/groups/2643123052617990

https://www.facebook.com/groups/esp32smartthermostat




#
## A Part of Art => HardWare is described @
## https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft



Let's make ART smart!


.	

.	
#	
# Start ART	

@[youtube](http://youtu.be/qNYT64CaLEI)	

Simple Looks, No OverKill (Maybe make it SkinAble, For Those who like OverKill)

OK Distracted https://www.youtube.com/watch?v=0U4r2_s59qk

<img src="https://image.easyeda.com/pullimage/0pvffSdQuBwEW5eRixJsPd3uQcttBgp2v1z47P3t.jpeg">

ECO mode = continu low heat setpoint energy saving setpoint (14C?)

NORMAL mode = continu heat comfortable setpoint (21C?)

AUTO mode = Switch heat temperature on programmed times with temperature

COOL mode = continu setpoint cooling airco/ventilator (25C?)


@[youtube](http://youtu.be/qNYT64CaLEI)	

![ART_ESP32_Thermostat](https://user-images.githubusercontent.com/45427770/101690375-8d377400-3a6d-11eb-8191-ab8abd6a1b2d.png)	

@[youtube](http://youtu.be/qNYT64CaLEI)	

Future (Could use some help on the WiFiManger & WebServer / HTML WebPage Part)

<img src="https://image.easyeda.com/pullimage/A4bHd1cMRSmGSywTSo8FhNrSkIzuRznVZiUuAgie.jpeg">	

https://jsfiddle.net/luberth/b6y53cn0	

FullScreen https://jsfiddle.net/luberth/b6y53cn0/embedded/result/#Result	


#	
## First time EasyEDA.com and JLCPCB.com and LCSC.com == Perfect!	

My ESP32 TFT prototype test board, extra row of female connnectors for connecting devices test pinout

Only the holes ar a bit tight, but female row headers fit => Next time, double side copper PCB

And Ground the copper poor infill

<img src="https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/ESP32_SPI_touch_TFT_PCB.jpeg">	

My ESP32 TFT prototype test board, extra row of female connnectors for connecting devices test pinout	

First time EasyEDA.com and JLCPCB.com and LCSC.com == Perfect!	

#
## DS3231 RTC with NTC Thermistor soldered onto power 

## sorry i switched to BME280 sensor temp. humid. barometer sensor == much better 

VCC on RTC DS3231 is 3.3V

Less Wires = Only a Signal wire from NTC Thermistor

NTC Connect => (-GND to VCC+3.3V) (VCC+3.3V to -GND) In Other Words Silkscreen print - should be + 

(This way its PULLDOWN) NTC Signal Line pulled down to ground
```diff
-Art's TFT screen will tell you how to connect the wires to ESP32 on startup

-On first boot Art's screen is Snowy for 20 seconds => I think Art is Formatting his Brain/Flash


```
ESP32 Note: Analog noise and fluctuences with analog read => multiread and capacitor 

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html

Not so clear for me as DIY Tinker  => think they want a 0.1mf 100uf capacitor between signal and ground to damp the analog read

<img src="https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/RTC_DS3231_NTC_Thermistor.jpg">


#
## TFT Backlight PWM cut the LED track to 3.3V

i have cut the LED track to 3.3V between the Pads

soldered a wire on the LED side pad

LED connected Wire connected to GPIO15 for the moment

Can now control the BackLight PWM from the screen/slidebar

in the LOOP{} is a hardcoded setting for now => dim screen if hour > ?? and < as ??

Jo's Energy Saver ;-)

a touch in top of screen in the blue rectangle => opens the settings menu

Blue border rectangle = Heating / Cooling is OFF

DutchOrange border Rectangle = The Heat is ON

IceBlue border Rectangle = Cooling is ON

<img src="https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/Art_Thermostat_backlight_PWM.jpg">


#
## Art output relais  heat & cool or single relais

the double relaiscoil is optical isolated swithed by optocoupler

the single relaiscoil is switched by transistor

a bit big relais for most off the time 24VAC CentralHeatingSystem switching

GND=GND

VCC = +5V (for the relais Coil) ESP32 +5VDC is comming from  USB

IN1, IN2 = if pulled low to GND => relais==ON (GPIO25 and GPIO26 from ESP32)

===== maybe Disconnect relais when programming ESP32  ======

<img src="https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/Art_Thermostat_relais.jpg">

#
## Art's Sensor BME280 Temperature, Humidity, Barometer (4Future)

ESP32 BME280 sensor test 

https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/test/ESP32_BME280_barometer_humidity_temperature_sensor_test.ino

<img src="https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/Art_Thermostat_BMP280.jpg">

#

BME280 humidity a scale makes vissible how whe ar doing with RV%

got my barometer pressure info from my pi webserver page http://84.107.155.75/

HE IS DAT HTTP://ARDUINO.Tk

## Art with Linear Humidity Comfort Scale 

<img src="https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/Art_Therrmostt_humidity_scale.jpg">

#
## Art with Linear BaroMeter and Humidity Comfort Scale

No it's not a slider, Art can not change the weather!

<img src="https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat/blob/main/Art_Thermostat_linear_barometer.jpg">


#	
## This is wat your Arduino IDE should look like, Main File with the TAB files	

ART_ESP32_Thermostat_7_12_2020_ver2.ino => is the Main File	

The other *.INO files are included tab files (Should be in the same Directory as Main File)	

<img src="https://image.easyeda.com/pullimage/VNE6BX0bdmtFa41PH79R6Qq3eSFhpZg6qHJ66yZu.jpeg">	


#
Have you got Arduino Experience, But don't know what to Do

WANTED, Boring Bored People or Students, I Could use some Help?!  ;-) 	

Make YourSelf UseFull!	

#

## It is Calendar Time, Free Printable Calender in many Languages	
## Print a Calendar for your Parents, GrandParents	
## http://sticker.tk/kalender.php
## http://arduino.tk
## http://PRINT-it.tk      
## http://PRINTit.tk


Art has a brand new home server http://www.arduino.tk

#
## maybe rtttl nokia ringtones for Art's Alarm 

http://Arduino.tk/rtttl/

http://Arduino.tk/rtttl/RTTTL_Tunes/ couple off thousands tunes 

We Dutch love Orange http://arduino.tk//rtttl/RTTTL_Tunes/play.php?file=Andr%E9+Hazes+-+Wij+Houden+Van+Oranje.txt

4 Art's BirthDay  http://sticker.tk/forum/rtttl/RTTTL_Tunes/play.php?file=Misc+-+Happy+Birthday+1.txt

dat mensen hier geld voor betaalden 
http://arduino.tk/rtttl/RTTTL_Tunes/play.php?file=xfiles.txt


#
### A Penny for Sharing My Thoughts?	

www.paypal.me/LDijkman	

# Art is now LIVE at http://Arduino.TK

# Help Art?!

https://m.facebook.com/groups/2643123052617990

https://www.facebook.com/groups/esp32smartthermostat
