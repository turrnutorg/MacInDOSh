 #include <dos.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "video.h"
 #include "windows.h"
 #include "text.h"

 Window window1;
 Window window2;
 Window window3;
 Window window4;
 Window window5;

 void createWindow(int x, int y, int width, int height, char name) {
	
 }
 void drawWindow(int window, int x, int y);

 void drawHeader(int window) {
	if (window == 1) {
		drawBorderedRectNoFramebuf(window1.x, window1.y, window1.width, 16, 0, 1, 1);
	}
 }