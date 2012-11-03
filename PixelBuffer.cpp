#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(int nLEDs) {
    length = nLEDs;
    buffer = (uint8_t*) malloc(sizeof(uint8_t) * N_COLORS * length + 1);

    clear();
}

PixelBuffer::~PixelBuffer() { }

void PixelBuffer::writeToStrip(LPD8806 &strip) {
    for (uint16_t i = 0; i < length; i++) {
        uint16_t index = i * N_COLORS;

        strip.setPixelColor(i, buffer[index], buffer[index + 1], buffer[index + 2]);
    }
}

void PixelBuffer::mixPixelBuffers(PixelBuffer &pb) {
    int16_t index = -1;

    for (int16_t i = 0; i < length; i++) {
        buffer[++index] += pb.buffer[index];
        buffer[++index] += pb.buffer[index];
        buffer[++index] += pb.buffer[index];
    }
/*
    for (uint16_t i = 0; i < length; i++) {
        uint16_t index = i * N_COLORS;

        buffer[index + 0] += pb.buffer[index + 0];
        buffer[index + 1] += pb.buffer[index + 1];
        buffer[index + 2] += pb.buffer[index + 2];
    }
*/
}

void PixelBuffer::mixPixelBuffers(PixelBuffer &pb1, PixelBuffer &pb2) {
    for (uint16_t i = 0; i < length; i++) {
        uint16_t index = i * N_COLORS;

        buffer[index + 0] = pb1.buffer[index + 0] + pb2.buffer[index + 0];
        buffer[index + 1] = pb1.buffer[index + 1] + pb2.buffer[index + 1];
        buffer[index + 2] = pb1.buffer[index + 2] + pb2.buffer[index + 2];
    }
}

void PixelBuffer::clear() {
    memset(buffer, 0, sizeof(uint8_t) * length * N_COLORS);
}
