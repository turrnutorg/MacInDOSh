#include <dos.h>
#include <stdlib.h>
#include "video.h"
#include "mouse.h"

int mouseX = 0;
int mouseY = 0;

int leftClicked;
int rightClicked;
int middleClicked;

int isEnabled = 1;

static unsigned char *mousebackupTile;

unsigned char cursorPointer[] = {
	1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 0, 1, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 0, 0, 1, 2, 1, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2,
	1, 1, 1, 2, 2, 1, 0, 0, 1, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 1, 0, 0, 1, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2
};

int mouseInit(void) {
	union REGS regs;
	regs.x.ax = 0x00;
	int86(0x33, &regs, &regs);
	if (regs.x.ax == 0xFFFF) {
		return 0;
	} else {
		return 99;
	}
}

void pollMouse(void) {
	union REGS regs;
	regs.x.ax = 0x03;
	int86(0x33, &regs, &regs);
	mouseX = regs.x.cx;
	mouseY = regs.x.dx;
	if (regs.x.bx & 1) { leftClicked = 1; } else { leftClicked = 0; }
	if (regs.x.bx & 2) { rightClicked = 1; } else { rightClicked = 0; }
	if (regs.x.bx & 4) { middleClicked = 1; } else { middleClicked = 0; }
	if (mouseX > WIDTH) { mouseX = HEIGHT; }
	if (mouseY > WIDTH) { mouseY = HEIGHT; }
}


void setMouseTile(void) {
	free(mousebackupTile);
	mousebackupTile = NULL;
	mousebackupTile = (unsigned char*)fetchTile(mouseX, mouseY, 16, 18);
}
void drawMouse(void) {
	static int prevMouseX = -1;
	static int prevMouseY = -1;

	if ((prevMouseX == mouseX && prevMouseY == mouseY) || !isEnabled) { return; }

	if (prevMouseX != -1 && prevMouseY != -1) {
		drawTileNoFramebuf(mousebackupTile, prevMouseX, prevMouseY, 16, 18, 1);
		free(mousebackupTile);
		mousebackupTile = NULL;
	}

	mousebackupTile = (unsigned char*)fetchTile(mouseX, mouseY, 16, 18);

	drawTileNoFramebuf(cursorPointer, mouseX, mouseY, 16, 18, 1);

	prevMouseX = mouseX;
	prevMouseY = mouseY;
}

void toggleMouse(void) { 
	isEnabled = !isEnabled; 
	if (!isEnabled) { drawTileNoFramebuf(mousebackupTile, mouseX, mouseY, 16, 18, 1); free(mousebackupTile); } 
}
