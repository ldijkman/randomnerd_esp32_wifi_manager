BIN files Sunday 20 february 2022 
# Program the ESP8266 with a simple tool
# For normal People

Binary files for ESP8266 (For All board types with 32mbit == 4MByte)

Maybe more people are able to try / test it this way

not all finnished == but most is working

---

program ESP8266 with *.ino.bin and *.littlefs.bin 

- connect your computer / phone / tablet WiFi to "ESP-WIFI-MANAGER-(?????)" Access Point, WiFi Direct Connect

- Browse to http://192.168.4.1 for wifi manager and configure ESP8266 for your wifirouter

- hope the rest goes automaticly
- - (MS Windows users might need to install Apple iTunes to get mDNS URL .local working)
- - Android phone/tablet use Bonjourbrowser App to see list browse mDNS https://play.google.com/store/apps/details?id=de.wellenvogel.bonjourbrowser&hl=nl&gl=US

Succes!!! Play and have Fun with Electra
- Warning, Fiddling with Electra can Kill You!

<b>Show me a video if you got it working????</b>
- https://github.com/ldijkman/randomnerd_esp32_wifi_manager/discussions
---

### Download next 2 files to your computer

*.ino.bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin

*.mklittlefs.bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin


## Download / Install, huh ESP8266 downloadtool == uploadtool?

https://www.espressif.com/en/support/download/other-tools?keys=&field_type_tid%5B%5D=14
- https://www.espressif.com/sites/default/files/tools/flash_download_tool_3.9.2.zip

### jak, started second hand windows 7 laptop (normally My usb stick x86 linux raspberry/debian)
# This works 
# *.ino.bin at 0x0
# *.mklittlefs.bin at 0x200000
- <b>be sure that there are 5 zeros after the 0x2</b>
- do not forget the checkboxes in front off the bin files
- - files and 0x0, 0x200000 should light up green
- - for some ESP8266 (RobotDyn Uno/Mega WiFi) boards i have to install a driver to see the COM Port in list
- - - CH34x_Install_Windows_v3_4.zip
- - - https://www.google.com/search?q=CH34x_Install_Windows_v3_4.zip


![ESP8266_download_tool](https://user-images.githubusercontent.com/45427770/154829873-ca5841cd-37e6-44ee-b582-d828457fe07a.png)

# NEW
- or download Combined BIN https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Binary_4_ESP8266_4MB/Electra_Combined_only_this_at_0x0.bin
- only this one at 0x0  (== 2 BIN files in 1 BIN file )

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/Binary_4_ESP8266_4MB/20220223_033932.jpg">


### Ja dat is jouw laptop Pieter Man! ;-)
Smeerlap, stond vol met p*rn*.

---
Robotdyn Uno WiFi ESP8266 32mbit==4MByte - Robotdyn Mega WiFi ESP8266 32mbit==4MByte
- program Dip 567 to on
- run / serial monitor Dip 56 on
- or run = all dip off
- - LED on this board is GPIO 14

---

## login password for littleFSbrowser filemanager texteditor == admin / admin

## Soon Electra will power a Gazillion Devices

Test 12345

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/images/20220221_034042.jpg">



Do or did you see any ads???
