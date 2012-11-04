#include "ModCrawlers.h"

ModCrawlers::ModCrawlers(int nLEDs_, uint8_t *table_) {
    counter = 0.0f;
    inc = 0.01f;
    table = table_;
    nLEDs = nLEDs_;
    length = 12;
    nCrawlers = 1;
    offset = 80;
}

ModCrawlers::~ModCrawlers() {}

void ModCrawlers::update(PixelBuffer &pb) {
    float length_inv = 1.0f / (float) length;
    int16_t tail_direction = inc > 0 ? -1 : 1;
    int16_t counter_scaled = (int16_t) (counter * (float) nLEDs);

    for (int16_t crawler = 0; crawler < nCrawlers; crawler++) {
        int16_t i = (crawler * offset + counter_scaled);
        i -= nLEDs * (i >= nLEDs);
        i += nLEDs * (i < 0);

        for (int16_t j = 0; j < length; j++) {
            int16_t t = i + j * tail_direction;
            t -= nLEDs * (t >= nLEDs);
            t += nLEDs * (t < 0);
            float fade = (float) (length - j) * length_inv;
            gradient->putPixel(pb, t, fade);
        }
    }

    counter += inc;
    counter -= 1.0f * (counter >= 1.0f);
    counter += 1.0f * (counter < 0.0f);
}

