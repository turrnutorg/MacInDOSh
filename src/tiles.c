#include "stdlib.h"
#include "video.h"

void drawTile(const unsigned char *tile, int x, int y, int width, int height, int scale) {
	int k = 0;
	for (int ty = 0; ty < height; ty++) {
		for (int tx = 0; tx < width; tx++, k++) {
			unsigned char color = tile[k];
			if (color > 15) continue; // Skip transparency or invalid

			for (int dy = 0; dy < scale; dy++) {
				for (int dx = 0; dx < scale; dx++) {
					setPixel(x + tx * scale + dx, y + ty * scale + dy, color);
				}
			}
		}
	}
	drawBuffer();
}

void setTile(const unsigned char *tile, int x, int y, int width, int height, int scale) {
	int k = 0;
	for (int ty = 0; ty < height; ty++) {
		for (int tx = 0; tx < width; tx++, k++) {
			unsigned char color = tile[k];
			if (color > 15) continue;

			for (int dy = 0; dy < scale; dy++) {
				for (int dx = 0; dx < scale; dx++) {
					setPixel(x + tx * scale + dx, y + ty * scale + dy, color);
				}
			}
		}
	}
}

void drawTileNoFramebuf(const unsigned char *tile, int x, int y, int width, int height, int scale) {
	int k = 0;
	for (int ty = 0; ty < height; ty++) {
		for (int tx = 0; tx < width; tx++, k++) {
			unsigned char color = tile[k];
			if (color > 15) continue;

			for (int dy = 0; dy < scale; dy++) {
				for (int dx = 0; dx < scale; dx++) {
					plotPixel(x + tx * scale + dx, y + ty * scale + dy, color);
				}
			}
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