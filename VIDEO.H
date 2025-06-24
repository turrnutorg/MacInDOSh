#ifndef VIDEO_H
#define VIDEO_H

#define HEIGHT 350
#define WIDTH 640

void toggleVideoMode(void);
void plotPixel(int x, int y, int color);
int fetchPixel(int x, int y);

#endif;