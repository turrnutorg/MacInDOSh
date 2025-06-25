#ifndef RENDER_H
#define RENDER_H

 void drawFilledRect(int x, int y, int width, int height, int color);
 void drawRect(int x, int y, int width, int height, int color, int thickness);
 void drawBorderedRect(int x, int y, int width, int height, int bordercolor, int fillcolor, int borderThickness);
 void drawFilledRectNoFramebuf(int x, int y, int width, int height, int color);
 void drawRectNoFramebuf(int x, int y, int width, int height, int color, int thickness);
 void drawBorderedRectNoFramebuf(int x, int y, int width, int height, int bordercolor, int fillcolor, int borderThickness);

#endif