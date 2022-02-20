files Thursday 17 february 2022 
# Program the ESP8266 with a simple tool
# For normal People

Binary files for ESP8266 32mbit == 4MByte ---------------> (eesz=4M2M, 4MB of wich 2MB is set/used for FS LittleFS)

my Arduino IDE Compiler settings, maybe these settings are handy for u?

"fqbn": "esp8266:esp8266:generic:xtal=160,vt=flash,exception=legacy,ssl=all,ResetMethod=nodemcu,CrystalFreq=26,FlashFreq=80,FlashMode=qio,eesz=4M2M,led=2,sdk=nonosdk_190703,ip=lm2f,dbg=Disabled,lvl=None____,wipe=none,baud=115200",

Maybe more people are able to try / test it this way

not all finnished == but most is working

---

program ESP8266 with ino bin and littlefs bin 

connect your computer / phone / tablet wifi to ESP Access Point direct connect

browse to 192.168.4.1 for wifi manager and configure ESP8266 for your wifirouter

hope the rest goes automaticly
- (MS Windows users might need to install Apple iTunes to get mDNS URL .local working)
- Android us Bonjourbrowser App to see list browse mDNS https://play.google.com/store/apps/details?id=de.wellenvogel.bonjourbrowser&hl=nl&gl=US

## login pw for littleFSbrowser filemanager texteditor == admin / admin

Succes!!! Play and have Fun with Electra, Warning Fiddling with Electra can Kill You!

show me a video if you got it working????

---

Download next 2 files to your computer

1 is ino bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin

1 is 2mb littlefs bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin


## huh ESP8266 downloadtool == uploadtool?

https://www.espressif.com/en/support/download/other-tools?keys=&field_type_tid%5B%5D=14
- https://www.espressif.com/sites/default/files/tools/flash_download_tool_3.9.2.zip

# jak started windows 7 laptop
# looks like this works 
# ino bin at 0x0
# mklittlefs bin at 0x200000

![ESP8266_download_tool](https://user-images.githubusercontent.com/45427770/154829873-ca5841cd-37e6-44ee-b582-d828457fe07a.png)


---






