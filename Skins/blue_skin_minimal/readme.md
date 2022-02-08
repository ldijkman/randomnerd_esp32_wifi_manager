to get the idea of a skin

blue background grey text Computer Blue https://www.youtube.com/watch?v=bt0XdyBgSnE

removed most text

the text between percentage is replaced on upload to browser

%MDNSSCAN%

%NETWORKINFO%

%OFFDELAY%

%MDNSNAME%

%STATUS%

![2022-02-05-175036_1360x768_scrot](https://user-images.githubusercontent.com/45427770/152650798-ead12835-8935-442f-89cf-34472a552c16.png)


<pre>
// Replaces placeholder with LED state value
// replaces the text between %match% in LittleFS index.html on upload with actual variables
String processor(const String& var) {
  if (var == "STATE") {                 // in index.html noted as &STATE&
    if (digitalRead(ledPin)) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    return ledState;
    return String();
  }
  else if (var == "MDNSNAME") {                                      // in index.html noted as %MDNSNAME%
    return String(mdnsdotlocalurl);
  } else if (var == "IP") {                                          // in index.html noted as %IP%
    return WiFi.localIP().toString();
  } else if (var == "GATEWAY") {                                    // in index.html noted as %GATEWAY%
    return WiFi.gatewayIP().toString();
  } else if (var == "SUBNET") {                                     // in index.html noted as %SUBNET%
    return WiFi.subnetMask().toString();
  } else if (var == "OFFDELAY") {                                   // in index.html noted as %OFFDELAY%
    return offdelay.c_str();
  } else if (var == "NTPTIME") {                                    // in index.html noted as &NTPTIME&
    String mystring = "time ntp";
    return mystring;
  } else if (var == "MDNSSCAN") {                                     // in index.html noted as %MDNSSCAN%
    String mystring = scanstr;
    return mystring;
  } else if (var == "NETWORKINFO") {                                   // in index.html noted as %NETWORKINFO%
    String mystring = "mDNS: " + String(mdnsdotlocalurl) + ".local<br>";
    mystring += "SSID: " + ssid + "<br>";
    mystring += " DHCP: " + dhcpcheck + "<br>";
    mystring += "IP: " + WiFi.localIP().toString() + "<br>";
    mystring += "GateWay: " + WiFi.gatewayIP().toString() + "<br>";
    mystring +=  "<a href=\"http://" + WiFi.gatewayIP().toString() + "\">Maybe WiFiRouter Admin / Config page</a><br>";
    mystring += "Subnet: " + WiFi.subnetMask().toString() + "<br>";
    mystring += "DNS: " + WiFi.dnsIP().toString() + "<br>";
    mystring += "MAC: " + WiFi.macAddress() + "<br>";
    return mystring;
  }
</pre>


![2022-02-06-112111_1360x768_scrot](https://user-images.githubusercontent.com/45427770/152676515-6aaa1204-0681-4a14-b9b3-503a7d360bc6.png)


