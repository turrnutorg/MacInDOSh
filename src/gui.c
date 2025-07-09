 #include "string.h"
 #include "stdlib.h"
 #include "video.h"
 #include "text.h"
 #include "gui.h"
 #include "tiles.h"
 #include "render.h"
 
 unsigned char happyMac[] = {
	17, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 17,
	17, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 17,
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0,
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0,
	0, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 0, 9, 9, 9, 0, 9, 9, 0, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 0, 9, 9, 9, 0, 9, 9, 0, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 0, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 0, 0, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 0, 9, 9, 0, 9, 0, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 0, 0, 9, 0, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 15, 7, 7, 0, 
	0, 7, 7, 7, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 2, 2, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 0, 
	0, 7, 7, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	17, 0, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 17, 
	17, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 17, 
	17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17
};

/* old coloured logo 
unsigned char logo[] = {
	17, 17, 17, 17, 17, 17, 17, 17, 2, 2, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 2, 2, 17, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 2, 17, 17, 17, 17, 17, 17, 17, 17,
	17, 17, 17, 2, 2, 2, 2, 17, 2, 2, 2, 2, 17, 17, 17, 17,
	17, 17, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 17, 17, 17,
	17, 17, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 17, 17,
	17, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 17, 17, 17, 17,  
	17, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 17, 17, 17, 17, 17,
	17, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 17, 17, 17, 17, 17,
	17, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 17, 17, 17, 17,
	17, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 17, 17,
	17, 17, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 17, 17,
	17, 17, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 17, 17, 17,
	17, 17, 17, 3, 3, 3, 3, 3, 3, 3, 3, 3, 17, 17, 17, 17,
	17, 17, 17, 17, 3, 3, 3, 17, 3, 3, 3, 17, 17, 17, 17, 17,
	17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17
};
*/

unsigned char logo[] = {
	17, 17, 17, 17, 17, 0, 0, 17, 17, 
	17, 17, 17, 17, 0, 0, 17, 17, 17, 
	17, 17, 17, 17, 0, 17, 17, 17, 17, 
	17, 0, 0, 0, 17, 0, 0, 0, 17,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 17, 17,
	0, 0, 0, 0, 0, 0, 0, 17, 17, 
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	17, 0, 0, 0, 0, 0, 0, 0, 17, 
	17, 17, 0, 0, 17, 0, 0, 17, 17
};

struct MenuBar menu_bar = {0};

struct Menu createMenu(char *title, char *labels[], VoidFunc funcs[], int count) {
	struct Menu m;
	m.title = title;
	m.options = count;

	for (int i = 0; i < count; i++) {
		m.function[i].name = labels[i];
		m.function[i].func = funcs[i];
	}

	if (menu_bar.menu_count < MAX_MENUS) {
		menu_bar.menus[menu_bar.menu_count++] = m;
	}

	return m;
}


void drawMenuBar(void) {
    int x = 43;

    drawFilledRect(0, 0, 640, 20, 15);
    setTile(logo, 20, 4, 9, 11, 1);
    for (int i = 0; i < WIDTH; i++) {
        setPixel(i, 20, 0);
    }

    for (int i = 0; i < menu_bar.menu_count; i++) {
        const unsigned char *title = menu_bar.menus[i].title;
        printChicago(title, x, 6);

        int w = 0;
        for (const unsigned char *p = title; *p; ++p) {
            if (*p == ' ') { w += 4; continue; }
            const Glyph *g = &glyphs_chicago[*p];
            w += g->bmp ? g->adv + 1 : 13;
        }

        x += w + 13;
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
					if (drawPixel == 1) { pixel = 15; }
					setPixel(j + dx, i + dy, pixel);
				}
			}
			drawPixel = !drawPixel;
		}
		drawPixel = !drawPixel;
	}
}

void dummyFunc(void) {
	// do fuck-all
}

char *fileMenuItems[] = {"Open", "Save", "Exit"};
VoidFunc fileFuncs[] = {dummyFunc, dummyFunc, dummyFunc};

char *editMenuItems[] = {"Cut", "Copy", "Paste"};
VoidFunc editFuncs[] = {dummyFunc, dummyFunc, dummyFunc};

char *viewMenuItems[] = {"Open", "Save", "Exit"};
VoidFunc viewFuncs[] = {dummyFunc, dummyFunc, dummyFunc};

char *specialMenuItems[] = {"Cut", "Copy", "Paste"};
VoidFunc specialFuncs[] = {dummyFunc, dummyFunc, dummyFunc};

void drawDesktop(void) {
	createMenu("File", fileMenuItems, fileFuncs, 3);
	createMenu("Edit", editMenuItems, editFuncs, 3);
	createMenu("View", viewMenuItems, viewFuncs, 3);
	createMenu("Special", specialMenuItems, specialFuncs, 3);

	clearScreen();
	drawBackground(1);
	drawMenuBar();
}