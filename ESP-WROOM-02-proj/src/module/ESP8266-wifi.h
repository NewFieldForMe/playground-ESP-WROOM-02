#ifndef __ESP8266_WIFI__
#define __ESP8266_WIFI__

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FS.h>

#define TCP_PORT 8090

class ESP8266_Wifi {
public:
  ESP8266_Wifi(char* ssid, char* password);
  void setup();
  void loop();
  void printIPAddress();
  String ReadData();
private:
  char* _ssid;
  char* _password;
};

#endif