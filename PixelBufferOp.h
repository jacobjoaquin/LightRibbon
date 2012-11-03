#ifndef PIXELBUFFEROP_H
#define PIXELBUFFEROP_H

#include "SPI.H"
#include "PixelBuffer.h"

class PixelBufferOp
{
public:
    static void invert(PixelBuffer &pb);
    static void scramble(PixelBuffer &pb, uint16_t nPixels);
    static void reverse(PixelBuffer &pb);
    static void desaturate(PixelBuffer &pb);
    static void rotate(PixelBuffer &destination, PixelBuffer &source, uint16_t offset);
    static void range_copy(PixelBuffer &dest, int16_t d0, int16_t d1, PixelBuffer &src, int16_t s0, int16_t s1);
    static void range_copy_float(PixelBuffer &dest, int16_t d0, int16_t d1, PixelBuffer &src, float s0, float s1);

private:
};

#endif
