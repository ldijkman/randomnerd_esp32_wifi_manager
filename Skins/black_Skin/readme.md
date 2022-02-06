to get the idea of a skin

black background grey text

removed most text

the text between percentage is replaced on upload to browser  

%MDNSSCAN%

%NETWORKINFO%

%OFFDELAY% 

%MDNSNAME%

%STATUS%


// Replaces placeholder with LED state value
// replaces the text between %match% in spiffs index.html on upload with actual variables
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
  else if (var == "MDNSNAME") {                  // in index.html noted as &MDNSNAME&
    return String(mdnsdotlocalurl);
  } else if (var == "IP") {                      // in index.html noted as &IP&
    return ssid+"<br>"+WiFi.localIP().toString() + " DHCP: " + dhcpcheck ;
  } else if (var == "GATEWAY") {                // in index.html noted as &GATEWAY&
    return WiFi.gatewayIP().toString();
  } else if (var == "SUBNET") {                  // in index.html noted as &SUBNET&
    return WiFi.subnetMask().toString() + "<br>DNS: " + WiFi.dnsIP().toString() + "<br>MAC: " + WiFi.macAddress();
  } else if (var == "OFFDELAY") {                  // in index.html noted as &OFFDELAY&
    return offdelay.c_str();
  } else if (var == "NTPTIME") {                  // in index.html noted as &NTPTIME&
    String mystring = "time ntp";
    return mystring;
  }

  return String();
}
