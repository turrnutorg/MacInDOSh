#ifndef MOUSE_H
#define MOUSE_H

extern int mouseX;
extern int mouseY;
extern int leftClicked;
extern int rightClicked;
extern int middleClicked;

void pollMouse(void);
void drawMouse(void);

#endif