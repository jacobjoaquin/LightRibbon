#include "Gradient.h"

Gradient::Gradient() {
}

void Gradient::fillPixelBuffer(PixelBuffer &pb) {}

void Gradient::putPixel(PixelBuffer &pb, uint16_t c, float x) {
    c *= pb.N_COLORS;

    pb.buffer[c] = (uint8_t) (x * 127.0f);
    pb.buffer[++c] = (uint8_t) (x * 127.0f);
    pb.buffer[++c] = (uint8_t) (x * 127.0f);
}
