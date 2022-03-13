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

void settings_two_screen() {
  int remoteon;
  x = 0; y = 0;
  delay(250);
  tft.fillScreen(BLACK);


  TempLong = millis();  // store millis() counter in variable TempLong

  while (1 == 1) {                  // 1 wil always be 1   so forever

    if (tft.getTouch(&x, &y)) {
      //print touch xy position to serial monitor
      Serial.print(x);
      Serial.print(",");
      Serial.println(y);
      // tft.setTextColor(GREEN, BLACK);
      // tft.setCursor(120 , 30);
      // tft.print("X="); tft.print(x); tft.print(" ");
      // tft.setCursor(200, 30);
      // tft.print("Y="); tft.print(y); tft.print(" ");
      if (drawgreendot)tft.drawPixel(x, y, GREEN);
    }

    if ((millis() - TempLong)  > 60000) { // compare stored TempLong to current millis() counter
      tft.fillScreen(BLACK);
      break;                              // after 60 seconds inactivetie timer break while loop timeout
    }




    HTTPClient http;
http.setConnectTimeout(100);
    http.begin(sonoffaddress[0] + "/value"); //Specify the URL
    int httpCode = http.GET();                                                  //Make the request

    if (httpCode > 0) { //Check for the returning code

      String payload = http.getString();
      //Serial.println(httpCode);
      Serial.print(payload);
      if (payload.toInt() == 0) {
        Serial.print("UIT");
        remoteon = 0;
      }
      if (payload.toInt() == 1) {
        Serial.print("AAN");
        remoteon = 1;
      }


    }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
    delay(250);



    tft.setCursor(275, 210);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.print(60 - ((millis() - TempLong) / 1000)); tft.print(" ");

    tft.setTextSize(2);

    tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);

    tft.drawRoundRect(10, 85, 145, 70, 8, LIGHTGREY);
    tft.setCursor(25, 110); tft.print("NetWork IP");
    if (x > 10 && x < 150 && y > 60 && y < 140) {
      tft.drawRoundRect(10, 85, 145, 70, 8, GREEN);
      Serial.println("brightness button pressed");
      delay(500);
    }

    if ( remoteon == 0) {
      tft.drawRoundRect(10, 10, 145, 70, 8, GREEN);
      tft.setTextColor(GREEN, BLACK);
      tft.setCursor(30, 40); tft.print("remote off");
    } else {
      tft.drawRoundRect(10, 10, 145, 70, 8, LIGHTGREY);
      tft.setTextColor(LIGHTGREY, BLACK);
      tft.setCursor(30, 40); tft.print("remote off");
    }

    if (x > 10 && x < 150 && y > 10 && y < 80) {
      tft.drawRoundRect(10, 10, 145, 70, 8, GREEN);
      tft.setTextColor(GREEN, BLACK);
      tft.setCursor(30, 40); tft.print("remote off");

      HTTPClient http;
http.setConnectTimeout(100);
      http.begin(sonoffaddress[0] + "/LED=OFF"); //Specify the URL
      int httpCode = http.GET();                                                  //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }

      else {
        Serial.println("Error on HTTP request");
      }

      http.end(); //Free the resources


      x = 0; y = 0;
      delay(500);
    }


    if ( remoteon == 1) {
      tft.drawRoundRect(165, 10, 145, 70, 8, GREEN);
      tft.setTextColor(GREEN, BLACK);
     tft.setCursor(175, 40);  tft.print("remote on");
    } else {
      tft.drawRoundRect(165, 10, 145, 70, 8, LIGHTGREY);
      tft.setTextColor(LIGHTGREY, BLACK);
     tft.setCursor(175, 40);  tft.print("remote on");
    }
    if (x > 165 && x < 315 && y > 5 && y < 65) {
      tft.drawRoundRect(165, 10, 145, 70, 8, GREEN);
      tft.setTextColor(GREEN, BLACK);
      tft.setCursor(175, 40); tft.print("remote on");

      HTTPClient http;
http.setConnectTimeout(100);
      http.begin(sonoffaddress[0] + "/LED=ON"); //Specify the URL
      int httpCode = http.GET();                                                  //Make the request

      if (httpCode > 0) { //Check for the returning code

        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }

      else {
        Serial.println("Error on HTTP request");
      }

      http.end(); //Free the resources

      x = 0; y = 0;
      delay(500);

    }

    tft.drawRoundRect(165, 85, 145, 70, 8, LIGHTGREY);
    tft.setCursor(180, 110); tft.setTextColor(LIGHTGREY, BLACK); tft.print("Art's Mem.");
    if (x > 165 && x < 315 && y > 70 && y < 145) {
      tft.drawRoundRect(165, 85, 145, 70, 8, GREEN);
      tft.setCursor(180, 110); tft.setTextColor(GREEN, BLACK); tft.print("Art's Mem.");
      delay(500);
      ArtsMemory();
      delay(250);
      break;
    }

    tft.drawRoundRect(10, 165, 145, 70, 8, LIGHTGREY);
    tft.setCursor(70, 190); tft.print("<<");
    if (x > 10 && x < 150 && y > 165 && y < 230) {
      tft.setTextColor(GREEN, BLACK); tft.setCursor(70, 190); tft.print("<<");
      tft.drawRoundRect(10, 165, 145, 70, 8, GREEN);
      delay(500);
      settings_one_screen();
      break;
    }

    tft.drawRoundRect(165, 165, 145, 70, 8, LIGHTGREY);
    tft.setCursor(220, 190); tft.print(">>");
    if (x > 160 && x < 310 && y > 165 && y < 230) {
      tft.setTextColor(GREEN, BLACK); tft.setCursor(220, 190); tft.print(">>");
      tft.drawRoundRect(165, 165, 145, 70, 8, GREEN);
      delay(500);
      settings_three_screen();
      break;
    }



  }

}
