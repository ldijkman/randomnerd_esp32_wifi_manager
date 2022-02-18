files Thursday 17 february 2022 

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

Succes!!! Play and have Fun with Electra, Warning Fiddling with Electra can Kill You!

show me a video if you got it working????

---

maybe you know how this works

1 is ino bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin

1 is 2mb littlefs bin https://github.com/ldijkman/randomnerd_esp32_wifi_manager/blob/main/Binary_4_ESP8266_4MB/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin

---

could you make a video how you do this???

or could u / willing to write an HowTo https://github.com/ldijkman/randomnerd_esp32_wifi_manager/discussions/15

---

Yowza, that’s a lot of files. Try again with fewer than 100 files.

i dont know maybe you do it with 

https://www.espressif.com/en/support/download/other-tools?keys=&field_type_tid%5B%5D=14

but thats mswindows thats not for my linux pi
