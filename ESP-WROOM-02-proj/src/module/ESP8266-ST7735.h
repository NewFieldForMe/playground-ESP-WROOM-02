#ifndef __ESP8266_ST7735__
#define __ESP8266_ST7735__

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <FS.h>

#define TFT_CS     15
#define TFT_RST    0  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     2

class ESP8266_ST7735 {
public:
  ESP8266_ST7735();
  void setup();
  void loop();
  void bmpDraw(String filename, uint8_t x, uint8_t y);
  void drawtext(String text, uint16_t color);
private:
  uint16_t read16(File f);
  uint32_t read32(File f);
};

#endif