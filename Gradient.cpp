#include "Gradient.h"

Gradient::Gradient() {
    r0 = 1.0f;
    g0 = 0.0f;
    b0 = 0.0f;
    r1 = 0.0f;
    g1 = 0.0f;
    b1 = 1.0f;
}

void Gradient::fillPixelBuffer(PixelBuffer &pb) {}

void Gradient::putPixel(PixelBuffer &pb, uint16_t c, float x) {
    c *= pb.N_COLORS;
    float f = 1.0f - x;
    float r = (r0 * f + r1 * x) * 127.0f;
    float g = (g0 * f + g1 * x) * 127.0f;
    float b = (b0 * f + b1 * x) * 127.0f;

    pb.buffer[c] = (uint8_t) r;
    pb.buffer[++c] = (uint8_t) g;
    pb.buffer[++c] = (uint8_t) b;
}

void Gradient::setColors(float r0_, float g0_, float b0_, float r1_, float g1_, float b1_) {
    r0 = r0_;
    g0 = g0_;
    b0 = b0_;
    r1 = r1_;
    g1 = g1_;
    b1 = b1_;
}
