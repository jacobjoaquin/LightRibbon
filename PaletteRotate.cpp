#include "PaletteRotate.h"

PaletteRotate::PaletteRotate(int nLEDs_, uint8_t *table_) {
    table = table_;
    nLEDs = nLEDs_;
    inc = 1.0f / 120.0f;
    phase = 0.0f;
}

PaletteRotate::~PaletteRotate() { }

void PaletteRotate::update(PixelBuffer &pb) {
    float nLEDs_inv = 1.0 / (float) nLEDs;
    int16_t index = -1;

    for (uint16_t i = 0; i < nLEDs; i++) {
        uint16_t combo = (int) (((float) i * nLEDs_inv + phase) * 128.0f);

        pb.buffer[++index] = table[combo % 128];
        pb.buffer[++index] = 10;
        pb.buffer[++index] = 0;
//        pb.buffer[index + 1] = table[(combo + 43) % 128] / 8;
//        pb.buffer[index + 2] = table[(combo + 85) % 128] / 8;
    }

    phase += inc;
    phase -= phase >= 1.0f;
    phase += phase < 0.0f;
}

