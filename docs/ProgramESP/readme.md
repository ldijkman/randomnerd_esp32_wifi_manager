inBrowser programming ESP8266 32mbit==4MByte with Electra, NO Tools Needed.  

https://ldijkman.github.io/randomnerd_esp32_wifi_manager/ProgramESP/index.html 2 bins uses manifest2.json

---

(not succeful working yet) not sure maybe it is my raspberry pi chromium thats is not working

https://ldijkman.github.io/randomnerd_esp32_wifi_manager/ProgramESP/programesp.html 1 combined bin uses manifest.json

must be an https:// connection on chromium, chrome or edge browser

---

another inbrowser programming tool that loads bin files from disk 
- https://adafruit.github.io/Adafruit_WebSerial_ESPTool/
- https://nabucasa.github.io/esp-web-flasher/

---

/home/pi/Downloads/arduino-esp32-master/tools/esptool.py --chip esp8266 merge_bin -o /home/pi/Downloads/Newe/merged-flash.bin --flash_mode dio --flash_size 4MB 0x0 /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin 0x200000 /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin

 /home/pi/Downloads/arduino-esp32-master/tools/esptool.py --chip esp8266 merge_bin -o /home/pi/Downloads/Newe/merged-flash.bin --flash_mode dio --flash_size 4MB 0x0 /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin 0x1E8480  /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin
 
 /home/pi/Downloads/arduino-esp32-master/tools/esptool.py --chip esp8266 merge_bin -o /home/pi/Downloads/Newe/merged-flash.bin --flash_mode dio --flash_size 4MB 0x0 /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin 0x200000 /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin
esptool.py v3.2-dev
Flash params set to 0x0240
Wrote 0x3fa000 bytes to file /home/pi/Downloads/Newe/merged-flash.bin, ready to flash to offset 0x0

<img src="https://github.com/ldijkman/randomnerd_esp32_wifi_manager/raw/main/Electra.jpg">

Soon Electra will Power a Gazillion Devices
