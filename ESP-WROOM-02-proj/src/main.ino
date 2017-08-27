#include <Wire.h>
#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  initializeMPU6050();
  Serial.begin(115200);
  while(!Serial){
    // wait for serial port to connect
    ;
  }
  Serial.println("Wake Up!!");
}

void loop() {
  readSensorData();
  calcRotation();
  // printRawSensorData();
  // printCalcSensorData();
  printAngle();
  if (decideLED() > 0.5) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  // sendSensorDataForMovingMouse();
  delay(200);
}