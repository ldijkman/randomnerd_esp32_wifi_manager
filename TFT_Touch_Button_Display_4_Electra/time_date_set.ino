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

void drawtimedatesetscreen() {
  byte uurselect = 1, minuutselect = 0, secondeselect = 0, dagselect = 0, maandselect = 0, jaarselect = 0;

  tft.fillScreen(BLACK);

  DateTime now = rtc.now();
  int uur = now.hour();
  int minuut = now.minute();
  int seconde = now.second();

  int dag = now.day();
  int maand = now.month();
  int jaar = now.year();

  while (1 == 1) {
    // tft ds3231 time setting code made by luberth dijkman https://www.youtube.com/watch?v=qNYT64CaLEI

    tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);
    x = 0; y = 0;
    tft.getTouch(&x, &y);

    tft.setTextColor(GREEN, BLACK);
    tft.setTextSize(1);
    tft.setCursor(15, 200);
    tft.println("NTP Time: " + timeClient.getFormattedTime());      // ntp

    tft.setCursor(15, 210);
    tft.print("Day ");
    tft.print(day(unix_epoch));                                     // ntp
    tft.print(" Month ");
    tft.print(month(unix_epoch));                                   // ntp
    tft.print(" Year ");
    tft.println(year(unix_epoch));                                  // ntp

    tft.setTextSize (4);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.setCursor(65, 25);
    if (uur < 10)tft.print(" ");
    if (uurselect) {
      tft.setTextColor (GREEN, BLACK);
    } else {
      tft.setTextColor (LIGHTGREY, BLACK);
    }
    tft.print(uur);
    tft.print(":");
    if (minuutselect) {
      tft.setTextColor (GREEN, BLACK);
    } else {
      tft.setTextColor (LIGHTGREY, BLACK);
    }
    if (minuut < 10)tft.print("0");
    tft.print(minuut);
    tft.print(":");
    if (secondeselect) {
      tft.setTextColor (GREEN, BLACK);
    } else {
      tft.setTextColor (LIGHTGREY, BLACK);
    }
    if (seconde < 10)tft.print("0");
    tft.print(seconde);

    tft.setTextSize (3);
    tft.setCursor(20, 80);
    if (dagselect) {
      tft.setTextColor(GREEN, BLACK);
    } else {
      tft.setTextColor (LIGHTGREY, BLACK);
    }
    tft.print(dag);
    tft.print(" ");
    //tft.print(maand);
    //tft.print("=");
    if (maandselect) {
      tft.setTextColor (GREEN, BLACK);
    } else {
      tft.setTextColor (LIGHTGREY, BLACK);
    }
    tft.print(monthName[maand - 1]);
    tft.print(" ");
    if (jaarselect) {
      tft.setTextColor (GREEN, BLACK);
    } else {
      tft.setTextColor (LIGHTGREY, BLACK);
    }
    tft.setCursor(240, 80);
    tft.print(jaar);
    //tft.print("   ");

    // time date +/- buttons set screen

    tft.setTextSize(4);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.setCursor(15, 130); tft.println(">>");
    tft.setCursor(110, 130); tft.println("-");
    tft.setCursor(190, 130); tft.println("+");
    tft.setTextSize(2);
    tft.setCursor(265, 135); tft.println("SET");
    tft.drawRoundRect(5, 120, 70, 50, 8, LIGHTGREY);
    tft.drawRoundRect(85, 120, 70, 50, 8, LIGHTGREY);
    tft.drawRoundRect(165, 120, 70, 50, 8, LIGHTGREY);
    tft.drawRoundRect(245, 120, 70, 50, 8, LIGHTGREY);


    //exit back button
    tft.setCursor(260 , 200);
    tft.println("BACK");
    tft.drawRoundRect(245, 180, 70, 50, 8, LIGHTGREY);

    //print touch xy position to serial monitor
    if (x != 0 && y != 0) {
      Serial.print(x);
      Serial.print(",");
      Serial.println(y);
    }

    if (uurselect) {
      if (x > 80 && x < 140 && y > 115 && y < 170) {
        tft.drawRoundRect(85, 120, 70, 50, 8, GREEN);
        delay(250);
        uur = uur - 1;
        if (uur < 0)uur = 23;
      }
      if (x > 160 && x < 235 && y > 115 && y < 170) {
        tft.drawRoundRect(165, 120, 70, 50, 8, GREEN);
        delay(250);
        uur = uur + 1;
        if (uur > 23)uur = 0;
      }
    }

    if (minuutselect) {
      if (x > 80 && x < 140 && y > 115 && y < 170) {
        tft.drawRoundRect(85, 120, 70, 50, 8, GREEN);
        delay(250);
        minuut = minuut - 1;
        if (minuut < 0)minuut = 59;
      }
      if (x > 160 && x < 235 && y > 115 && y < 170) {
        tft.drawRoundRect(165, 120, 70, 50, 8, GREEN);
        delay(250);
        minuut = minuut + 1;
        if (minuut > 59)minuut = 0;
      }
    }

    if (secondeselect) {
      if (x > 80 && x < 140 && y > 115 && y < 170) {
        tft.drawRoundRect(85, 120, 70, 50, 8, GREEN);
        delay(250);
        seconde = seconde - 1;
        if (seconde < 0)seconde = 59;
      }
      if (x > 160 && x < 235 && y > 115 && y < 170) {
        tft.drawRoundRect(165, 120, 70, 50, 8, GREEN);
        delay(250);
        seconde = seconde + 1;
        if (seconde > 59)seconde = 0;
      }
    }

    if (dagselect) {
      if (x > 80 && x < 140 && y > 115 && y < 170) {
        tft.drawRoundRect(85, 120, 70, 50, 8, GREEN);
        delay(250);
        dag = dag - 1;
        if (dag < 1)dag = 31;
      }
      if (x > 160 && x < 235 && y > 115 && y < 170) {
        tft.drawRoundRect(165, 120, 70, 50, 8, GREEN);
        delay(250);
        dag = dag + 1;
        if (dag > 31)dag = 1;
      }
    }

    if (maandselect) {
      if (x > 80 && x < 140 && y > 115 && y < 170) {
        tft.drawRoundRect(85, 120, 70, 50, 8, GREEN);
        delay(250);
        tft.fillRoundRect(45, 75, 190, 35, 1, BLACK);  // erase monthname
        maand = maand - 1;
        if (maand < 1)maand = 12;
      }
      if (x > 160 && x < 235 && y > 115 && y < 170) {
        tft.drawRoundRect(165, 120, 70, 50, 8, GREEN);
        delay(250);
        tft.fillRoundRect(45, 75, 190, 35, 1, BLACK);  // erase monthname
        maand = maand + 1;
        if (maand > 12)maand = 1;
      }
    }


    if (jaarselect) {
      if (x > 80 && x < 140 && y > 115 && y < 170) {
        tft.drawRoundRect(85, 120, 70, 50, 8, GREEN);
        delay(250);
        jaar = jaar - 1;
        if (jaar < 2020)jaar = 2020;
      }
      if (x > 160 && x < 235 && y > 115 && y < 170) {
        tft.drawRoundRect(165, 120, 70, 50, 8, GREEN);
        delay(250);
        jaar = jaar + 1;
        if (jaar > 2060)jaar = 2060;
      }
    }

    // >> next select
    if (x > 5 && x < 65 && y > 115 && y < 170) {    // >> next select
      tft.drawRoundRect(5, 120, 70, 50, 8, GREEN);
      delay(500);
      if (jaarselect == 1) {
        jaarselect = 0;
        uurselect = 1;
        out = 1;
      }

      if (maandselect == 1) {
        maandselect = 0;
        jaarselect = 1;
      }

      if (dagselect == 1) {
        dagselect = 0;
        maandselect = 1;
      }

      if (secondeselect == 1) {
        secondeselect = 0;
        dagselect = 1;
      }

      if (minuutselect == 1) {
        minuutselect = 0;
        secondeselect = 1;
      }

      if (uurselect == 1 && out == 0) {
        uurselect = 0;
        minuutselect = 1;
      }

    }
    out = 0;

    if (x > 245 && x < 315 && y > 115 && y < 170) {  // set button save to ds3231 en leave
      tft.drawRoundRect(245, 120, 70, 50, 8, GREEN);
      delay(250);
 //     rtc.adjust(DateTime(jaar, maand, dag, uur, minuut, seconde));
      delay(250);
      break;
    }

    if (x > 245 && x < 315 && y > 180 && y < 235) {  // back button exit  without save
      tft.drawRoundRect(245, 180, 70, 50, 8, GREEN);
      delay(250);
      delay(250);
      break;
    }



    // ntp2rtc button
    tft.setTextSize(1);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.setCursor(170 , 200);
    tft.println("NTP 2 RTC");
    tft.drawRoundRect(165, 180, 70, 50, 8, LIGHTGREY);
    if (x > 165 && x < 235 && y > 180 && y < 235) {  // ntp2rtc button and exit
      tft.drawRoundRect(165, 180, 70, 50, 8, GREEN);                                         // button is touched make it green
      tft.setTextColor (GREEN, BLACK);tft.setCursor(170 , 200);tft.println("NTP 2 RTC");
      delay(250);
      unix_epoch = timeClient.getEpochTime();    // Get Unix epoch time from the NTP server and set it to rtc
 //     rtc.adjust(DateTime(year(unix_epoch), month(unix_epoch), day(unix_epoch), hour(unix_epoch), minute(unix_epoch), second(unix_epoch)));
      delay(250);
      break;
    }


    if (x > 50 && x < 115 && y > 15 && y < 45) {
      uurselect = 1, minuutselect = 0, secondeselect = 0, dagselect = 0, maandselect = 0, jaarselect = 0;
    }
    if (x >  115 && x < 190 && y > 15 && y < 45) {
      uurselect = 0, minuutselect = 1, secondeselect = 0, dagselect = 0, maandselect = 0, jaarselect = 0;
    }
    if (x > 190 && x < 260 && y > 15 && y < 45) {
      uurselect = 0, minuutselect = 0, secondeselect = 1, dagselect = 0, maandselect = 0, jaarselect = 0;
    }

    if (x > 5 && x < 55 && y > 65 && y < 110) {
      uurselect = 0, minuutselect = 0, secondeselect = 0 , dagselect = 1, maandselect = 0, jaarselect = 0;
    }
    if (x > 55 && x < 230 && y > 65 && y < 110) {
      uurselect = 0, minuutselect = 0, secondeselect = 0, dagselect = 0, maandselect = 1, jaarselect = 0;
    }
    if (x > 230 && x < 315 && y > 65 && y < 110) {
      uurselect = 0, minuutselect = 0, secondeselect = 0, dagselect = 0, maandselect = 0, jaarselect = 1;
    }


  }
  // tft ds3231 time setting code made by luberth dijkman https://www.youtube.com/watch?v=qNYT64CaLEI

}

// please let me sleep 1
