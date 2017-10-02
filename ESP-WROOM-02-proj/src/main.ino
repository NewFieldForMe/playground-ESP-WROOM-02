#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <FS.h>
#include "module/ESP8266-wifi.h"
// #include "module/ESP8266-ST7735.h"
#include "module/ESP8266-ILI9341.h"
#include "module/MPU6050.h"

ESP8266_Wifi* _wifi;
char ssid[] = "";
char password[] = "";

// ESP8266_ST7735* _ST7735;
ESP8266_ILI9341* _ILI9341;
MPU6050* _MPU6050;

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

  // ST7735 start
  // _ST7735 = new ESP8266_ST7735();
  // _ST7735->setup();
  // ILI9341 start
  _ILI9341 = new ESP8266_ILI9341();
  _ILI9341->setup();
  // MPU6050 start
  // _MPU6050 = new MPU6050();
  // _MPU6050->setup();
}

void loop() {
  _wifi->loop();
  // _MPU6050->loop();

  String recv = _wifi->ReadData();
  String filename = "";
  if (recv == "Neko!!") {
    filename = "/mya.bmp";
  } else if(recv == "Inu!!") {
    filename = "/innu.bmp";
  }
  // if (_MPU6050->decideLED()){
  //   filename = "/mya.bmp";
  // } else {
  //   filename = "/innu.bmp";
  // }
  // filename = "/temp.bmp";
  _ILI9341->bmpDraw(filename, 0, 0);

  delay(1000);
}