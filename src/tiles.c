#include "stdlib.h"
#include "video.h"

 void drawTile(unsigned char *tile, int x, int y, int width, int height, int multiplier) {
	int i, j;
	int k = 0;
	int dx, dy;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int pixelColour = 0;
			pixelColour = tile[k];
			for (dy = 0; dy < multiplier; dy++) {
				for (dx = 0; dx < multiplier; dx++) {
					if (pixelColour < 2) { setPixel(x + j * multiplier + dx, y + i * multiplier + dy, pixelColour); }
				}
			}
			k++;
		}
	}
	drawBuffer();
 }

 void setTile(unsigned char *tile, int x, int y, int width, int height, int multiplier) {
	int i, j;
	int k = 0;
	int dx, dy;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int pixelColour = 0;
			pixelColour = tile[k];
			for (dy = 0; dy < multiplier; dy++) {
				for (dx = 0; dx < multiplier; dx++) {
					if (pixelColour < 2) { setPixel(x + j * multiplier + dx, y + i * multiplier + dy, pixelColour); }
				}
			}
			k++;
		}
	}
 }

 void drawTileNoFramebuf(unsigned char *tile, int x, int y, int width, int height, int multiplier) {
	int i, j;
	int k = 0;
	int dx, dy;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int pixelColour = 0;
			pixelColour = tile[k];
			for (dy = 0; dy < multiplier; dy++) {
				for (dx = 0; dx < multiplier; dx++) {
					if (pixelColour < 2) { plotPixel(x + j * multiplier + dx, y + i * multiplier + dy, pixelColour); }
				}
			}
			k++;
		}
	}
 }


 unsigned char *fetchTile(int x, int y, int width, int height) {
	int pixels = width * height;
	unsigned char *data;
	int i, j;
	int k = 0;


	data = (unsigned char*)malloc(pixels);

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			int pixelColour = fetchPixel(x + j, y + i);
			data[k] = pixelColour;
			k++;
		}
	}
	return data;
}

/* Currently unused, but can be used to load tile files in the future when we have FS support.
unsigned char *loadTileFile(const char *filename, int width, int height) {
	FILE *file = fopen(filename, "rb");
	int pixels = width * height;
	unsigned char *data;
	int i;

	if (file == NULL) {
		toggleVideoMode();
		printf("Couldn't open %s!\n", filename);
		getch();
		return NULL;
	}

	data = (unsigned char*)malloc(pixels);

	for (i = 0; i < pixels; i++) {
		signed int pixelColour;
		fscanf(file, "%d", &pixelColour);
		if (pixelColour == -1) { pixelColour = 2; }
		data[i] = pixelColour;
	}
	fclose(file);
	return data;
}
*/