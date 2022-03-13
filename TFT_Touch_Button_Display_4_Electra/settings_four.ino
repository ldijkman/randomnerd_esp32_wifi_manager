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
/*
   keyboard code from HazardsMind https://github.com/AndrewMascolo?tab=repositories
   keyboard code from HazardsMind  https://github.com/AndrewMascolo/Adafruit_Stuff
   keyboard code from https://forum.arduino.cc/t/adafruit-tft-touchscreen-keypad-for-touchscreen/347024
   Keyboard.ino =>    https://forum.arduino.cc/uploads/short-url/5usmT2vYW6bSOZXEv50QqjW0LMF.ino


  String buttontext[0] = "Sonoff 1";
  String buttontext[1] = "Sonoff 2";
  String buttontext[2] = "Sonoff 3";
  String buttontext[3] = "Sonoff 4";
  String buttontext[4] = "Sonoff 5";
  String buttontext[5] = "Sonoff 6";
  String button7text = "<<";
  String button8text = ">>";
*/
const char Mobile_KB[3][13] PROGMEM = {
  {0, 13, 10, 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
  {1, 12, 9, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L'},
  {3, 10, 7, 'Z', 'X', 'C', 'V', 'B', 'N', 'M'},
};

const char Mobile_NumKeys[3][13] PROGMEM = {
  {0, 13, 10, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {0, 13, 10, '-', '/', ':', ';', '(', ')', '$', '&', '@', '"'},
  {5, 8, 5, '.', '\,', '?', '!', '\''}
};

const char Mobile_SymKeys[3][13] PROGMEM = {
  {0, 13, 10, '[', ']', '{', '}', '#', '%', '^', '*', '+', '='},
  {4, 9, 6, '_', '\\', '|', '~', '<', '>'}, //4
  {5, 8, 5, '.', '\,', '?', '!', '\''}
};

const char textLimit = 25;
char MyBuffer[textLimit];
int butt = 0;


bool  exitkeyboard = 0;
String lightstatus = "OFF";



void settings_four_screen() {



readfromeeprom();

  x = 0; y = 0;
  delay(250);
  tft.fillScreen(BLACK);

  long slowdown;
  tft.setTextSize(2); tft.setTextColor(LIGHTGREY, BLACK);
  tft.setCursor(0 , 0);
  tft.println(" 0           12");
  tft.println(" 1           13");
  tft.println(" 2           14");
  tft.println(" 3           15");
  tft.println(" 4           16");
  tft.println(" 5           17");
  tft.println(" 6           18");
  tft.println(" 7           19");
  tft.println(" 8           20");
  tft.println(" 9           21");
  tft.println("10           22");
  tft.println("11           23");
  tft.println("");
  tft.println("");
  tft.println(buttontext[1] + " light schedule");





  while (1 == 1) {
    DateTime now = rtc.now();









    // x exit
    drawButton(300, 0, 15, 20);
    tft.setCursor(303, 3); tft.setTextSize(2); tft.setTextColor(BLACK, LIGHTGREY);
    tft.print(F("X"));
    // x exit
    if (TouchButton(300, 0, 15, 20))
    {
      delay(500);
      tft.fillScreen(BLACK);
      savetoeeprom();
      break;                     // exit while forever loop
    }

    for (int y = 1; y < 1 + 12 * 16; y = y + 16) {              // 12 hour boxes down
      for (int x = 30; x < 30 + 4 * 16; x = x + 16) {          // 4 quarter boxes sideway
        if ( sonoffstatus[1] == 2)tft.drawRoundRect(x , y, 13, 13, 1, RED); else tft.drawRoundRect(x , y, 13, 13, 1, DARKGREEN); // if 2=offline red
      }
    }

    for (int y = 1; y < 1 + 12 * 16; y = y + 16) {             // 12 hour boxes down
      for (int x = 200; x < 200 + 4 * 16; x = x + 16) {        // 4 quarter boxes sideway
        if ( sonoffstatus[1] == 2)tft.drawRoundRect(x , y, 13, 13, 1, RED); else tft.drawRoundRect(x , y, 13, 13, 1, DARKGREEN); // if 2=offline red
      }
    }

    tft.getTouch(&x, &y);
    butt = 0;

    for (int y = 1; y <= 190; y = y + 16) {
      for (int x = 30; x <= 80; x = x + 16) {
        if (Touch_q_checkbox(x, y, 13, 13)) {
          //tft.setCursor(0 , 0);
          //tft.print(butt);tft.print("  ");
          q_checkbox[butt] = !q_checkbox[butt];   // toggle
          delay(250);
        }
        if (q_checkbox[butt] == 1)tft.fillRoundRect(x + 1, y + 1, 11, 11, 1, YELLOW);  // make selected checkbox yellow
        if (q_checkbox[butt] == 0)tft.fillRoundRect(x + 1, y + 1, 11, 11, 1, BLACK);   // else black
        if (int(now.hour() * 60 + now.minute()) / 15 == butt) {
          if ((millis() / 500) % 2) {                                            // blink
            tft.drawRoundRect(x , y, 13, 13, 1, GREEN);                         // make current time quarter check lightgreen border
            tft.drawRoundRect(x + 1 , y + 1, 13 - 2, 13 - 2, 1, GREEN);         // make current time quarter check lightgreen border
            // tft.fillRoundRect(x + 1, y + 1, 11, 11, 1, GREEN);
          }
        }
        butt = butt + 1;
      }
    }


    for (int y = 1; y <= 190; y = y + 16) {
      for (int x = 200; x <= 250; x = x + 16) {

        if (Touch_q_checkbox(x, y, 13, 13)) {
          //tft.setCursor(0 , 0);
          //tft.print(butt);tft.print("  ");
          q_checkbox[butt] = !q_checkbox[butt];    // toggle

          delay(250);
        }
        if (q_checkbox[butt] == 1)tft.fillRoundRect(x + 1, y + 1, 11, 11, 1, YELLOW);
        if (q_checkbox[butt] == 0)tft.fillRoundRect(x + 1, y + 1, 11, 11, 1, BLACK);
        if (int(now.hour() * 60 + now.minute()) / 15 == butt) {
          if ((millis() / 500) % 2) {                                            // blink
            tft.drawRoundRect(x , y, 13, 13, 1, GREEN);                         // make current time quarter check lightgreen border
            tft.drawRoundRect(x + 1 , y + 1, 13 - 2, 13 - 2, 1, GREEN);         // make current time quarter check lightgreen border
            //tft.fillRoundRect(x + 1, y + 1, 11, 11, 1, GREEN);
          }
        }
        butt = butt + 1;
      }
    }

    /*
        for (int ix = 0; ix <= 95; ix++) {
          if (q_checkbox[ix] == 1) {
            tft.print(ix * 15); tft.println("           ");
            tft.print(ix * 15 + 15); tft.println("           ");
          }
        }
    */

    if ((millis() - templong)  > 1000) {                           // send to sonoff switches every second
      templong = millis();

      bitcoin_usd();

      if (q_checkbox[(now.hour() * 60 + now.minute()) / 15]) {
        sendon(1);
        lightstatus = "ON ";
      } else {
        sendoff(1);
        lightstatus = "OFF";
      }
      tft.setCursor(270 , 200); tft.setTextSize(2); tft.setTextColor(YELLOW, BLACK);
      tft.print(lightstatus);





      HTTPClient http;

      http.begin(sonoffaddress[1] + "/value");                            // Specify the URL
      //Serial.println(sonoffaddress[i] + "/value");
      http.setConnectTimeout(100);
      int httpCode = http.GET();                                         // Make the request
      sonoffstatus[1] = 2;                                               // if not changed status is 2 = error
      if (httpCode > 0) {                                                // Check for the returning code

        String payload = http.getString();
        payload.trim();                                        // trim the white space off the string:  other wise the 0 or 1 compare does not work
        //Serial.println(httpCode);
        Serial.print("payload >"); Serial.print(payload); Serial.print("<"); Serial.println("-");
        if (payload == "0") {
          sonoffstatus[1] = 0;
        }
        if (payload == "1") {
          sonoffstatus[1] = 1;
        }

        payload = "-";

      }
      else {
        Serial.println("Error on HTTP request");

      }

      http.end(); //Free the resources


    }

  }


  TempLong = millis();  // store millis() counter in variable TempLong for screen timeout

  MakeKB_Button(Mobile_KB);

 
  
  while (1 == 1) {                  // 1 wil always be 1   so forever

    if (tft.getTouch(&x, &y)) {
      //print touch xy position to serial monitor
      //  Serial.print(x);
      //   Serial.print(",");
      //   Serial.println(y);
      // tft.setTextColor(GREEN, BLACK);
      // tft.setCursor(120 , 30);
      // tft.print("X="); tft.print(x); tft.print(" ");
      // tft.setCursor(200, 30);
      // tft.print("Y="); tft.print(y); tft.print(" ");
      if (drawgreendot)tft.drawPixel(x, y, GREEN);
      TempLong = millis();  // reset when touch timeout timer millis() counter in variable TempLong
    }

    if ((millis() - TempLong)  > 60000) { // compare stored TempLong to current millis() counter  screen timeout
      tft.fillScreen(BLACK);
      break;                              // after 60 seconds inactivetie timer break while loop timeout
    }

    if ( exitkeyboard == 1) {
      exitkeyboard = 0;
      break;
    }


    GetKeyPress(MyBuffer);

    Serial.print("MyBuffer="); Serial.println(MyBuffer);






    x = 0; y = 0;                     // reset touch position

  }                                  // end while 1==1 loop forever




}


static bool shift = false;
static bool special = false, back = false, lastSp = false, lastSh = false;
static int bufIndex = 0;

void GetKeyPress(char *textBuffer){

  char key = 0;

  //if (!ts.bufferEmpty()){
  
  //ShiftKey
  if (TouchButton(15, 160, 35, 25))
  {
    shift = !shift;
    delay(200);
  }

  //Special Characters
  if (TouchButton(15, 190, 35, 25))
  {
    special = !special;
    delay(200);
  }

  if (special != lastSp || shift != lastSh)
  {
    if (special)
    {
      if (shift) {
        //tft.fillScreen(BLACK);
        MakeKB_Button(Mobile_SymKeys);
      } else {
        //tft.fillScreen(BLACK);
        MakeKB_Button(Mobile_NumKeys);
      }
    }
    else
    {
      //tft.fillScreen(BLACK);
      MakeKB_Button(Mobile_KB);
      tft.setTextColor(BLACK, LIGHTGREY);
    }

    if (special) {                       //!#1" or AB or ab
      tft.setTextColor(BLACK, LIGHTGREY);
      tft.setCursor(15, 168);
      if (!shift)tft.print("1/2");
      if (shift)tft.print("2/2");
      tft.setCursor(19, 195);
      if (!shift)tft.print("ab");
      if (shift)tft.print("AB");
    } else {
      tft.setTextColor(BLACK, LIGHTGREY);
      tft.setCursor(14, 195);
      tft.print("!#1");
    }

    lastSh = shift;
    lastSp = special;
    lastSh = shift;
  }


  for (int y = 0; y < 3; y++)
  {
    int ShiftRight;
    if (special)
    {
      if (shift) {
        ShiftRight = 15 * pgm_read_byte(&(Mobile_SymKeys[y][0]));

      } else {
        ShiftRight = 15 * pgm_read_byte(&(Mobile_NumKeys[y][0]));

      }
    }
    else {
      ShiftRight = 15 * pgm_read_byte(&(Mobile_KB[y][0]));

    }
    for (int x = 3; x < 13; x++)
    {
      if (x >=  (special ? (shift ? pgm_read_byte(&(Mobile_SymKeys[y][1])) : pgm_read_byte(&(Mobile_NumKeys[y][1]))) : pgm_read_byte(&(Mobile_KB[y][1])) )) break;

      if (TouchButton(15 + (30 * (x - 3)) + ShiftRight, 100 + (30 * y), 20, 25)) // this will draw the button on the screen by so many pixels
      {
        if (bufIndex < (textLimit - 1))
        {
          delay(200);

          if (special)
          {
            if (shift) {
              textBuffer[bufIndex] = pgm_read_byte(&(Mobile_SymKeys[y][x]));
              //MakeKB_Button(Mobile_SymKeys);
            } else {
              textBuffer[bufIndex] = pgm_read_byte(&(Mobile_NumKeys[y][x]));
              //MakeKB_Button(Mobile_NumKeys);
            }
          }
          else {
            textBuffer[bufIndex] = (pgm_read_byte(&(Mobile_KB[y][x])) + (shift ? 0 : ('a' - 'A')));
            //MakeKB_Button(Mobile_KB);
          }
          bufIndex++;
        }
        break;
      }
    }
  }




  //Spacebar
  if (TouchButton(60, 190, 200, 25))
  {
    textBuffer[bufIndex++] = ' ';
    delay(200);
  }

  //BackSpace
  if (TouchButton(270, 160, 35, 25))
  {
    if ((bufIndex) > 0)
      bufIndex--;
    textBuffer[bufIndex] = 0;
    tft.setTextColor(GREEN, BLACK);
    tft.setCursor(15, 15);
    tft.print("                         ");
    delay(50);
  }

  // x exit
  if (TouchButton(300, 0, 15, 20))
  {
    delay(500);
    tft.fillScreen(BLACK);
    exitkeyboard = 1;
  }

  //Return
  if (TouchButton(270, 190, 35, 25))
  {
    Serial.println("textBuffer"); Serial.println(textBuffer);
    tft.setTextColor(GREEN, BLACK);
    tft.setCursor(15, 60);
    tft.print(F("                         "));
    tft.setCursor(15, 60);
    tft.print(textBuffer);
    //sonoffaddress[5] = "http://" + String(textBuffer);
    //buttontext[5] = String(textBuffer);

    while (bufIndex > 0)
    {
      bufIndex--;
      textBuffer[bufIndex] = 0;
    }

    tft.setTextColor(GREEN, BLACK);
    tft.setCursor(0, 15);
    tft.print(F("                         "));
    delay(500);
    tft.fillScreen(BLACK);
    exitkeyboard = 1;
  }
  //}
  tft.setTextColor(LIGHTGREY, BLACK);
  tft.setCursor(15, 15);
  tft.print(textBuffer);
  if ((millis() / 500) % 2) tft.print("_"); else  tft.print(" "); // blinking cursor
  

}










void drawButton(int x, int y, int w, int h)
{
  // grey
  tft.fillRoundRect(x - 3, y + 3, w, h, 3, BLACK); //Button Shading

  // white
  tft.fillRoundRect(x, y, w, h, 3, WHITE);// outter button color

  //red
  tft.fillRoundRect(x + 1, y + 1, w - 1 * 2, h - 1 * 2, 3, LIGHTGREY); //inner button color
}

















void MakeKB_Button(const char type[][13])
{
  tft.setTextSize(2);
  tft.setTextColor(BLACK);
  tft.fillRoundRect(5, 90, 310, 150, 4, GRAY);

  for (int y = 0; y < 3; y++)
  {
    int ShiftRight = 15 * pgm_read_byte(&(type[y][0]));
    for (int x = 3; x < 13; x++)
    {
      if (x >= pgm_read_byte(&(type[y][1]))) break;

      drawButton(15 + (30 * (x - 3)) + ShiftRight, 100 + (30 * y), 20, 25); // this will draw the button on the screen by so many pixels
      tft.setCursor(20 + (30 * (x - 3)) + ShiftRight, 105 + (30 * y));
      if (!shift) tft.print(char(tolower(pgm_read_byte(&(type[y][x])))));
      if (shift)tft.print(char(pgm_read_byte(&(type[y][x]))));
    }
  }
  //ShiftKey
  drawButton(13, 160, 39, 25);
  tft.setCursor(27, 168);
  tft.print('^');

  //Special Characters
  drawButton(13, 190, 39, 25);
  tft.setCursor(14, 195);
  tft.print("!#1");


  //BackSpace
  drawButton(270, 160, 35, 25);
  tft.setCursor(276, 165);
  tft.print(F("BS"));

  //Return
  drawButton(270, 190, 35, 25);
  tft.setCursor(276, 195);
  tft.print(F("RT"));

  //Spacebar
  drawButton(60, 190, 200, 25);
  tft.setCursor(105, 195);
  tft.print(F("SPACE BAR"));

  // x exit
  drawButton(300, 0, 15, 20);
  tft.setCursor(303, 3);
  tft.print(F("X"));
}




byte Touch_q_checkbox(int xx, int yy, int ww, int hh) {
  if (x > xx && x < xx + ww && y > yy && y < yy + hh) {
    delay(50);
    x = 0; y = 0;
    return 1;
  } else {
    return 0;
  }
}


byte TouchButton(int xx, int yy, int ww, int hh)
{
  //tft.getTouch(&x, &y);
  if (x > xx && x < xx + ww && y > yy && y < yy + hh) {
    tft.drawRoundRect(xx, yy, ww, hh, 4, GREEN);                // bit off visual touch
    tft.drawRoundRect(xx + 1, yy + 1, ww - 2, hh - 2, 4, GREEN); // bit off visual touch
    delay(50);
    tft.drawRoundRect(xx, yy, ww, hh, 4, BLACK);                // bit off visual touch
    tft.drawRoundRect(xx + 1, yy + 1, ww - 2, hh - 2, 4, BLACK); // bit off visual touch
    delay(50);
    tft.drawRoundRect(xx, yy, ww, hh, 4, WHITE);                // bit off visual touch
    tft.drawRoundRect(xx + 1, yy + 1, ww - 2, hh - 2, 4, LIGHTGREY); // bit off visual touch
    return 1;
  } else {
    return 0;
  }
}
