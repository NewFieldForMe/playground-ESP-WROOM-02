#include <Wire.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#define LED_PIN 13

#define TFT_CS     15
#define TFT_RST    0  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     2
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup() {
  // pinMode(LED_PIN, OUTPUT);
  initializeMPU6050();
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  Serial.begin(115200);
  while(!Serial){
    // wait for serial port to connect
    ;
  }
  Serial.println("Wake Up!!");
  tft.fillScreen(ST7735_BLACK);
}

void loop() {
  readSensorData();
  calcRotation();
  // printRawSensorData();
  // printCalcSensorData();
  // printAngle();
  // if (decideLED() > 0.5) {
  //   digitalWrite(LED_PIN, HIGH);
  // } else {
  //   digitalWrite(LED_PIN, LOW);
  // }
  // sendSensorDataForMovingMouse();
  String str = stringAngle();
  char charArray[str.length()];
  str.toCharArray(charArray, str.length());

  drawtext(charArray, ST7735_WHITE);
  delay(1000);
}

void drawtext(char *text, uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.println("* Accel *");
  tft.println(text);
}