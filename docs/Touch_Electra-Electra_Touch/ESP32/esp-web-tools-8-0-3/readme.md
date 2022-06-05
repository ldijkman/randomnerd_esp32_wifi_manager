https://ldijkman.github.io/randomnerd_esp32_wifi_manager/Touch_Electra-Electra_Touch/ESP32/esp-web-tools-8-0-3/Burn_the_Bits.html

ok arduino ide compiler says

python /home/pi/.arduino15/packages/esp32/tools/esptool_py/3.0.0/esptool.py --chip esp32 --port /dev/ttyUSB1 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 

57344 0xe000 /home/pi/.arduino15/packages/esp32/hardware/esp32/1.0.6/tools/partitions/boot_app0.bin 

4096 0x1000 /home/pi/.arduino15/packages/esp32/hardware/esp32/1.0.6/tools/sdk/bin/bootloader_qio_80m.bin 

65536 0x10000 /tmp/arduino_build_972339/ESP_AsyncFSBrowser.ino.bin 

32768 0x8000 /tmp/arduino_build_972339/ESP_AsyncFSBrowser.ino.partitions.bin 

and

"ESP_AsyncFSBrowser.littlefs.bin", "offset": 2162688 


