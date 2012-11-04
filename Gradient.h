#ifndef GRADIENT_H
#define GRADIENT_H

#include "SPI.H"
#include "PixelBuffer.h"

class Gradient
{
public:
    Gradient();
    void fillPixelBuffer(PixelBuffer &pb);
    void putPixel(PixelBuffer &pb, uint16_t c, float x);
    void setColors(float r0_, float g0_, float b0_, float r1_, float g1_, float b1_);
private:
    float r0, g0, b0, r1, g1, b1;
};

#endif
