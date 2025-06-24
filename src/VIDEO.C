 #include <dos.h>
 #include <alloc.h>
 #include <string.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "video.h"

 unsigned char far* framebuffer = NULL;
 unsigned char far* framebuf2 = NULL;

 int isToggled = 0;

 unsigned char far *video_memory = (unsigned char far*)0xA0000000L;

 void toggleVideoMode() {
	if (!isToggled) {
		union REGS regs;
		regs.x.ax = 0x0F;
		int86(0x10, &regs, &regs);
		framebuffer = (unsigned char far*)farmalloc(((WIDTH * HEIGHT) / 8) + 1);
		framebuf2 = (unsigned char far*)farmalloc(((WIDTH * HEIGHT) / 8) + 1);
		isToggled = !isToggled;
	} else {
		union REGS regs;
		regs.h.ah = 0x00;
		regs.h.al = 0x03;
		int86(0x10, &regs, &regs);
		if (framebuffer) farfree(framebuffer);
		if (framebuf2) farfree(framebuf2);
		framebuffer = NULL;
		framebuf2 = NULL;
	}
 }

 void plotPixel(x, y, color) {
	unsigned int offset = (y * (WIDTH / 8)) + (x / 8);
	unsigned char mask = 1 << (7 - (x % 8));

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }

	if (color) { video_memory[offset] |= mask; }
	else { video_memory[offset] &= ~mask; }
 }

 int fetchPixel(x, y) {
	int color;
	unsigned int offset = (y * (WIDTH / 8)) + (x / 8);
	unsigned char mask = 1 << (7 - (x % 8));

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return 0; }

	color = (video_memory[offset] & mask) ? 1 : 0;
	return color;
 }

 void setPixel(x, y, color) {
	unsigned int offset = (y * (WIDTH / 8)) + (x / 8);
	unsigned char mask = 1 << (7 - (x % 8));

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }

	if (color) { framebuf2[offset] |= mask; }
	else { framebuf2[offset] &= ~mask; }

 }

 void setPixelBackBuffer(x, y, color) {
	unsigned int offset = (y * (WIDTH / 8)) + (x / 8);
	unsigned char mask = 1 << (7 - (x % 8));

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) { return; }

	if (color) { framebuffer[offset] |= mask; }
	else { framebuffer[offset] &= ~mask; }

 }

 void syncBuffer() {
	int i;
	for (i = 0; i < 28000; i++) {
		framebuf2[i] = framebuffer[i];
	}
 }

 void clearBuffer(int buffer) {
	int i;
	for (i = 0; i < 28000; i++) { if (buffer) { framebuffer[i] = 0; } else { framebuf2[i] = 0; } }
 }

 void drawBuffer(int buffer) {
	int i;
	for (i = 0; i < 28000; i++) {
		if (buffer) {
			if (video_memory[i] != framebuffer[i] && framebuffer) {
				video_memory[i] = framebuffer[i];
			}
		}
		else { 
			if (video_memory[i] != framebuf2[i] && framebuf2) {
				video_memory[i] = framebuf2[i];
			}
		}
	}
 }

 void clearScreen() { clearBuffer(1); drawBuffer(0); syncBuffer(); }
