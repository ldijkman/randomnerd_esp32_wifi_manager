files Thursday 17 february 2022 
# Program the ESP8266 with a simple tool
# For normal People

Binary files for ESP8266 32mbit == 4MByte

Maybe more people are able to try / test it this way

not all finnished == but most is working

---

program ESP8266 with ino bin and littlefs bin 

connect your computer / phone / tablet wifi to ESP Access Point direct connect

browse to 192.168.4.1 for wifi manager and configure ESP8266 for your wifirouter

hope the rest goes automaticly
- (MS Windows users might need to install Apple iTunes to get mDNS URL .local working)
- Android us Bonjourbrowser App to see list browse mDNS https://play.google.com/store/apps/details?id=de.wellenvogel.bonjourbrowser&hl=nl&gl=US

Succes!!! Play and have Fun with Electra, Warning Fiddling with Electra can Kill You!

show me a video if you got it working????

---

Download next 2 files to your computer

1 is ino bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin

1 is 2mb littlefs bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin


## huh ESP8266 downloadtool == uploadtool?

https://www.espressif.com/en/support/download/other-tools?keys=&field_type_tid%5B%5D=14
- https://www.espressif.com/sites/default/files/tools/flash_download_tool_3.9.2.zip

### jak, started second hand windows 7 laptop (normally My usb stick x86 linux raspberry/debian)
# This works 
# ino bin at 0x0
# mklittlefs bin at 0x200000
- be sure that there are 5 zeros after the 0x2
- do not forget the checkboxes in front off the bin files, files an 0x0 0x200000 should light up green
- - for some ESP8266 (RobotDyn Uno/Mega WiFi) boards i have to install a driver to see the COM Port in list
- - CH34x_Install_Windows_v3_4.zip
- - https://www.google.com/search?q=CH34x_Install_Windows_v3_4.zip

![ESP8266_download_tool](https://user-images.githubusercontent.com/45427770/154829873-ca5841cd-37e6-44ee-b582-d828457fe07a.png)

### Ja dat is jouw laptop Pieter Man! ;-)
Smeerlap, stond vol met porno.

---
Robotdyn Uno WiFi ESP8266 32mbit==4MByte - Robotdyn Mega WiFi ESP8266 32mbit==4MByte
- program Dip 567 to on
- run / serial monitor Dip 56 on
- or run = all dip off

---

## login pw for littleFSbrowser filemanager texteditor == admin / admin

## Soon Electra will power a Gazillion Devices






