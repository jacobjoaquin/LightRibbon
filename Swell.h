#ifndef SWELL_H
#define SWELL_H

#include "SPI.H"
#include "PixelBuffer.h"

class Swell
{
public:
    Swell(int nLEDs);
    ~Swell();
    void update(PixelBuffer &pb_);
    void setInc(float i);
    void setColor(uint8_t r1, uint8_t g1, uint8_t b1,
            uint8_t r2, uint8_t g2, uint8_t b2);

private:
    uint8_t interp(uint8_t c1, uint8_t c2, float x);
    uint16_t numPixels;
    float brightness;
    float inc;
    uint8_t red_1, green_1, blue_1, red_2, green_2, blue_2;
    uint16_t length;
    static const uint8_t N_COLORS = 3; 
};

#endif
