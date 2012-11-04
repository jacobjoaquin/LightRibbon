#include "ModCrawlers.h"

ModCrawlers::ModCrawlers(int nLEDs_, uint8_t *table_) {
    phasor_r = 0.0f;
    phasor_g = 0.0f;
    phasor_b = 0.0f;
    rate_r = 0.01f;
    rate_g = 0.012f;
    rate_b = 0.015f;
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
    int16_t phr = phasor_r * MAX_BRIGHTNESS;
    int16_t phg = phasor_g * MAX_BRIGHTNESS;
    int16_t phb = phasor_b * MAX_BRIGHTNESS;
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
  
            float r = table[(phr + t) % 128];
            float g = table[(phg + t) % 128];
            float b = table[(phb + t) % 128];
            float fade = (float) (length - j) * length_inv;

            uint16_t index = t * N_COLORS;

            pb.buffer[index] = (uint8_t) (r * fade);
            pb.buffer[++index] = (uint8_t) (g * fade);
            pb.buffer[++index] = (uint8_t) (b * fade);
        }
    }

    counter += inc;
    counter -= 1.0f * (counter >= 1.0f);
    counter += 1.0f * (counter < 0.0f);

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

