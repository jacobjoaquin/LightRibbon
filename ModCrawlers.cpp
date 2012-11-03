#include "ModCrawlers.h"

ModCrawlers::ModCrawlers(int nLEDs_, uint8_t *table_) {
    phasor_r = 0.0f;
    phasor_g = 0.0f;
    phasor_b = 0.0f;
    rate_r = 0.01f;
    rate_g = 0.012f;
    rate_b = 0.015f;
    counter = 0;
    offset = 80;
    inc = 1;
    table = table_;
    nLEDs = nLEDs_;
    length = 12;
}

ModCrawlers::~ModCrawlers() {
    // Nothing to do
}

void ModCrawlers::update(PixelBuffer &pb) {
    pb.clear();

    for (int i = 0; i < nLEDs; i++) {
        if (!((i + counter) % offset)) {
            for (int j = 0; j < length; j++) {
                uint8_t ij = i + j;
                uint8_t t = ij;

                t -= nLEDs * (t >= nLEDs);
                t += nLEDs * (t < 0);
                
                float r = table[(((uint8_t) (phasor_r * MAX_BRIGHTNESS)) + ij) % 128];
                float g = table[(((uint8_t) (phasor_g * MAX_BRIGHTNESS)) + ij) % 128];
                float b = table[(((uint8_t) (phasor_b * MAX_BRIGHTNESS)) + ij) % 128];
                float fade = (float) (length - j) / (float) (length);
                uint16_t index = t * N_COLORS;

                pb.buffer[index] = (uint8_t) (r * fade);
                pb.buffer[++index] = (uint8_t) (g * fade);
                pb.buffer[++index] = (uint8_t) (b * fade);
            }
        }
    }

    counter += inc;
    counter -= nLEDs * (counter >= nLEDs);
    counter += nLEDs * (counter < 0);

    phasor_r += rate_r;
    phasor_r -= phasor_r >= 1.0f;
    phasor_r += phasor_r < 0.0f;

    phasor_g += rate_g;
    phasor_g -= phasor_g >= 1.0f;
    phasor_g += phasor_g < 0.0f;

    phasor_b += rate_b;
    phasor_b -= phasor_b >= 1.0f;
    phasor_b += phasor_b < 0.0f;
}

