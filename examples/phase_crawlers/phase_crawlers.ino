#include "LPD8806.h"
#include "SPI.h"
#include "ModCrawlers.h"
#include "PixelBuffer.h"
#include "Gradient.h"

uint8_t sineTable[128];
int const NUM_LEDS = 160;
LPD8806 strip = LPD8806(NUM_LEDS);
PixelBuffer pb = PixelBuffer(NUM_LEDS);
PixelBuffer pb2 = PixelBuffer(NUM_LEDS);
ModCrawlers mc = ModCrawlers(NUM_LEDS, sineTable);
ModCrawlers mc2 = ModCrawlers(NUM_LEDS, sineTable);
ModCrawlers mc3 = ModCrawlers(NUM_LEDS, sineTable);
Gradient gradient = Gradient();
Gradient gradient2 = Gradient();
Gradient gradient3 = Gradient();

void setup()
{
    // Generate sine table
    for (uint8_t i = 0; i < 128; i++) {
        sineTable[i] = sin(((float) i / 128.0f) * TWO_PI) * 63 + 64;
    }

    gradient.setColors(0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f);
    gradient2.setColors(0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f);
    gradient3.setColors(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f);

    mc.length = 50;
    mc.inc = 1.0f / (float) NUM_LEDS;
    mc.nCrawlers = 1;
    mc.offset = 0;
    mc.gradient = &gradient;

    mc2.length = 50;
    mc2.inc = 0.9f / (float) NUM_LEDS;
    mc2.nCrawlers = 1;
    mc2.offset = 0;
    mc2.gradient = &gradient2;

    mc3.length = 50;
    mc3.inc = 0.8f / (float) NUM_LEDS;
    mc3.nCrawlers = 1;
    mc3.offset = 0;
    mc3.gradient = &gradient3;

    strip.begin();
}

void loop()
{
    pb.clear();
    pb2.clear();
    mc.update(pb);
    mc2.update(pb2);
    pb.mixPixelBuffers(pb2);
    pb2.clear();
    mc3.update(pb2);
    pb.mixPixelBuffers(pb2);

    // Write to strip
    clearStrip();
    pb.writeToStrip(strip); 
    strip.show();
}

void clearStrip() {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
        strip.setPixelColor(i, 0);
    }
}
