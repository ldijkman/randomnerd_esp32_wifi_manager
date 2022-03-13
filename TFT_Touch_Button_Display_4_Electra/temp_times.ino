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


void printsettimes() {

  byte tempon0sel = 1, tempon1sel = 0, tempon2sel = 0;
  byte tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
  byte houron0sel = 0, houron1sel = 0, houron2sel = 0;
  byte houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
  byte minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
  byte minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;

  tft.fillScreen(BLACK);
  tft.drawRoundRect(1, 0, 319, 239, 2, DARKGREY);

  while (1 == 1) {

    tft.getTouch(&x, &y);
    //print touch xy position to serial monitor
    // if (x != 0 && y != 0) {
    //   Serial.print(x);
    //   Serial.print(",");
    //   Serial.println(y);
    // }

    tft.drawRoundRect(1, 0, 319, 239, 2, DARKGREY);


    /*
        tft.drawRoundRect(5, 190, 70, 45, 2, LIGHTGREY);      // boxdata extracted https://github.com/ImpulseAdventure/GUIslice-Builder
        tft.setCursor(25, 205); tft.print("SET");
        if (x > 5 && x < 70 && y > 190 && y < 190 + 45) {
          tft.drawRoundRect(5, 190, 70, 45, 2, GREEN);
          tft.setTextColor(GREEN, BLACK); tft.setCursor(25, 205); tft.print("SET");
          delay(500);
        }
    */

    tft.drawRoundRect(245, 190, 70, 45, 2, LIGHTGREY);      // boxdata extracted https://github.com/ImpulseAdventure/GUIslice-Builder
    tft.setCursor(260, 205); tft.print(" >> ");
    if (x > 245 && x < 325 && y > 190 && y < 190 + 45) {
      tft.drawRoundRect(245, 190, 70, 45, 2, GREEN);
      tft.setTextColor(GREEN, BLACK); tft.setCursor(260, 205); tft.print(" >> ");
      delay(500);
      x = 0; y = 0;
      break;
    }

    tft.drawLine(15, 71, 250, 71, LIGHTGREY);
    tft.drawLine(15, 127, 250, 127, LIGHTGREY);

    tft.setTextSize(4);
    tft.setCursor(110, 200); tft.print("-");
    tft.drawRoundRect(85, 190, 70, 45, 2, LIGHTGREY);
    tft.setCursor(190, 200); tft.print("+");
    tft.drawRoundRect(165, 190, 70, 45, 2, LIGHTGREY);

    tft.setTextColor(LIGHTGREY, BLACK);
    tft.setTextSize(2);
    tft.setCursor(5, 0);
    tft.println("Switch times Mon / Friday ");

    tft.setCursor(25, 25);
    tft.print("ON  "); if (HeatONhour[0] < 10)tft.print(" "); tft.print(HeatONhour[0], 0); tft.print(":"); if (HeatONminute[0] < 10)tft.print("0");
    tft.print(HeatONminute[0], 0); tft.print("   "); tft.print(tempON[0], 1); tft.print(char(247)); tft.print("C");

    tft.setCursor(25, 50);
    tft.print("OFF "); if (HeatOFFhour[0] < 10)tft.print(" "); tft.print(HeatOFFhour[0], 0); tft.print(":"); if (HeatOFFminute[0] < 10)tft.print("0");
    tft.print(HeatOFFminute[0], 0); tft.print("   "); tft.print(tempOFF[0], 1); tft.print(char(247)); tft.print("C");

    //line

    tft.setCursor(25, 80);
    tft.print("ON  "); if (HeatONhour[1] < 10)tft.print(" "); tft.print(HeatONhour[1], 0); tft.print(":"); if (HeatONminute[1] < 10)tft.print("0");
    tft.print(HeatONminute[1], 0); tft.print("   "); tft.print(tempON[1], 1); tft.print(char(247)); tft.print("C");

    tft.setCursor(25, 105);
    tft.print("OFF "); if (HeatOFFhour[1] < 10)tft.print(" "); tft.print(HeatOFFhour[1], 0); tft.print(":"); if (HeatOFFminute[1] < 10)tft.print("0");
    tft.print(HeatOFFminute[1], 0); tft.print("   "); tft.print(tempOFF[1], 1); tft.print(char(247)); tft.print("C");

    //line

    tft.setCursor(25, 135);
    tft.print("ON  "); if (HeatONhour[2] < 10)tft.print(" "); tft.print(HeatONhour[2], 0); tft.print(":"); if (HeatONminute[2] < 10)tft.print("0");
    tft.print(HeatONminute[2], 0); tft.print("   "); tft.print(tempON[2], 1); tft.print(char(247)); tft.print("C");

    tft.setCursor(25, 160);
    tft.print("OFF "); if (HeatOFFhour[2] < 10)tft.print(" "); tft.print(HeatOFFhour[2], 0); tft.print(":"); if (HeatOFFminute[2] < 10)tft.print("0");
    tft.print(HeatOFFminute[2], 0); tft.print("   "); tft.print(tempOFF[2], 1); tft.print(char(247)); tft.print("C");

    //////////////////////////////////////////////////////
    //houron10
    if (x > 50 && x < 100 && y > 15  && y < 35 ) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 1, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //houroff10
    if (x > 50 && x < 100 && y > 45 && y < 65) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 1, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //houron11
    if (x > 50 && x < 100 && y > 65  && y < 95 ) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 1, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //houroff11
    if (x > 50 && x < 100 && y > 95 && y < 125) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 1, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //houron12
    if (x > 50 && x < 100 && y > 125  && y < 155 ) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 1;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //houroff12
    if (x > 50 && x < 100 && y > 155 && y < 185) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 1;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //////////////////////////////////////////////////////
    //minuteon10
    if (x > 100 && x < 150 && y > 15  && y < 35 ) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 1, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //minuteoff10
    if (x > 100 && x < 150 && y > 45 && y < 65) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 1, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //minuteon11
    if (x > 100 && x < 150 && y > 65  && y < 95 ) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 1, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //minuteoff11
    if (x > 100 && x < 150 && y > 95 && y < 125) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 1, minuteoff2sel = 0;
    }
    //minuteon12
    if (x > 100 && x < 150 && y > 125  && y < 155 ) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 1;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //minuteoff12
    if (x > 100 && x < 150 && y > 155 && y < 185) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 1;
    }
    /////////////////////////////////////////////////////,
    //tempon10
    if (x > 155 && x < 245 && y > 15  && y < 35 ) {
      tempon0sel = 1, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //tempoff10
    if (x > 155 && x < 245 && y > 45 && y < 65) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 1, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //tempon11
    if (x > 155 && x < 245 && y > 65  && y < 95 ) {
      tempon0sel = 0, tempon1sel = 1, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //tempoff11
    if (x > 155 && x < 245 && y > 95 && y < 125) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 1, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //tempon12
    if (x > 155 && x < 245 && y > 125  && y < 155 ) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 1;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 0;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }
    //tempoff12
    if (x > 155 && x < 245 && y > 155 && y < 185) {
      tempon0sel = 0, tempon1sel = 0, tempon2sel = 0;
      tempoff0sel = 0, tempoff1sel = 0, tempoff2sel = 1;
      houron0sel = 0, houron1sel = 0, houron2sel = 0;
      houroff0sel = 0, houroff1sel = 0, houroff2sel = 0;
      minuteon0sel = 0, minuteon1sel = 0, minuteon2sel = 0;
      minuteoff0sel = 0, minuteoff1sel = 0, minuteoff2sel = 0;
    }



    //hour
    if (houron0sel) {
      tft.drawRoundRect(70, 22, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 22, 30,  20, 1, BLACK);
    }
    if (houroff0sel) {
      tft.drawRoundRect(70, 46, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 46, 30,  20, 1, BLACK);
    }
    if (houron1sel) {
      tft.drawRoundRect(70, 77, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 77, 30,  20, 1, BLACK);
    }
    if (houroff1sel) {
      tft.drawRoundRect(70, 101, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 101, 30,  20, 1, BLACK);
    }
    if (houron2sel) {
      tft.drawRoundRect(70, 131, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 131, 30,  20, 1, BLACK);
    }
    if (houroff2sel) {
      tft.drawRoundRect(70, 156, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 156, 30,  20, 1, BLACK);
    }




    //minute
    if (minuteon0sel) {
      tft.drawRoundRect(105, 22, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 22, 30,  20, 1, BLACK);
    }
    if (minuteoff0sel) {
      tft.drawRoundRect(105, 46, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 46, 30,  20, 1, BLACK);
    }
    if (minuteon1sel) {
      tft.drawRoundRect(105, 77, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 77, 30,  20, 1, BLACK);
    }
    if (minuteoff1sel) {
      tft.drawRoundRect(105, 101, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 101, 30,  20, 1, BLACK);
    }
    if (minuteon2sel) {
      tft.drawRoundRect(105, 131, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 131, 30,  20, 1, BLACK);
    }
    if (minuteoff2sel) {
      tft.drawRoundRect(105, 156, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 156, 30,  20, 1, BLACK);
    }


    //temp
    if (tempon0sel) {
      tft.drawRoundRect(155, 22, 95,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 22, 95,  20, 1, BLACK);
    }
    if (tempoff0sel) {
      tft.drawRoundRect(155, 46, 95,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 46, 95,  20, 1, BLACK);
    }
    if (tempon1sel) {
      tft.drawRoundRect(155, 77, 95,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 77, 95,  20, 1, BLACK);
    }
    if (tempoff1sel) {
      tft.drawRoundRect(155, 101, 95,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 101, 95,  20, 1, BLACK);
    }
    if (tempon2sel) {
      tft.drawRoundRect(155, 131, 95,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 131, 95,  20, 1, BLACK);
    }
    if (tempoff2sel) {
      tft.drawRoundRect(155, 156, 95,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 156, 95,  20, 1, BLACK);
    }






    //-button
    if (x > 75 && x < 150 && y > 190 && y < 240) {
      tft.setTextSize(4);
      tft.setTextColor(GREEN, BLACK);
      tft.setCursor(110, 200); tft.print("-");
      tft.drawRoundRect(85, 190, 70, 45,  2, GREEN);
      tft.setTextSize(2);
      tft.setTextColor(LIGHTGREY, BLACK);

      ///////////////////////////////////////////////////////////////
      if (houron0sel) {
        HeatONhour[0] = HeatONhour[0] - 1;
        if (HeatONhour[0] < 0)HeatONhour[0] = 23;
      }
      if (houroff0sel) {
        HeatOFFhour[0] = HeatOFFhour[0] - 1;
        if (HeatOFFhour[0] < 0)HeatOFFhour[0] = 23;
      }
      if (houron1sel) {
        HeatONhour[1] = HeatONhour[1] - 1;
        if (HeatONhour[1] < 0)HeatONhour[1] = 23;
      }
      if (houroff1sel) {
        HeatOFFhour[1] = HeatOFFhour[1] - 1;
        if (HeatOFFhour[1] < 0)HeatOFFhour[1] = 23;
      }
      if (houron2sel) {
        HeatONhour[2] = HeatONhour[2] - 1;
        if (HeatONhour[2] < 0)HeatONhour[2] = 23;
      }
      if (houroff2sel) {
        HeatOFFhour[2] = HeatOFFhour[2] - 1;
        if (HeatOFFhour[2] < 0)HeatOFFhour[2] = 23;
      }
      /////////////////////////////////////////////////////////
      if (minuteon0sel) {
        HeatONminute[0] = HeatONminute[0] - 1;
        if (HeatONminute[0] < 0)HeatONminute[0] = 59;
      }
      if (minuteoff0sel) {
        HeatOFFminute[0] = HeatOFFminute[0] - 1;
        if (HeatOFFminute[0] < 0)HeatOFFminute[0] = 59;
      }
      if (minuteon1sel) {
        HeatONminute[1] = HeatONminute[1] - 1;
        if (HeatONminute[1] < 0)HeatONminute[1] = 59;
      }
      if (minuteoff1sel) {
        HeatOFFminute[1] = HeatOFFminute[1] - 1;
        if (HeatOFFminute[1] < 0)HeatOFFminute[1] = 59;
      }
      if (minuteon2sel) {
        HeatONminute[2] = HeatONminute[2] - 1;
        if (HeatONminute[2] < 0)HeatONminute[2] = 59;
      }
      if (minuteoff2sel) {
        HeatOFFminute[2] = HeatOFFminute[2] - 1;
        if (HeatOFFminute[2] < 0)HeatOFFminute[2] = 59;
      }
      /////////////////////////////////////////////////////////
      if (tempon0sel) {
        tempON[0] = tempON[0] - 0.1;
        if (tempON[0] < 10)tempON[0] = 35;
      }
      if (tempoff0sel) {
        tempOFF[0] = tempOFF[0] - 0.1;
        if (tempOFF[0] < 10)tempOFF[0] = 35;
      }
      if (tempon1sel) {
        tempON[1] = tempON[1] - 0.1;
        if (tempON[1] < 10)tempON[1] = 35;
      }
      if (tempoff1sel) {
        tempOFF[1] = tempOFF[1] - 0.1;
        if (tempOFF[1] < 10)tempOFF[1] = 35;
      }
      if (tempon2sel) {
        tempON[2] = tempON[2] - 0.1;
        if (tempON[2] < 10)tempON[2] = 35;
      }
      if (tempoff2sel) {
        tempOFF[2] = tempOFF[2] - 0.1;
        if (tempOFF[2] < 10)tempOFF[2] = 35;
      }
      delay(10);
    }





    //+button
    if (x > 160 && x < 230 && y > 190 && y < 240) {
      tft.setTextSize(4);
      tft.setTextColor(GREEN, BLACK);
      tft.setCursor(190, 200); tft.print("+");
      tft.drawRoundRect(165, 190, 70, 45, 2, GREEN);
      tft.setTextSize(2);
      tft.setTextColor(LIGHTGREY, BLACK);

      ///////////////////////////////////////////////////////////////
      if (houron0sel) {
        HeatONhour[0] = HeatONhour[0] + 1;
        if (HeatONhour[0] > 23 )HeatONhour[0] = 23;
      }
      if (houroff0sel) {
        HeatOFFhour[0] = HeatOFFhour[0] + 1;
        if (HeatOFFhour[0] > 23 )HeatOFFhour[0] = 23;
      }
      if (houron1sel) {
        HeatONhour[1] = HeatONhour[1] + 1;
        if (HeatONhour[1] > 23 )HeatONhour[1] = 23;
      }
      if (houroff1sel) {
        HeatOFFhour[1] = HeatOFFhour[1] + 1;
        if (HeatOFFhour[1] > 23)HeatOFFhour[1] = 23;
      }
      if (houron2sel) {
        HeatONhour[2] = HeatONhour[2] + 1;
        if (HeatONhour[2] > 23 )HeatONhour[2] = 23;
      }
      if (houroff2sel) {
        HeatOFFhour[2] = HeatOFFhour[2] + 1;
        if (HeatOFFhour[2] > 23 )HeatOFFhour[2] = 23;
      }
      /////////////////////////////////////////////////////////
      if (minuteon0sel) {
        HeatONminute[0] = HeatONminute[0] + 1;
        if (HeatONminute[0] > 59 )HeatONminute[0] = 0;
      }
      if (minuteoff0sel) {
        HeatOFFminute[0] = HeatOFFminute[0] + 1;
        if (HeatOFFminute[0] > 59 )HeatOFFminute[0] = 0;
      }
      if (minuteon1sel) {
        HeatONminute[1] = HeatONminute[1] + 1;
        if (HeatONminute[1] > 59 )HeatONminute[1] = 0;
      }
      if (minuteoff1sel) {
        HeatOFFminute[1] = HeatOFFminute[1] + 1;
        if (HeatOFFminute[1] > 59 )HeatOFFminute[1] = 0;
      }
      if (minuteon2sel) {
        HeatONminute[2] = HeatONminute[2] + 1;
        if (HeatONminute[2] > 59 )HeatONminute[2] = 0;
      }
      if (minuteoff2sel) {
        HeatOFFminute[2] = HeatOFFminute[2] + 1;
        if (HeatOFFminute[2] > 59 )HeatOFFminute[2] = 0;
      }
      /////////////////////////////////////////////////////////


      if (tempon0sel) {
        tempON[0] = tempON[0] + 0.1;
        if (tempON[0] > 35)tempON[0] = 10;
      }
      if (tempoff0sel) {
        tempOFF[0] = tempOFF[0] + 0.1;
        if (tempOFF[0] > 35)tempOFF[0] = 10;
      }

      if (tempon1sel) {
        tempON[1] = tempON[1] + 0.1;
        if (tempON[1] > 35)tempON[1] = 10;
      }
      if (tempoff1sel) {
        tempOFF[1] = tempOFF[1] + 0.1;
        if (tempOFF[1] > 35)tempOFF[1] = 10;
      }

      if (tempon2sel) {
        tempON[2] = tempON[2] + 0.1;
        if (tempON[2] > 35)tempON[2] = 10;
      }
      if (tempoff2sel) {
        tempOFF[2] = tempOFF[2] + 0.1;
        if (tempOFF[2] > 35)tempOFF[2] = 10;
      }
      delay(10);
    }
    x = 0; y = 0;
  }












  /*
    for (X = 0; X <= 2; X++) {
    tft.println(X);
    tft.print("ON  ");
    tft.print(HeatONhour[X]);
    tft.print(":");
    if (HeatONminute[X] < 10)tft.print("0"); // makes 01 02 ... 09 10 minutes
    tft.print(HeatONminute[X]);
    tft.print("   ");
    tft.print(tempON[X]);
    tft.print(char(247)); //degree sign
    tft.print("C");

    tft.println(" ");
    tft.print("OFF ");
    tft.print(HeatOFFhour[X]);
    tft.print(":");
    if (HeatOFFminute[X] < 10)tft.print("0"); // makes 01 02 ... 09 10 minutes
    tft.print(HeatOFFminute[X]);
    tft.print("   ");
    tft.print(tempOFF[X]);
    tft.print(char(247)); //degree sign
    tft.print("C");
    tft.println(" ");

    }

    waitfortouchanywhere();
  */






  byte tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
  byte tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
  byte houron10sel = 0, houron11sel = 0, houron12sel = 0;
  byte houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
  byte minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
  byte minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;

  tft.fillScreen(BLACK);


  while (1 == 1) {



    tft.getTouch(&x, &y);
    //print touch xy position to serial monitor
    //if (x != 0 && y != 0) {
    //  Serial.print(x);
    //  Serial.print(",");
    //  Serial.println(y);
    //}

    tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);


    /*
        tft.drawRoundRect(5, 190, 70, 45, 2, LIGHTGREY);      // boxdata extracted https://github.com/ImpulseAdventure/GUIslice-Builder
        tft.setCursor(25, 205); tft.print("SET");
        if (x > 5 && x < 70 && y > 190 && y < 190 + 45) {
          tft.drawRoundRect(5, 190, 70, 45, 2, GREEN);
          tft.setTextColor(GREEN, BLACK); tft.setCursor(25, 205); tft.print("SET");
          delay(500);
        }
    */

    tft.drawRoundRect(245, 190, 70, 45, 2, LIGHTGREY);      // boxdata extracted https://github.com/ImpulseAdventure/GUIslice-Builder
    tft.setCursor(260, 205); tft.print("EXIT");
    if (x > 245 && x < 325 && y > 190 && y < 190 + 45) {
      tft.drawRoundRect(245, 190, 70, 45, 2, GREEN);
      tft.setTextColor(GREEN, BLACK); tft.setCursor(260, 205); tft.print("EXIT");
      delay(500);
      x = 0; y = 0;
      break;
    }

    tft.drawLine(15, 71, 250, 71, LIGHTGREY);
    tft.drawLine(15, 127, 250, 127, LIGHTGREY);

    tft.setTextSize(4);
    tft.setCursor(110, 200); tft.print("-");
    tft.drawRoundRect(85, 190, 70, 45, 2, LIGHTGREY);
    tft.setCursor(190, 200); tft.print("+");
    tft.drawRoundRect(165, 190, 70, 45, 2, LIGHTGREY);

    tft.setTextColor(LIGHTGREY, BLACK);
    tft.setTextSize(2);
    tft.setCursor(5, 0);
    tft.println("Switch times Sat / Sunday ");

    tft.setCursor(25, 25);
    tft.print("ON  "); if (HeatONhour[10] < 10)tft.print(" "); tft.print(HeatONhour[10], 0); tft.print(":"); if (HeatONminute[10] < 10)tft.print("0");
    tft.print(HeatONminute[10], 0); tft.print("   "); tft.print(tempON[10], 1); tft.print(char(247)); tft.print("C");

    tft.setCursor(25, 50);
    tft.print("OFF "); if (HeatOFFhour[10] < 10)tft.print(" "); tft.print(HeatOFFhour[10], 0); tft.print(":"); if (HeatOFFminute[10] < 10)tft.print("0");
    tft.print(HeatOFFminute[10], 0); tft.print("   "); tft.print(tempOFF[10], 1); tft.print(char(247)); tft.print("C");

    //line

    tft.setCursor(25, 80);
    tft.print("ON  "); if (HeatONhour[11] < 10)tft.print(" "); tft.print(HeatONhour[11], 0); tft.print(":"); if (HeatONminute[11] < 10)tft.print("0");
    tft.print(HeatONminute[11], 0); tft.print("   "); tft.print(tempON[11], 1); tft.print(char(247)); tft.print("C");

    tft.setCursor(25, 105);
    tft.print("OFF "); if (HeatOFFhour[11] < 10)tft.print(" "); tft.print(HeatOFFhour[11], 0); tft.print(":"); if (HeatOFFminute[11] < 10)tft.print("0");
    tft.print(HeatOFFminute[11], 0); tft.print("   "); tft.print(tempOFF[11], 1); tft.print(char(247)); tft.print("C");

    //line

    tft.setCursor(25, 135);
    tft.print("ON  "); if (HeatONhour[12] < 10)tft.print(" "); tft.print(HeatONhour[12], 0); tft.print(":"); if (HeatONminute[12] < 10)tft.print("0");
    tft.print(HeatONminute[12], 0); tft.print("   "); tft.print(tempON[12], 1); tft.print(char(247)); tft.print("C");

    tft.setCursor(25, 160);
    tft.print("OFF "); if (HeatOFFhour[12] < 10)tft.print(" "); tft.print(HeatOFFhour[12], 0); tft.print(":"); if (HeatOFFminute[12] < 10)tft.print("0");
    tft.print(HeatOFFminute[12], 0); tft.print("   "); tft.print(tempOFF[12], 1); tft.print(char(247)); tft.print("C");

    //////////////////////////////////////////////////////
    //houron10
    if (x > 50 && x < 100 && y > 15  && y < 35 ) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 1, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //houroff10
    if (x > 50 && x < 100 && y > 45 && y < 65) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 1, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //houron11
    if (x > 50 && x < 100 && y > 65  && y < 95 ) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 1, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //houroff11
    if (x > 50 && x < 100 && y > 95 && y < 125) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 1, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //houron12
    if (x > 50 && x < 100 && y > 125  && y < 155 ) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 1;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //houroff12
    if (x > 50 && x < 100 && y > 155 && y < 185) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 1;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //////////////////////////////////////////////////////
    //minuteon10
    if (x > 100 && x < 150 && y > 15  && y < 35 ) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 1, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //minuteoff10
    if (x > 100 && x < 150 && y > 45 && y < 65) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 1, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //minuteon11
    if (x > 100 && x < 150 && y > 65  && y < 95 ) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 1, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //minuteoff11
    if (x > 100 && x < 150 && y > 95 && y < 125) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 1, minuteoff12sel = 0;
    }
    //minuteon12
    if (x > 100 && x < 150 && y > 125  && y < 155 ) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 1;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //minuteoff12
    if (x > 100 && x < 150 && y > 155 && y < 185) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 1;
    }
    /////////////////////////////////////////////////////,
    //tempon10
    if (x > 155 && x < 245 && y > 15  && y < 35 ) {
      tempon10sel = 1, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //tempoff10
    if (x > 155 && x < 245 && y > 45 && y < 65) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 1, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //tempon11
    if (x > 155 && x < 245 && y > 65  && y < 95 ) {
      tempon10sel = 0, tempon11sel = 1, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //tempoff11
    if (x > 155 && x < 245 && y > 95 && y < 125) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 1, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //tempon12
    if (x > 155 && x < 245 && y > 125  && y < 155 ) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 1;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 0;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }
    //tempoff12
    if (x > 155 && x < 245 && y > 155 && y < 185) {
      tempon10sel = 0, tempon11sel = 0, tempon12sel = 0;
      tempoff10sel = 0, tempoff11sel = 0, tempoff12sel = 1;
      houron10sel = 0, houron11sel = 0, houron12sel = 0;
      houroff10sel = 0, houroff11sel = 0, houroff12sel = 0;
      minuteon10sel = 0, minuteon11sel = 0, minuteon12sel = 0;
      minuteoff10sel = 0, minuteoff11sel = 0, minuteoff12sel = 0;
    }



    //hour
    if (houron10sel) {
      tft.drawRoundRect(70, 22, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 22, 30,  20, 1, BLACK);
    }
    if (houroff10sel) {
      tft.drawRoundRect(70, 46, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 46, 30,  20, 1, BLACK);
    }
    if (houron11sel) {
      tft.drawRoundRect(70, 77, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 77, 30,  20, 1, BLACK);
    }
    if (houroff11sel) {
      tft.drawRoundRect(70, 101, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 101, 30,  20, 1, BLACK);
    }
    if (houron12sel) {
      tft.drawRoundRect(70, 131, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 131, 30,  20, 1, BLACK);
    }
    if (houroff12sel) {
      tft.drawRoundRect(70, 156, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(70, 156, 30,  20, 1, BLACK);
    }




    //minute
    if (minuteon10sel) {
      tft.drawRoundRect(105, 22, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 22, 30,  20, 1, BLACK);
    }
    if (minuteoff10sel) {
      tft.drawRoundRect(105, 46, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 46, 30,  20, 1, BLACK);
    }
    if (minuteon11sel) {
      tft.drawRoundRect(105, 77, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 77, 30,  20, 1, BLACK);
    }
    if (minuteoff11sel) {
      tft.drawRoundRect(105, 101, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 101, 30,  20, 1, BLACK);
    }
    if (minuteon12sel) {
      tft.drawRoundRect(105, 131, 30,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 131, 30,  20, 1, BLACK);
    }
    if (minuteoff12sel) {
      tft.drawRoundRect(105, 156, 30,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(105, 156, 30,  20, 1, BLACK);
    }


    //temp
    if (tempon10sel) {
      tft.drawRoundRect(155, 22, 95,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 22, 95,  20, 1, BLACK);
    }
    if (tempoff10sel) {
      tft.drawRoundRect(155, 46, 95,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 46, 95,  20, 1, BLACK);
    }
    if (tempon11sel) {
      tft.drawRoundRect(155, 77, 95,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 77, 95,  20, 1, BLACK);
    }
    if (tempoff11sel) {
      tft.drawRoundRect(155, 101, 95,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 101, 95,  20, 1, BLACK);
    }
    if (tempon12sel) {
      tft.drawRoundRect(155, 131, 95,   20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 131, 95,  20, 1, BLACK);
    }
    if (tempoff12sel) {
      tft.drawRoundRect(155, 156, 95,  20, 1, GREEN);
    } else {
      tft.drawRoundRect(155, 156, 95,  20, 1, BLACK);
    }






    //-button
    if (x > 75 && x < 150 && y > 190 && y < 240) {
      tft.setTextSize(4);
      tft.setTextColor(GREEN, BLACK);
      tft.setCursor(110, 200); tft.print("-");
      tft.drawRoundRect(85, 190, 70, 45, 2, GREEN);
      tft.setTextSize(2);
      tft.setTextColor(LIGHTGREY, BLACK);


      ///////////////////////////////////////////////////////////////
      if (houron10sel) {
        HeatONhour[10] = HeatONhour[10] - 1;
        if (HeatONhour[10] < 0)HeatONhour[10] = 23;
      }
      if (houroff10sel) {
        HeatOFFhour[10] = HeatOFFhour[10] - 1;
        if (HeatOFFhour[10] < 0)HeatOFFhour[10] = 23;
      }
      if (houron11sel) {
        HeatONhour[11] = HeatONhour[11] - 1;
        if (HeatONhour[11] < 0)HeatONhour[11] = 23;
      }
      if (houroff11sel) {
        HeatOFFhour[11] = HeatOFFhour[11] - 1;
        if (HeatOFFhour[11] < 0)HeatOFFhour[11] = 23;
      }
      if (houron12sel) {
        HeatONhour[12] = HeatONhour[12] - 1;
        if (HeatONhour[12] < 0)HeatONhour[12] = 23;
      }
      if (houroff12sel) {
        HeatOFFhour[12] = HeatOFFhour[12] - 1;
        if (HeatOFFhour[12] < 0)HeatOFFhour[12] = 23;
      }
      /////////////////////////////////////////////////////////
      if (minuteon10sel) {
        HeatONminute[10] = HeatONminute[10] - 1;
        if (HeatONminute[10] < 0)HeatONminute[10] = 59;
      }
      if (minuteoff10sel) {
        HeatOFFminute[10] = HeatOFFminute[10] - 1;
        if (HeatOFFminute[10] < 0)HeatOFFminute[10] = 59;
      }
      if (minuteon11sel) {
        HeatONminute[11] = HeatONminute[11] - 1;
        if (HeatONminute[11] < 0)HeatONminute[11] = 59;
      }
      if (minuteoff11sel) {
        HeatOFFminute[11] = HeatOFFminute[11] - 1;
        if (HeatOFFminute[11] < 0)HeatOFFminute[11] = 59;
      }
      if (minuteon12sel) {
        HeatONminute[12] = HeatONminute[12] - 1;
        if (HeatONminute[12] < 0)HeatONminute[12] = 59;
      }
      if (minuteoff12sel) {
        HeatOFFminute[12] = HeatOFFminute[12] - 1;
        if (HeatOFFminute[12] < 0)HeatOFFminute[12] = 59;
      }
      /////////////////////////////////////////////////////////
      if (tempon10sel) {
        tempON[10] = tempON[10] - 0.1;
        if (tempON[10] < 10)tempON[10] = 35;
      }
      if (tempoff10sel) {
        tempOFF[10] = tempOFF[10] - 0.1;
        if (tempOFF[10] < 10)tempOFF[10] = 35;
      }
      if (tempon11sel) {
        tempON[11] = tempON[11] - 0.1;
        if (tempON[11] < 10)tempON[11] = 35;
      }
      if (tempoff11sel) {
        tempOFF[11] = tempOFF[11] - 0.1;
        if (tempOFF[11] < 10)tempOFF[11] = 35;
      }
      if (tempon12sel) {
        tempON[12] = tempON[12] - 0.1;
        if (tempON[12] < 10)tempON[12] = 35;
      }
      if (tempoff12sel) {
        tempOFF[12] = tempOFF[12] - 0.1;
        if (tempOFF[12] < 10)tempOFF[12] = 35;
      }
      delay(20);
    }





    //+button
    if (x > 160 && x < 230 && y > 190 && y < 240) {
      tft.setTextSize(4);
      tft.setTextColor(GREEN, BLACK);
      tft.setCursor(190, 200); tft.print("+");
      tft.drawRoundRect(165, 190, 70, 45, 2, GREEN);
      tft.setTextSize(2);
      tft.setTextColor(LIGHTGREY, BLACK);


      ///////////////////////////////////////////////////////////////
      if (houron10sel) {
        HeatONhour[10] = HeatONhour[10] + 1;
        if (HeatONhour[10] > 23 )HeatONhour[10] = 23;
      }
      if (houroff10sel) {
        HeatOFFhour[10] = HeatOFFhour[10] + 1;
        if (HeatOFFhour[10] > 23 )HeatOFFhour[10] = 23;
      }
      if (houron11sel) {
        HeatONhour[11] = HeatONhour[11] + 1;
        if (HeatONhour[11] > 23 )HeatONhour[11] = 23;
      }
      if (houroff11sel) {
        HeatOFFhour[11] = HeatOFFhour[11] + 1;
        if (HeatOFFhour[11] > 23)HeatOFFhour[11] = 23;
      }
      if (houron12sel) {
        HeatONhour[12] = HeatONhour[12] + 1;
        if (HeatONhour[12] > 23 )HeatONhour[12] = 23;
      }
      if (houroff12sel) {
        HeatOFFhour[12] = HeatOFFhour[12] + 1;
        if (HeatOFFhour[12] > 23 )HeatOFFhour[12] = 23;
      }
      /////////////////////////////////////////////////////////
      if (minuteon10sel) {
        HeatONminute[10] = HeatONminute[10] + 1;
        if (HeatONminute[10] > 59 )HeatONminute[10] = 0;
      }
      if (minuteoff10sel) {
        HeatOFFminute[10] = HeatOFFminute[10] + 1;
        if (HeatOFFminute[10] > 59 )HeatOFFminute[10] = 0;
      }
      if (minuteon11sel) {
        HeatONminute[11] = HeatONminute[11] + 1;
        if (HeatONminute[11] > 59 )HeatONminute[11] = 0;
      }
      if (minuteoff11sel) {
        HeatOFFminute[11] = HeatOFFminute[11] + 1;
        if (HeatOFFminute[11] > 59 )HeatOFFminute[11] = 0;
      }
      if (minuteon12sel) {
        HeatONminute[12] = HeatONminute[12] + 1;
        if (HeatONminute[12] > 59 )HeatONminute[12] = 0;
      }
      if (minuteoff12sel) {
        HeatOFFminute[12] = HeatOFFminute[12] + 1;
        if (HeatOFFminute[12] > 59 )HeatOFFminute[12] = 0;
      }
      /////////////////////////////////////////////////////////


      if (tempon10sel) {
        tempON[10] = tempON[10] + 0.1;
        if (tempON[10] > 35)tempON[10] = 10;
      }
      if (tempoff10sel) {
        tempOFF[10] = tempOFF[10] + 0.1;
        if (tempOFF[10] > 35)tempOFF[10] = 10;
      }

      if (tempon11sel) {
        tempON[11] = tempON[11] + 0.1;
        if (tempON[11] > 35)tempON[11] = 10;
      }
      if (tempoff11sel) {
        tempOFF[11] = tempOFF[11] + 0.1;
        if (tempOFF[11] > 35)tempOFF[11] = 10;
      }

      if (tempon12sel) {
        tempON[12] = tempON[12] + 0.1;
        if (tempON[12] > 35)tempON[12] = 10;
      }
      if (tempoff12sel) {
        tempOFF[12] = tempOFF[12] + 0.1;
        if (tempOFF[12] > 35)tempOFF[12] = 10;
      }
      delay(20);
    }





    /*
      tft.setTextColor(LIGHTGREY);
      tft.setTextSize(2);
      tft.setCursor(5, 0);
      tft.println("Switch times Sat / Sunday ");
      tft.setTextSize(2);
      for (X = 10; X <= 12; X++) {
       tft.println(" ");
       tft.print("ON  ");
       tft.print(HeatONhour[X]);
       tft.print(":");
       if (HeatONminute[X] < 10)tft.print("0"); // makes 01 02 ... 09 10 minutes
       tft.print(HeatONminute[X]);
       tft.print("   ");
       tft.print(tempON[X]);
       tft.print(char(247)); //degree sign
       tft.print("C");

       tft.println(" ");
       tft.print("OFF ");
       tft.print(HeatOFFhour[X]);
       tft.print(":");
       if (HeatOFFminute[X] < 10)tft.print("0"); // makes 01 02 ... 09 10 minutes
       tft.print(HeatOFFminute[X]);
       tft.print("   ");
       tft.print(tempOFF[X]);
       tft.print(char(247)); //degree sign
       tft.print("C");
       tft.println(" ");

      }*/
    x = 0; y = 0;
  }


}

//ver 0
