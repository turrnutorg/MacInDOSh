#ifndef VIDEO_H
#define VIDEO_H

#define HEIGHT 350
#define WIDTH 640

void initVideo(void);
void drawBuffer(void);
void clearBuffer(void);
void clearScreen(void);
void plotPixel(int x, int y, int color);
int fetchPixel(int x, int y);
void setPixel(int x, int y, int color);


#endif