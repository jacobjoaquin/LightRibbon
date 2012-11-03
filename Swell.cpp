#include "Swell.h"

Swell::Swell(int nLEDs) {
    brightness = 0.0f;
    inc = 1.0 / 127.0f;
    red_1 = 0;
    green_1 = 0;
    blue_1 = 0;
    red_2 = 127;
    green_2 = 127;
    blue_2 = 127;
    length = nLEDs;
}

Swell::~Swell() {
    // Nothing to do
}

void Swell::update(PixelBuffer &pb_) {
    uint8_t r, g, b;

    if (brightness >= 1.0f) {
        brightness = 1.0f;
        inc *= -1.0;
    }

    if (brightness <= 0.0f) {
        brightness = 0.0f;
        inc *= -1.0f;
    } 

    r = interp(red_1, red_2, brightness);
    g = interp(green_1, green_2, brightness);
    b = interp(blue_1, blue_2, brightness);

    for (uint16_t i = 0; i < length; i++) {
        uint16_t index = i * N_COLORS;

        pb_.buffer[index] = r;
        pb_.buffer[index + 1] = g;
        pb_.buffer[index + 2] = b;
    }

    brightness += inc;
}

uint8_t Swell::interp(uint8_t c1, uint8_t c2, float x) {
    return (uint8_t) (((float) c2 - (float) c1) * x + (float) c1);
}

void Swell::setInc(float i) {
    inc = i;
}

void Swell::setColor(uint8_t r1, uint8_t g1, uint8_t b1,
        uint8_t r2, uint8_t g2, uint8_t b2) {
    red_1 = r1;
    green_1 = g1;
    blue_1 = b1;
    red_2 = r2;
    green_2 = g2;
    blue_2 = b2;
}


