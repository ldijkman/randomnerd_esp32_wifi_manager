// hello
// https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft
// https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat
// http://www.Arduino.TK
//
// https://m.facebook.com/groups/2643123052617990
// https://www.facebook.com/groups/esp32smartthermostat
//
// GNU General Public License,
// which basically means that you may freely copy, change, and distribute it,
// but you may not impose any restrictions on further distribution,
// and you must make the source code available.
//

// Wouldnt that be Great if Art can remember Things
// Read from Arts memory and write into Arts memory
//
// touch calibrate setting save has already formatted Arts Brain if needed
//
// Use new brain-file for Art => file = "/Arts_Memory";
//
//***************************
// what do we want to save
//***************************
// eco setpoint
// normal setpoint
// cool setpoint
// switchpoint above / below
// alarm setpoints low/high
// screen brightnes
//
// auto modus  program & times temps
//
// Arts age ;-) time since startdate / memory creation?
// nunber of reboots
// total time heating on
// total time cooling on
//
//
//
//
//
// touch calibrate did already format and mount?
// and some other SPIFFS things?
//
//while (!SPIFFS.bgin()) {             //FORMAT_SPIFFS_IF_FAILED)) {
//   tft.println("SPIFFS Mount Failed");
//}




//###############
void ArtsMemory() {
  if (SPIFFS.exists("/Arts_Memory")) {
    tft.println("Creating arts memory file");
    WriteintoArtsMemory();
  }
  tft.setTextSize (1);
  while (0 == 0) {

    tft.fillScreen(BLACK);
    tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);
    tft.setCursor(10 , 10);
    tft.println("directory listing");
    listDir(SPIFFS, "/", 0);
    tft.println(); tft.println();
    tft.println("ListDir 5 second delay");

    for (int i = 0; i <= 500; i++) {   //500x10 is 5 seconds
      if (tft.getTouch(&x, &y)) {
        tft.drawRoundRect(1, 1, 319, 239, 2, GREEN);
        x = 0, y = 0;
        delay(1000);
        return;               // exit if touched
      }
      delay(10);
    }

    tft.fillScreen(BLACK);
    tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);
    tft.setCursor(10 , 10);
    // check if calibration file exists   // part from touch calibration
    if (SPIFFS.exists("/Arts_Memory")) {
      tft.println("Art memory file exists this is the content");
      ReadArtsMemory();
    } else {
      tft.println("Creating arts memory file");
      WriteintoArtsMemory();
    }

    tft.println(); tft.println();
    tft.println(" 5 second delay");
    for (int i = 0; i <= 500; i++) {
      if (tft.getTouch(&x, &y)) {
        tft.drawRoundRect(1, 1, 319, 239, 2, GREEN);
        x = 0, y = 0;
        delay(1000);
        return;
      }
      delay(10);
    }
  }
}





//##############################################
void WriteintoArtsMemory() {
  File  file = SPIFFS.open("/Arts_Memory", FILE_WRITE);
  if (!file) {
    tft.println("- failed to open file for writing");
    return;
  } else {
    file.println(millis());
    file.println(eco_setpoint);
    file.println(normal_setpoint);
    file.println(cool_setpoint);
    file.println("1555");
    file.println("12345");
    file.println("6789");
    file.println("16611.111");
    file.println("11.111");
    file.close();
    tft.println("done writing into arts memory file");
  }
}





//##########################################
void ReadArtsMemory() {
  File readfile = SPIFFS.open("/Arts_Memory");
  if (!readfile || readfile.isDirectory()) {
    tft.println("no good");
    return;
  }

  tft.println(" Got acces 2 Arts memory, going to read Art's Mem.");
  tft.println("");
  int i = 1;
  String ThisString, readstring;
  while (readfile.available()) {

    readstring = (readfile.readStringUntil('\n'));
    if (i == 1) {
      tft.print(" millis        ");
    }
    if (i == 2) {
      tft.print(" eco setpoint  ");
    }
    if (i == 3) {
      tft.print(" normal sepoint");
    }
    if (i == 4) {
      tft.print(" cool setpoint ");
    }

    tft.print(" = ");
    tft.println(readstring);

    i = i + 1;

  }
}




//################################################################
void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  tft.println("");
  tft.printf("Listing directory: %s\r\n", dirname);
  tft.println("");
  File root = fs.open(dirname);
  if (!root) {
    tft.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    tft.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      tft.print("  DIR : ");
      tft.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      tft.print("  FILE: ");
      tft.print(file.name());
      tft.print("\t SIZE: ");
      tft.println(file.size());
    }
    file = root.openNextFile();
  }
}
