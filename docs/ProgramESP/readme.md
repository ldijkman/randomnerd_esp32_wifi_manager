inBrowser programming ESP8266 32mbit==4MByte with Electra, NO Tools Needed.  

https://ldijkman.github.io/randomnerd_esp32_wifi_manager/ProgramESP/index.html 2 bins uses manifest2.json

---

(not succeful working yet)

https://ldijkman.github.io/randomnerd_esp32_wifi_manager/ProgramESP/programesp.html 1 combined bin uses manifest.json

must be an https:// connection on chromium, chrome or edge browser

/home/pi/Downloads/arduino-esp32-master/tools/esptool.py --chip esp8266 merge_bin -o /home/pi/Downloads/Newe/merged-flash.bin --flash_mode dio --flash_size 4MB 0x0 /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.ino.bin 0x200000 /home/pi/Downloads/Newe/ESP8266-LittleFS-wifi-manager_with_editor.mklittlefs.bin

