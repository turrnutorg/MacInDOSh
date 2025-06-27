#include "video.h"
#include "port.h"

#define VIDEO_MEM ((unsigned char*)0xA0000)
#define PLANE_MASK_PORT_INDEX 0x3C4
#define PLANE_MASK_PORT_DATA  0x3C5
#define MAP_MASK_REGISTER     0x02

unsigned char framebuffer[WIDTH * HEIGHT] = {0};

static void setWritePlane(int plane) {
    outb(PLANE_MASK_PORT_INDEX, MAP_MASK_REGISTER);
    outb(PLANE_MASK_PORT_DATA, 1 << plane);
}

void plotPixel(int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;

    unsigned int byte_offset = y * (WIDTH / 8) + (x / 8);
    unsigned char bit_mask = 1 << (7 - (x % 8));

    for (int plane = 0; plane < 4; plane++) {
        setWritePlane(plane);

        if (color & (1 << plane)) {
            VIDEO_MEM[byte_offset] |= bit_mask;
        } else {
            VIDEO_MEM[byte_offset] &= ~bit_mask;
        }
    }
}

void setPixel(int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    framebuffer[y * WIDTH + x] = color & 0x0F;
}

int fetchPixel(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;
    return framebuffer[y * WIDTH + x];
}

void drawBuffer(void) {
    for (int plane = 0; plane < 4; plane++) {
        setWritePlane(plane);

        for (int y = 0; y < HEIGHT; y++) {
            for (int byte = 0; byte < WIDTH / 8; byte++) {
                unsigned char out_byte = 0;

                for (int bit = 0; bit < 8; bit++) {
                    int x = byte * 8 + bit;
                    unsigned char color = framebuffer[y * WIDTH + x];
                    unsigned char bit_val = (color >> plane) & 1;

                    if (bit_val) {
                        out_byte |= (1 << (7 - bit));
                    }
                }

                VIDEO_MEM[y * (WIDTH / 8) + byte] = out_byte;
            }
        }
    }
}

void clearBuffer(void) {
    for (unsigned int i = 0; i < WIDTH * HEIGHT; i++) {
        framebuffer[i] = 0;
    }
}

void clearScreen(void) {
    clearBuffer();
    drawBuffer();
}
