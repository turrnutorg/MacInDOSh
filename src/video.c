#include "video.h"

unsigned char framebuffer[28000];

unsigned char* video_memory = (unsigned char*)0xA0000;

void plotPixel(int x, int y, int color) {
    unsigned int offset = (y * (WIDTH / 8)) + (x / 8);
    unsigned char mask = 1 << (7 - (x % 8));

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;

    if (color) {
        video_memory[offset] |= mask;
    } else {
        video_memory[offset] &= ~mask;
    }
}

int fetchPixel(int x, int y) {
    unsigned int offset = (y * (WIDTH / 8)) + (x / 8);
    unsigned char mask = 1 << (7 - (x % 8));

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;

    return (video_memory[offset] & mask) ? 1 : 0;
}

void setPixel(int x, int y, int color) {
    unsigned int offset = (y * (WIDTH / 8)) + (x / 8);
    unsigned char mask = 1 << (7 - (x % 8));

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;

    if (color) {
        framebuffer[offset] |= mask;
    } else {
        framebuffer[offset] &= ~mask;
    }
}

void drawBuffer(void) {
    unsigned int i;
    for (i = 0; i < ((WIDTH * HEIGHT) / 8) + 1; i++) {
        if (video_memory[i] != framebuffer[i]) {
            video_memory[i] = framebuffer[i];
        }
    }
}

void clearBuffer(void) {
    unsigned int i;
    for (i = 0; i < ((WIDTH * HEIGHT) / 8) + 1; i++) {
        framebuffer[i] = 0;
    }
}

void clearScreen(void) {
    clearBuffer();
    drawBuffer();
}
