 #include "string.h"
 #include "stdlib.h"
 #include "video.h"
 #include "text.h"
 #include "gui.h"
 #include "tiles.h"
 #include "render.h"
 
 unsigned char happyMac[] = {
	17, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 17,
	17, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 17,
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0,
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0,
	0, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 9, 9, 9, 0, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 0, 9, 9, 9, 9, 0, 9, 9, 9, 0, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 0, 9, 9, 9, 0, 0, 9, 9, 9, 0, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 0, 0, 0, 9, 9, 0, 0, 0, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 
	0, 7, 7, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	17, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 
	17, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 17, 
	17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17
};

unsigned char logo[] = {
	17, 17, 17, 17, 17, 17, 17, 17, 17, 2, 2, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 17, 2, 2, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 17, 2, 17, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 2, 2, 2, 17, 2, 2, 2, 17, 17, 17, 17,
	17, 17, 17, 17, 2, 2, 2, 2, 2, 2, 2, 2, 2, 17, 17, 17,
	17, 17, 17, 17, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 17, 17,
	17, 17, 17, 14, 14, 14, 14, 14, 14, 14, 14, 14, 17, 17, 17, 17,  
	17, 17, 17, 6, 6, 6, 6, 6, 6, 6, 6, 17, 17, 17, 17, 17,
	17, 17, 17, 6, 6, 6, 6, 6, 6, 6, 6, 17, 17, 17, 17, 17,
	17, 17, 17, 4, 4, 4, 4, 4, 4, 4, 4, 4, 17, 17, 17, 17,
	17, 17, 17, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 17, 17,
	17, 17, 17, 17, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 17, 17,
	17, 17, 17, 17, 5, 5, 5, 5, 5, 5, 5, 5, 5, 17, 17, 17,
	17, 17, 17, 17, 17, 3, 3, 3, 3, 3, 3, 3, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 3, 3, 17, 3, 3, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17
};

struct MenuBar menu_bar = {0};

struct Menu createMenu(char *title, char *labels[], VoidFunc funcs[], int count) {
	struct Menu m;
	int i;
	m.title = title;
	m.options = count;

	for (i = 0; i < count; i++) {
		m.function[i].name = labels[i];
		m.function[i].func = funcs[i];
	}

	menu_bar.menus[menu_bar.menu_count++];

	return m;
}

void drawMenuBar(void) {
    int i, j = 0;
    int x = 30;

	drawFilledRect(0, 0, 640, 20, 15);

    for (i = 0; i < menu_bar.menu_count; i++) {
        if (strcmp(menu_bar.menus[i].title, "apple") == 0) {
			drawTile(logo, 12, 2, 10, 12, 1);
            j = 5;
        } else {
	    print(menu_bar.menus[i].title, x, 2);
            j = strlen(menu_bar.menus[i].title);
        }

        x += j * 8 + 16;
    }
}

void drawBackground(int pixelCount) {
	int drawPixel = 1;
	int dx, dy;
	int i, j;
	for (i = 0; i < HEIGHT; i += pixelCount) {
		for (j = 0; j < WIDTH; j += pixelCount) {
			for (dy = 0; dy < pixelCount; dy++) {
				for (dx = 0; dx < pixelCount; dx++) {
					int pixel = 0;
					if (drawPixel == 1) { pixel = 9; }
					setPixel(j + dx, i + dy, pixel);
				}
			}
			drawPixel = !drawPixel;
		}
		drawPixel = !drawPixel;
	}
}

void drawDesktop(void) {
	clearScreen();
	drawBackground(1);
	drawMenuBar();
	drawTile(logo, 14, 2, 16, 16, 1);
}