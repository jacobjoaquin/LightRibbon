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
private:
};

#endif
