#include "ESP8266-wifi.h"

WiFiServer server(TCP_PORT);
/*  constructor
 *
 */
ESP8266_Wifi::ESP8266_Wifi(char* ssid, char* password) {
  _ssid = ssid;
  _password = password;
}

void ESP8266_Wifi::setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("esp8266-dev");

  // No authentication by default
  // ArduinoOTA.setPassword((const char *)"123");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  server.begin();
}

void ESP8266_Wifi::loop() {
  ArduinoOTA.handle();
  printIPAddress();
}

String ESP8266_Wifi::ReadData() {
  WiFiClient client = server.available();
  if (!client.available()) { return ""; }
  if (SPIFFS.exists("/temp.bmp")) {
    SPIFFS.remove("/temp.bmp");
  }
  String line = "";
  while(client.available()){
    line += client.readStringUntil('\r');
    Serial.println(line);
  }
  client.flush();
  client.stop();
  return line;
}

void ESP8266_Wifi::printIPAddress() {
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}