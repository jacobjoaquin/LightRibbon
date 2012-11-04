#ifndef MODCRAWLERS_H
#define MODCRAWLERS_H

#include "SPI.H"
#include "PixelBuffer.h"
#include "Gradient.h"

class ModCrawlers
{
public:
    ModCrawlers(int nLEDs, uint8_t *table_);
    ~ModCrawlers();
    void update(PixelBuffer &pb_);
    uint16_t length;
    float inc;
    int nCrawlers;
    int offset;
    Gradient *gradient;

private:
    static const uint8_t N_COLORS = 3;

    uint8_t *table; 
    float counter;
    int16_t nLEDs;
    static const float MAX_BRIGHTNESS = 10.0f;
};

#endif
