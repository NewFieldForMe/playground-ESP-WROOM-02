#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <FS.h>
#include "module/ESP8266-wifi.h"
#include "module/ESP8266-ST7735.h"

int8_t neko;

ESP8266_Wifi* _wifi;
char ssid[] = "";
char password[] = "";

ESP8266_ST7735* _ST7735;

void setup() {
  Serial.begin(9600);
  Serial.println("Wake Up!!");
  while(!Serial){
    // wait for serial port to connect
    ;
  }
  // wifi start
  _wifi = new ESP8266_Wifi(ssid, password);
  _wifi->setup();
  // pinMode(LED_PIN, OUTPUT);
  // initializeMPU6050();
  _ST7735 = new ESP8266_ST7735();
  _ST7735->setup();
  neko = 1;
}

void loop() {
  _wifi->loop();
  // readSensorData();
  // calcRotation();
  // printRawSensorData();
  // printCalcSensorData();
  // printAngle();
  // if (decideLED() > 0.5) {
  //   digitalWrite(LED_PIN, HIGH);
  // } else {
  //   digitalWrite(LED_PIN, LOW);
  // }
  // sendSensorDataForMovingMouse();
  // String str = stringAngle();
  // char charArray[str.length()];
  // str.toCharArray(charArray, str.length());

  // drawtext(charArray, ST7735_WHITE);
  
  // ------
  String filename;
  if (neko == true) {
    filename = "/mya.bmp";
  } else {
    filename = "/innu.bmp";
  }
  _ST7735->bmpDraw(filename, 0, 0);
  neko = !neko;

  delay(10000);
}