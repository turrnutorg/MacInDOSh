#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

#define WIDTH  640
#define HEIGHT 480

extern int bw_mode;

void setPixel(int x, int y, int color);

void plotPixel(int x, int y, int color);

int fetchPixel(int x, int y);

void drawBuffer(void);

void clearBuffer(void);

void clearScreen(void);

void set_palette_color(unsigned char index, unsigned char rgb_val);

unsigned char ega_color(unsigned char r, unsigned char g, unsigned char b);

void invertColor(int x, int y);

#endif
