 #include <stdlib.h>
 #include "video.h"
 #include "render.h"

 void drawFilledRect(int x, int y, int width, int height, int color) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			setPixel(x + j, y + i, color);
		}
	}
	drawBuffer();
 }

 void drawRect(int x, int y, int width, int height, int color, int thickness) {
	int i, j, k;
	for (k = 0; k < thickness; k++) {
		width -= (k * 2);
		height -= (k * 2);
		x += k;
		y += k;
		for (i = 0; i < width; i++) {
			setPixel(x + i, y, color);
		}
		for (j = 0; j < height; j++) {
			setPixel(x, y + j, color);
		}
		for (i = 0; i < width; i++) {
			setPixel(x + i, y + j, color);
		}
		for (j = 0; j < height; j++) {
			setPixel(x + i, y + j, color);
		}
	}
	drawBuffer();
 }

 void drawBorderedRect(int x, int y, int width, int height, int bordercolor, int fillcolor, int borderThickness) {
	drawRect(x, y, width, height, bordercolor, borderThickness);
	drawFilledRect(x + borderThickness, y + borderThickness, width - borderThickness - 1, height - borderThickness - 1, fillcolor);
 }

 void drawFilledRectNoFramebuf(int x, int y, int width, int height, int color) {
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			plotPixel(x + j, y + i, color);
		}
	}
 }

 void drawRectNoFramebuf(int x, int y, int width, int height, int color, int thickness) {
	int i, j, k;
	for (k = 0; k < thickness; k++) {
		width -= (k * 2);
		height -= (k * 2);
		x += k;
		y += k;
		for (i = 0; i < width; i++) {
			plotPixel(x + i, y, color);
		}
		for (j = 0; j < height; j++) {
			plotPixel(x, y + j, color);
		}
		for (i = 0; i < width; i++) {
			plotPixel(x + i, y + j, color);
		}
		for (j = 0; j < height; j++) {
			plotPixel(x + i, y + j, color);
		}
	}
 }

 void drawBorderedRectNoFramebuf(int x, int y, int width, int height, int bordercolor, int fillcolor, int borderThickness) {
	drawRectNoFramebuf(x, y, width, height, bordercolor, borderThickness);
	drawFilledRectNoFramebuf(x + borderThickness, y + borderThickness, width - borderThickness - 1, height - borderThickness - 1, fillcolor);
 }