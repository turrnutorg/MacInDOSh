#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dos.h>
#include "VIDEO.H"
#include "MOUSE.H"
#include "gui.h"

int i, j;

int main(void) {
	toggleVideoMode();
	mouseInit();
	loadText();

	drawBackground(2);
	setTileBackBuffer(happyMac, ((WIDTH / 2) - 13), ((HEIGHT / 2) - 16), 26, 32, 1);
	drawBuffer(1);
	sleep(3);
	drawBorderedRectNoFramebuf(160, 70, 320, 210, 0, 1, 2);
	printNoFramebuf("Welcome to MacInDOSh.", 168, 78);
	sleep(2);
	drawDesktop();

	while(1) {
		pollMouse();

		if (kbhit()) {
			char key = getch();

			if (key == 'q') {break;}
		}

		drawMouse(1);
	}

	toggleVideoMode();
	return 0;
}