#ifndef WINDOW_H
#define WINDOW_H

typedef struct {
	int x;
	int y;
	int width;
	int height;
	int active;
	int isOpen;
	unsigned char backupTile;
	char windowName[16];
} Window;

#endif