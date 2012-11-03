#include "PixelBufferOp.h"

void PixelBufferOp::invert(PixelBuffer &pb) {
    for (uint16_t i = 0; i < pb.length; i++) {
        uint16_t index = i * pb.N_COLORS;

        pb.buffer[index] = pb.MAX - pb.buffer[index];
        pb.buffer[index + 1] = pb.MAX - pb.buffer[index + 1];
        pb.buffer[index + 2] = pb.MAX - pb.buffer[index + 2];
    }
}

void PixelBufferOp::scramble(PixelBuffer &pb, uint16_t nPixels) {
    for (uint16_t i = 0; i < nPixels; i++) {
        uint16_t led_a = random(pb.length) * pb.N_COLORS;
        uint16_t led_b = random(pb.length) * pb.N_COLORS;
        uint8_t r = pb.buffer[led_a];
        uint8_t g = pb.buffer[led_a + 1];
        uint8_t b = pb.buffer[led_a + 2];

        pb.buffer[led_a] = pb.buffer[led_b];
        pb.buffer[led_a + 1] = pb.buffer[led_b + 1];
        pb.buffer[led_a + 2] = pb.buffer[led_b + 2];

        pb.buffer[led_b] = r;
        pb.buffer[led_b + 1] = g;
        pb.buffer[led_b + 2] = b;
    }
}

void PixelBufferOp::reverse(PixelBuffer &pb) {
    for (uint16_t i = 0; i < pb.length >> 1; i++) {
        uint16_t index = i * pb.N_COLORS;
        uint8_t r = pb.buffer[index];
        uint8_t g = pb.buffer[index + 1];
        uint8_t b = pb.buffer[index + 2];
        uint16_t opposite = (pb.length - i - 1) * pb.N_COLORS;

        pb.buffer[index] = pb.buffer[opposite];
        pb.buffer[index + 1] = pb.buffer[opposite + 1];
        pb.buffer[index + 2] = pb.buffer[opposite + 2];

        pb.buffer[opposite] = r;
        pb.buffer[opposite + 1] = g;
        pb.buffer[opposite + 2] = b;
    }
}

void PixelBufferOp::desaturate(PixelBuffer &pb) {
    for (uint16_t i = 0; i < pb.length; i++) {
        uint16_t index = i * pb.N_COLORS;
        uint8_t r = pb.buffer[index];
        uint8_t g = pb.buffer[index + 1];
        uint8_t b = pb.buffer[index + 2];
        uint16_t m = (r + g + b) / 3;

        pb.buffer[index] = m;
        pb.buffer[index + 1] = m;
        pb.buffer[index + 2] = m;
    }
}

void PixelBufferOp::rotate(PixelBuffer &destination, PixelBuffer &source, uint16_t offset) {
    uint16_t length = source.length;

    while (offset >= length) {
        offset -= length;
    }

    while (offset < 0) {
        offset += length;
    }

    for (uint16_t i = 0; i < length; i++) {
        int16_t index = i * source.N_COLORS;
        int16_t index_source = i + offset;

        index_source -= length * (index_source >= length);
        index_source += length * (index_source < 0);
        index_source *= source.N_COLORS; 

        destination.buffer[index] = source.buffer[index_source];
        destination.buffer[index + 1] = source.buffer[index_source + 1];
        destination.buffer[index + 2] = source.buffer[index_source + 2];
    }
}

void PixelBufferOp::range_copy(PixelBuffer &dest, int16_t d0, int16_t d1, PixelBuffer &src, int16_t s0, int16_t s1) {
    int16_t d_length = abs(d1 - d0);
    int16_t d_inc = d1 > d0 ? 1 : -1;
    int16_t s_length = abs(s1 - s0);
    int16_t s_inc = s1 > s0 ? 1 : -1;

    for (uint16_t i = 0; i < d_length; i++) {
        int16_t d_index = d0 * dest.N_COLORS;
        int16_t s_index = s0 * dest.N_COLORS;

        dest.buffer[d_index] = src.buffer[s_index];
        dest.buffer[++d_index] = src.buffer[++s_index];
        dest.buffer[++d_index] = src.buffer[++s_index];

        d0 += d_inc;
        s0 += s_inc;
    }
}

void PixelBufferOp::range_copy_float(PixelBuffer &dest, int16_t d0, int16_t d1, PixelBuffer &src, float s0, float s1) {
    int16_t d_length = abs(d1 - d0);
    int16_t d_inc = d1 > d0 ? 1 : -1;
    float s_inc = (s1 - s0) / (float) d_length;

    for (uint16_t i = 0; i < d_length; i++) {
        int16_t d_index = d0 * dest.N_COLORS;
        int16_t s_index = (int16_t) s0 * dest.N_COLORS;

        dest.buffer[d_index] = src.buffer[s_index];
        dest.buffer[++d_index] = src.buffer[++s_index];
        dest.buffer[++d_index] = src.buffer[++s_index];

        d0 += d_inc;
        s0 += s_inc;
    }
}

