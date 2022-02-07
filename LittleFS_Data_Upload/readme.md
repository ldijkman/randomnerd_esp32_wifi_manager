https://github.com/earlephilhower/arduino-esp8266littlefs-plugin

<pre>
Arduino ESP8266 LittleFS Filesystem Uploader
Arduino plugin which packs sketch data folder into LittleFS filesystem image, and uploads the image to ESP8266 flash memory.

Installation
Make sure you use one of the supported versions of Arduino IDE and have ESP8266 core installed.
Download the tool archive from 
</pre>

https://github.com/earlephilhower/arduino-esp8266littlefs-plugin/releases.

<pre>
In your Arduino sketchbook directory, create tools directory if it doesn't exist yet.
Unpack the tool into tools directory (the path will look like <home_dir>/Arduino/tools/ESP8266LittleFS/tool/esp8266littlefs.jar).
Restart Arduino IDE.
On the OS X create the tools directory in ~/Documents/Arduino/ and unpack the files there

Usage
Open a sketch (or create a new one and save it).
Go to sketch directory (choose Sketch > Show Sketch Folder).
Create a directory named data and any files you want in the file system there.
Make sure you have selected a board, port, and closed Serial Monitor.
Select Tools > ESP8266 LittleFS Data Upload menu item. This should start uploading the files into ESP8266 flash file system. When done, IDE status bar will display LittleFS Image Uploaded message. Might take a few minutes for large file system sizes.
Screenshot
</pre>

# make sure you closed Serial Monitor on data upload. otherwise error

![screenshot](https://user-images.githubusercontent.com/45427770/152723622-2bec70b2-84cc-4a51-9234-c781dff7ecc2.png)
