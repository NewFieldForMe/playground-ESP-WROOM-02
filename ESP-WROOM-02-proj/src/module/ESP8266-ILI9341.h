#ifndef __ESP8266_ILI9341__
#define __ESP8266_ILI9341__

#include <FS.h>
#include <TFTv2.h>

#define TFT_CS     15
#define TFT_RST    16  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     2

class ESP8266_ILI9341 {
public:
  ESP8266_ILI9341();
  void setup();
  void loop();
  void bmpDraw(String filename, uint8_t x, uint8_t y);
private:
  uint16_t read16(File f);
  uint32_t read32(File f);
  uint16_t width  = 320;
  uint16_t height = 240;
};

#endif