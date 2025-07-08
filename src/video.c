#include "video.h"
#include "port.h"
#include <stdint.h>

#define VIDEO_MEM ((unsigned char*)0xA0000)
#define PLANE_MASK_PORT_INDEX 0x3C4
#define PLANE_MASK_PORT_DATA  0x3C5
#define MAP_MASK_REGISTER     0x02

unsigned char framebuffer[WIDTH * HEIGHT] = {0};

static int isCornerBlocked(int x, int y) {
    if (x < 12 && y < 12) {
        int dx = 12 - x - 1;
        int dy = 12 - y - 1;
        if (dx*dx + dy*dy >= 144) return 1;
    }
    if (x >= 628 && y < 12) {
        int dx = x - 628;
        int dy = 12 - y - 1;
        if (dx*dx + dy*dy >= 144) return 1;
    }
    if (x < 12 && y >= 468) {
        int dx = 12 - x - 1;
        int dy = y - 468;
        if (dx*dx + dy*dy >= 144) return 1;
    }
    if (x >= 628 && y >= 468) {
        int dx = x - 628;
        int dy = y - 468;
        if (dx*dx + dy*dy >= 144) return 1;
    }
    return 0;
}

static void setWritePlane(int plane) {
    outb(PLANE_MASK_PORT_INDEX, MAP_MASK_REGISTER);
    outb(PLANE_MASK_PORT_DATA, 1 << plane);
}

void setPixel(int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    if (isCornerBlocked(x, y)) return;
    framebuffer[y * WIDTH + x] = color & 0x0F;
}

void plotPixel(int x, int y, int color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    if (isCornerBlocked(x, y)) return;

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

int fetchPixel(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;
    return framebuffer[y * WIDTH + x];
}

void drawBuffer(void) {
    const int bytes_per_line = WIDTH / 8;

    for (int plane = 0; plane < 4; plane++) {
        setWritePlane(plane);

        for (int y = 0; y < HEIGHT; y++) {
            unsigned char *vram_ptr = VIDEO_MEM + y * bytes_per_line;
            unsigned char *frame_ptr = framebuffer + y * WIDTH;

            for (int byte = 0; byte < bytes_per_line; byte++) {
                unsigned char out_byte = 0;

                for (int bit = 0; bit < 8; bit++) {
                    int x = byte * 8 + bit;
                    unsigned char color = frame_ptr[x];
                    if ((color >> plane) & 1) {
                        out_byte |= (1 << (7 - bit));
                    }
                }

                vram_ptr[byte] = out_byte;
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

void set_palette_color(unsigned char index, unsigned char rgb_val) {
    inb(0x3DA);  
    outb(0x3C0, (index & 0x1F) | 0x20); 
    outb(0x3C0, rgb_val);                  
    inb(0x3DA);           
}

unsigned char ega_color(unsigned char r, unsigned char g, unsigned char b) {
    return ((r & 0x03) << 4) | ((g & 0x03) << 2) | (b & 0x03);
}

void invertColor(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    int current = fetchPixel(x, y);
    int inverted = 15 - (current & 0x0F);
    setPixel(x, y, inverted);
}

