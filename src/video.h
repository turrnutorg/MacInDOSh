#ifndef VIDEO_H
#define VIDEO_H

#define WIDTH  640
#define HEIGHT 480

extern int bw_mode;

void setPixel(int x, int y, int color);

void plotPixel(int x, int y, int color);

int fetchPixel(int x, int y);

void drawBuffer(void);

void clearBuffer(void);

void clearScreen(void);

#endif
