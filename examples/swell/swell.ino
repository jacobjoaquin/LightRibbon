#include "LPD8806.h"
#include "SPI.h"
#include "Swell.h"
#include "PixelBuffer.h"

uint8_t sineTable[128];
int const NUM_LEDS = 160;
LPD8806 strip = LPD8806(NUM_LEDS);
Swell swell = Swell(NUM_LEDS);
PixelBuffer pixel_buffer = PixelBuffer(NUM_LEDS);

void setup()
{
    strip.begin();
}

void loop()
{
    swell.update(pixel_buffer);
    pixel_buffer.writeToStrip(strip); 
    strip.show(); 
}

