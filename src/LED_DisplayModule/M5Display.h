#include "../../Defines.h"

#include <FastLED.h>
#define FASTLED_INTERNAL

void setup_M5Display();

void animation(uint8_t *buffptr, uint8_t amspeed, uint8_t ammode, int64_t amcount = -1);
void displaybuff(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0);
void setBrightness(uint8_t brightness);
void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color);
void drawpix(uint8_t Number, CRGB Color);
void clear();
void fillpix(CRGB Color);

