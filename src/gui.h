#ifndef GUI_H
#define GUI_H

#define MAX_MENU_FUNCS 10
#define MAX_MENUS 6
typedef void (*VoidFunc)(void);

struct MenuFunction {
	char *name;
	VoidFunc func;
};

struct Menu {
	char *title;
	int options;
	struct MenuFunction function[MAX_MENU_FUNCS];
};

struct MenuBar {
	struct Menu menus[MAX_MENUS];
	int menu_count;
};

extern unsigned char logo[];
extern unsigned char happyMac[];

struct Menu createMenu(char *title, char *labels[], VoidFunc funcs[], int count);
void drawMenuBar(void);
void drawDesktop(void);
void drawBackground(int color);
void drawWindow(int window, int x, int y);
void drawHeader(int window);

#endif