#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include "LPD8806.h"
#include "SPI.H"

class PixelBuffer
{
public:
    PixelBuffer(int nLEDs);
    ~PixelBuffer();
    void setup(int nLEDs);
    void writeToStrip(LPD8806 &strip);
    uint8_t *buffer;
    uint16_t length;
    void mixPixelBuffers(PixelBuffer &pb1, PixelBuffer &pb2);
    void mixPixelBuffers(PixelBuffer &pb);
    void clear();
    static const uint16_t N_COLORS = 3;
    static const uint8_t MAX = 255;

private:
};

#endif
