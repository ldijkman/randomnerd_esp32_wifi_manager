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
/*
  String buttontext[0] = "Sonoff 1";
  String buttontext[1] = "Sonoff 2";
  String buttontext[2] = "Sonoff 3";
  String buttontext[3] = "Sonoff 4";
  String buttontext[4] = "Sonoff 5";
  String  buttontext[5] = "Sonoff 6";
  String button7text = "<<";
  String button8text = ">>";
*/
void settings_three_screen() {
  x = 0; y = 0;
  delay(250);
  tft.fillScreen(BLACK);

  long slowdown;



  TempLong = millis();  // store millis() counter in variable TempLong for screen timeout

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
      TempLong = millis();  // reset when touch timeout timer millis() counter in variable TempLong
    }

    if ((millis() - TempLong)  > 60000) { // compare stored TempLong to current millis() counter  screen timeout
      tft.fillScreen(BLACK);
      break;                              // after 60 seconds inactivetie timer break while loop timeout
    }



    if ((millis() - slowdown)  > 1000) {  // ckeck status of sonoff switches every second
      for (int i = 0; i < 6; i++) {
        slowdown = millis();

        Serial.println(i);
        HTTPClient http;

        http.begin(sonoffaddress[i] + "/status");                            // Specify the URL
        //Serial.println(sonoffaddress[i] + "/value");
        http.setConnectTimeout(100);
        int httpCode = http.GET();                                         // Make the request
        sonoffstatus[i] = 2;                                               // if not changed status is 2 = error
        if (httpCode > 0) {                                                // Check for the returning code

          String payload = http.getString();
          payload.trim(); // trim the white space off the string:  other wise the 0 or 1 compare does not work
          //Serial.println(httpCode);
          Serial.print("payload >"); Serial.print(payload); Serial.print("<"); Serial.println("-");
          //     Serial.println(payload.toInt());
          if (payload == "0") {
            //   Serial.println("UIT");
            sonoffstatus[i] = 0;
          }
          if (payload == "1") {
            //  Serial.println("AAN");
            sonoffstatus[i] = 1;
          }

          payload = "-";

        }
        else {
          Serial.println("Error on HTTP request");

        }

        http.end(); //Free the resources
        // Serial.print("sonoffstatus[0]=");Serial.println(sonoffstatus[0]);
        // Serial.print("sonoffstatus[1]=");Serial.println(sonoffstatus[1]);
        // Serial.print("sonoffstatus[2]=");Serial.println(sonoffstatus[2]);
        // Serial.print("sonoffstatus[3]=");Serial.println(sonoffstatus[3]);
        // Serial.print("sonoffstatus[4]=");Serial.println(sonoffstatus[4]);
        //  Serial.print("sonoffstatus[5]=");Serial.println(sonoffstatus[5]);
        // Serial.println("");Serial.println("");

      } // end for i

    } // end slowdown sonoff status check to every second




    tft.setCursor(275, 210);
    tft.setTextColor (LIGHTGREY, BLACK);
    tft.print(60 - ((millis() - TempLong) / 1000)); tft.print(" ");             // print screen time out counter

    tft.setTextSize(2);




    if ( sonoffstatus[0] == 0) button1(LIGHTGREY, buttontext[0]);
    if ( sonoffstatus[0] == 1) button1(GREEN, buttontext[0]);
    if ( sonoffstatus[0] == 2) button1(RED, buttontext[0]);
    if ( editsettingsthree == 1) {
      button1(PURPLE, buttontext[0]);
      button9(PURPLE, button9text);
    }
    if (button1touch()) {
      if ( editsettingsthree == 1) {
        editbutton(1);
      } else {
        sendit(0);                          // sendit does toggle sonoff switch on url address stringarray 0
      }
      delay(250);
    }



    if ( sonoffstatus[1] == 0) button2(LIGHTGREY, buttontext[1]);
    if ( sonoffstatus[1] == 1) button2(GREEN, buttontext[1]);
    if ( sonoffstatus[1] == 2) button2(RED, buttontext[1]);
    if ( editsettingsthree == 1) {
      button2(PURPLE, buttontext[1]);
      button9(PURPLE, button9text);
    }
    if (button2touch()) {
      if ( editsettingsthree == 1) {
        editbutton(2);
      } else {
        sendit(1);                           // sendit does toggle sonoff switch on url address stringarray 1
      }
      delay(250);
    }





    if ( sonoffstatus[2] == 0) button3(LIGHTGREY, buttontext[2]);
    if ( sonoffstatus[2] == 1) button3(GREEN, buttontext[2]);
    if ( sonoffstatus[2] == 2) button3(RED, buttontext[2]);
    if ( editsettingsthree == 1) {
      button3(PURPLE, buttontext[2]);
      button9(PURPLE, button9text);
    }
    if (button3touch()) {
      if ( editsettingsthree == 1) {
        editbutton(3);
      } else {
        sendit(2);                            // sendit does toggle sonoff switch on url address stringarray 2
      }
      delay(250);
    }



    if ( sonoffstatus[3] == 0) button4(LIGHTGREY, buttontext[3]);
    if ( sonoffstatus[3] == 1) button4(GREEN, buttontext[3]);
    if ( sonoffstatus[3] == 2) button4(RED, buttontext[3]);
    if ( editsettingsthree == 1) {
      button4(PURPLE, buttontext[3]);
      button9(PURPLE, button9text);
    }
    if (button4touch()) {
      if ( editsettingsthree == 1) {
        editbutton(4);
      } else {
        sendit(3);                           // sendit does toggle sonoff switch on url address stringarray 3
      }
      delay(250);
    }


    if ( sonoffstatus[4] == 0) button5(LIGHTGREY, buttontext[4]);
    if ( sonoffstatus[4] == 1) button5(GREEN, buttontext[4]);
    if ( sonoffstatus[4] == 2) button5(RED, buttontext[4]);
    if ( editsettingsthree == 1) {
      button5(PURPLE, buttontext[4]);
      button9(PURPLE, button9text);
    }
    if (button5touch()) {
      if ( editsettingsthree == 1) {
        editbutton(5);
      } else {
        sendit(4);                           // sendit does toggle sonoff switch on url address stringarray 4
        delay(250);
      }
    }


    if ( sonoffstatus[5] == 0) button6(LIGHTGREY, buttontext[5]);
    if ( sonoffstatus[5] == 1) button6(GREEN, buttontext[5]);
    if ( sonoffstatus[5] == 2) button6(RED, buttontext[5]);
    if ( editsettingsthree == 1) {
      button6(PURPLE, buttontext[5]);
      button9(PURPLE, button9text);
    }
    if (button6touch()) {
      if ( editsettingsthree == 1) {
        editbutton(6);
      } else {
        sendit(5); // sendit does toggle sonoff switch on url address stringarray 5
      }
      delay(250);
    }


    button7(LIGHTGREY, button7text);
    if (button7touch()) {
      delay(250);
      settings_two_screen();
      break;
    }


    button8(LIGHTGREY, button8text);
    if (button8touch()) {
      delay(250);
      settings_four_screen();
      break;
    }

    if ( editsettingsthree == 1)button9(PURPLE, button9text); else button9(LIGHTGREY, button9text);
    if (button9touch()) {
      delay(250);
      editsettingsthree = !editsettingsthree; // toggle 1 to 0 or 0 to 1
    }


    button10(LIGHTGREY, button10text);
    if (button10touch()) {
      delay(250);
      break;
    }

    button11(LIGHTGREY, button11text);
    if (button10touch()) {
      delay(250);
      break;
    }


    x = 0; y = 0;                     // reset touch position

  }                                  // end while 1==1 loop forever




}





void button1(uint32_t color, String text) {
  tft.drawRoundRect(10, 10, 145, 40, 8, color);
  tft.setTextColor(color, BLACK); tft.setCursor(20, 25); tft.print(text);
}
bool button1touch() {
  if (x > 10 && x < 10 + 145 && y > 10 && y < 10 + 40) {
    button1(ORANGE, buttontext[0]);
    return 1;
  } else {
    return 0;
  }
}



void button11(uint32_t color, String text) {
  tft.drawRoundRect(132, 19, 20, 20, 8, color);
  tft.setTextColor(DARKGREY, BLACK); tft.setCursor(137, 21); tft.print(text);
}
bool button11touch() {
  if (x > 130 && x < 130 + 30 && y > 10 && y < 10 + 40) {
    button11(ORANGE, button11text);
    return 1;
  } else {
    return 0;
  }
}

void button2(uint32_t color, String text) {
  tft.drawRoundRect(165, 10, 145, 40, 8, color);
  tft.setTextColor(color, BLACK); tft.setCursor(175, 25); tft.print(text);
}
bool button2touch() {
  if (x > 165 && x < 165 + 145 && y > 10 && y < 10 + 40) {
    button2(ORANGE, buttontext[1]);
    return 1;
  } else {
    return 0;
  }
}

void button3(uint32_t color, String text) {
  tft.drawRoundRect(10, 60, 145, 40, 8,  color);
  tft.setTextColor(color, BLACK); tft.setCursor(20, 75); tft.print(text);
}
bool button3touch() {
  if (x > 10 && x < 10 + 145 && y > 60 && y < 60 + 40) {
    button3(ORANGE, buttontext[2]);
    return 1;
  } else {
    return 0;
  }
}

void button4(uint32_t color, String text) {
  tft.drawRoundRect(165, 60, 145, 40, 8,  color);
  tft.setTextColor(color, BLACK); tft.setCursor(175, 75); tft.print(text);
}
bool button4touch() {
  if (x > 165 && x < 165 + 145 && y > 60 && y < 60 + 40) {
    button4(ORANGE, buttontext[3]);
    return 1;
  } else {
    return 0;
  }
}

void button5(uint32_t color, String text) {
  tft.drawRoundRect(10, 110, 145, 40, 8,  color);
  tft.setTextColor(color, BLACK); tft.setCursor(20, 125); tft.print(text);
}
bool button5touch() {
  if (x > 10 && x < 10 + 145 && y > 110 && y < 110 + 40) {
    button5(ORANGE, buttontext[4]);
    return 1;
  } else {
    return 0;
  }
}

void button6(uint32_t color, String text) {
  tft.drawRoundRect(165, 110, 145, 40, 8,  color);
  tft.setTextColor(color, BLACK); tft.setCursor(175, 125); tft.print(text);
}
bool button6touch() {
  if (x > 165 && x < 165 + 145 && y > 110 && y < 110 + 40) {
    button6(ORANGE, buttontext[5]);
    return 1;
  } else {
    return 0;
  }
}


void button7(uint32_t color, String text) {
  tft.drawRoundRect(10, 165, 90, 70, 8, color);
  tft.setTextColor(color, BLACK); tft.setCursor(40, 190); tft.print(text);
}
bool button7touch() {
  if (x > 10 && x < 10 + 90 && y > 165 && y < 165 + 70) {
    button7(GREEN, button7text);
    return 1;
  } else {
    return 0;
  }
}

void button8(uint32_t color, String text) {
  tft.drawRoundRect(220, 165, 90, 70, 8,  color);
  tft.setTextColor(color, BLACK); tft.setCursor(250, 190); tft.print(text);
}
bool button8touch() {
  if (x > 220 && x < 220 + 90 && y > 165 && y < 165 + 70) {
    button8(GREEN, button8text);
    return 1;
  } else {
    return 0;
  }
}

void button9(uint32_t color, String text) {
  tft.drawRoundRect(115, 165, 90, 30, 8,  color);
  tft.setTextColor(color, BLACK); tft.setCursor(130, 175); tft.print(text);
}
bool button9touch() {
  if (x > 115 && x < 115 + 90 && y > 165 && y < 165 + 30) {
    button9(GREEN, button9text);
    return 1;
  } else {
    return 0;
  }
}

void button10(uint32_t color, String text) {
  tft.drawRoundRect(115, 205, 90, 30, 8,  color);
  tft.setTextColor(color, BLACK); tft.setCursor(130, 215); tft.print(text);
}
bool button10touch() {

  if (x > 115 && x < 115 + 90 && y > 205 && y < 205 + 30) {
    button10(GREEN, button10text);
    return 1;
  } else {
    return 0;
  }
}







//tft.drawRoundRect(10, 160, 90, 70, 8, LIGHTGREY);   // -     draw buttons outline
// tft.drawRoundRect(115, 160, 90, 70, 8, LIGHTGREY);  // modus  draw buttons outline
//  tft.drawRoundRect(220, 160, 90, 70, 8, LIGHTGREY);  // +     draw buttons ou

void sendit(int wich) {
  HTTPClient http;
  http.setConnectTimeout(100);
  // toggle
  if ( sonoffstatus[wich] == 0)http.begin(sonoffaddress[wich] + "/on"); //Specify the URL
  if ( sonoffstatus[wich] == 1)http.begin(sonoffaddress[wich] + "/off"); //Specify the URL

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

}

void editbutton(byte wich) {
  tft.fillScreen(BLACK);
  special = 0; shift = 1;
  MakeKB_Button(Mobile_KB);
  tft.setTextColor(GREEN, BLACK); tft.setCursor(15, 60); tft.print("Enter button text?");
  buttontext[wich - 1].toCharArray(MyBuffer, 25); bufIndex = strlen(MyBuffer);
  while (exitkeyboard == 0) {
    tft.getTouch(&x, &y);

    Serial.print("MyBuffer="); Serial.println(MyBuffer);
    buttontext[wich - 1] = MyBuffer;

    GetKeyPress(MyBuffer);
    x = 0; y = 0;
  }
  exitkeyboard = 0;
  special = 1; shift = 0;
  MakeKB_Button(Mobile_NumKeys);
  tft.setTextColor(GREEN, BLACK); tft.setCursor(15, 60); tft.println("Enter network address?");

   
  String stemp = sonoffaddress[wich - 1] ;
  stemp.replace("http://", "");
  stemp.toCharArray(MyBuffer, 25);   // i do not know there should be an easier way to remove http:// from char array
  bufIndex = strlen(MyBuffer);       // i do not understand the char and string thing

  while (exitkeyboard == 0) {
    tft.getTouch(&x, &y);

    Serial.print("MyBuffer="); Serial.println(MyBuffer);
    sonoffaddress[wich - 1] = "http://" + String(MyBuffer);

    GetKeyPress(MyBuffer);
      tft.setTextSize(1); tft.setCursor(15, 25);
  tft.println("");
  IPAddress serverIp = MDNS.queryHost("kitchen",100);   // 100 is timeout get ip adres for http://kitchem.local
  tft.print("IP http://kitchen.local = ");
  tft.print(serverIp.toString());tft.println("        ");
  serverIp = MDNS.queryHost("living",100);              // 100 is timeout get ip adres for http://living.local
  tft.print("IP http://living.local = ");
  tft.println(serverIp.toString());
  serverIp = MDNS.queryHost("hallway",100);               // 100 is timeout get ip adres for http://art.local
  tft.print("IP http://hallway.local = ");
  tft.println(serverIp.toString());
 tft.setTextSize(2);
    x = 0; y = 0;
  }
  exitkeyboard = 0;
  editsettingsthree = 0;
}



void sendon(int wich) {
  HTTPClient http;
  http.setConnectTimeout(100);
  // toggle
  http.begin(sonoffaddress[wich] + "/on"); //Specify the URL


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

}



void sendoff(int wich) {
  HTTPClient http;
  http.setConnectTimeout(100);
  // toggle

  http.begin(sonoffaddress[wich] + "/off"); //Specify the URL

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

}





void bitcoin_usd() {

  HTTPClient http;
  http.setConnectTimeout(500);
  // toggle

  http.begin("http://api.coindesk.com/v1/bpi/currentprice/BTC.json"); //Specify the URL

  int httpCode = http.GET();                                                  //Make the request

  if (httpCode > 0) { //Check for the returning code

    StaticJsonDocument<768> doc;
    deserializeJson(doc, http.getStream());

    // DeserializationError error = deserializeJson(doc, input);

    // if (error) {
    //  Serial.print(F("deserializeJson() failed: "));
    //  Serial.println(error.f_str());
    //  return;
    // }

    JsonObject time = doc["time"];
    const char* time_updated = time["updated"]; // "Oct 2, 2021 10:42:00 UTC"
    const char* time_updatedISO = time["updatedISO"]; // "2021-10-02T10:42:00+00:00"
    const char* time_updateduk = time["updateduk"]; // "Oct 2, 2021 at 11:42 BST"

    const char* disclaimer = doc["disclaimer"]; // "This data was produced from the CoinDesk Bitcoin Price ...

    JsonObject bpi_USD = doc["bpi"]["USD"];
    const char* bpi_USD_code = bpi_USD["code"]; // "USD"
    const char* bpi_USD_rate = bpi_USD["rate"]; // "47,680.7167"
    const char* bpi_USD_description = bpi_USD["description"]; // "United States Dollar"
    double bpi_USD_rate_float = bpi_USD["rate_float"]; // 47680.7167

    JsonObject bpi_BTC = doc["bpi"]["BTC"];
    const char* bpi_BTC_code = bpi_BTC["code"]; // "BTC"
    const char* bpi_BTC_rate = bpi_BTC["rate"]; // "1.0000"
    const char* bpi_BTC_description = bpi_BTC["description"]; // "Bitcoin"
    int bpi_BTC_rate_float = bpi_BTC["rate_float"]; // 1

    // tft.print(doc["rate"].as<String>());

    tft.setCursor(1, 200);
    tft.setTextSize(2);
    tft.setTextColor(YELLOW, BLACK);
    tft.print("1 BTC "); tft.print(bpi_USD_rate_float); tft.print(" USD ");

  } else {
    Serial.println("Error on HTTP request");
  }

  http.end(); //Free the resources

}
