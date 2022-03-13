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

void drawbrightnessscreen() {
  
  int oldx=0;

  tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);

  x = map(backgroundlightval, 5, 255, 35, 285 ) + 1; // i add 1 otherwise it goes down==do not no why
  y = 0;
  delay(250);
  tft.fillScreen(BLACK);
  tft.drawRoundRect(1, 1, 319, 239, 2, DARKGREY);
  tft.setTextColor(GREEN, BLACK);
  tft.setCursor(20 , 30);
  tft.print("Set backlight brightness");


  TempLong = millis();                    // store millis() counter in variable TempLong for starttime timeout

  while (1 == 1) {                        // the big while loop, 1 wil always be 1   so forever
    
    if (tft.getTouch(&x, &y)) {           //  gets x, y and only print to seial monitor i there is a touch  
      Serial.print(x);                    //  print touch xy position to serial monitor for debug
      Serial.print(",");
      Serial.println(y);
      // tft.setTextColor(GREEN, BLACK);                    // draw text to tft screen for debug
      // tft.setCursor(120 , 30);
      // tft.print("X="); tft.print(x); tft.print(" ");
      // tft.setCursor(200, 30);
      // tft.print("Y="); tft.print(y); tft.print(" ");
      if (drawgreendot)tft.drawPixel(x, y, GREEN);         // draw touch position pixel
    }
    
    if ((millis() - TempLong)  > 60000) {                 // compare stored TempLong to current millis() counter
      tft.fillScreen(BLACK);                              // if currentime - starttime > 60sec 
      break;                                              // after 60 seconds inactivetie timer break while loop timeout
    }

    tft.setCursor(275, 210);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.print(60 - ((millis() - TempLong) / 1000)); tft.print(" ");               // print countdown on screen

    tft.setTextColor(LIGHTGREY);
    tft.setTextSize(2);
    tft.setCursor(0, 10);

             

    tft.drawRoundRect(160 - (145 / 2), 170, 145, 60, 8, LIGHTGREY);               // draw buttons outline gray
    tft.setCursor(140, 190); tft.print("EXIT");                                   // draw exit button text gray
    if (x > 80 && x < 250 && y > 170 && y < 235) {                                // if touch in exit button 
      tft.drawRoundRect(160 - (145 / 2), 170, 145, 60, 8, GREEN);                 // make button outline green
      tft.setTextColor(GREEN, BLACK);tft.setCursor(140, 190); tft.print("EXIT");  // make button text green
      delay(500);                                                                 // delay .5 sec otherwise it goes to fast
      //should be something like wait for button released
      tft.fillScreen(BLACK);                                                      // erase screen
      x=0;y=0;
      break;                                                                      // break the big while forever loop = exit
    }
    tft.setTextColor(GREEN, BLACK);


    // yes ;-) i made my first slider without looking at code examples

    if (x <= 35)x = 35;                                               // set minimal x
    if (x >= 285)x = 285;                                             // set maximum x
    if (x != oldx) {                                                  // only draw slidebar and circle if x touch has changed, x not is xold
      tft.fillRoundRect(10, 110, 300, 50, 13, GREEN);
      tft.fillCircle(x, 135, 25, BLACK);
    } 
    
    oldx = x;                                                        // store x in oldx for next compare, should whe draw a slidebar

    backgroundlightval = x;                                          // touchval x between 35 and 285 
 
    backgroundlightval = map(backgroundlightval, 35, 285, 5, 255);   // scale x into a 5 to 255 for PWM output
    tft.setCursor(150, 55);
    tft.print(backgroundlightval);
    tft.print("  ");


    tft.setCursor(150, 80);
    //show it in procent                                             // scale backgroundlightval into procent, for %value on screen
    tft.print(map(backgroundlightval, 5, 255, 2, 100));              // 100/255*5 maybe 2% otherwise black screen = no visibility
    tft.print("%  ");

    if (backgroundlightval >= 255)backgroundlightval = 255;          // should not be needed
    if (backgroundlightval <= 5)backgroundlightval = 5;              // should not be needed
    
    ledcWrite(ledChannel, backgroundlightval);                       // output PWM for backlight LED brightness

  
  }          // end while 1==1 forever loop, go back to begin of loop

                                             // My Brain Goes Crazy, Please, Let me Sleep  https://www.youtube.com/watch?v=aXJhDltzYVQ
                                            // Mummy. Why does EveryBody has a Bum?!       https://www.youtube.com/watch?v=weUhBGA8mxo
                                            // Jami, Why does EveryBody has a Phone?!       http://jami.net
}
