#ifndef PALETTEROTATE_H
#define PALETTEROTATE_H

#include "SPI.H"
#include "PixelBuffer.h"

class PaletteRotate
{
public:
    PaletteRotate(int nLEDs, uint8_t *table_);
    ~PaletteRotate();
    void update(PixelBuffer &pb_);
    float inc;

private:
    static const uint8_t N_COLORS = 3;
    uint8_t *table;
    float phase;
    int nLEDs;
};

#endif
