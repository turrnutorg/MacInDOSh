#include "video.h"
#include "mouse.h"
#include "tiles.h"
#include "text.h"

int mouseX = 0;
int mouseY = 0;

int leftClicked;
int rightClicked;
int middleClicked;

int isEnabled = 1;

static unsigned char mousebackupTile[16 * 18];

extern volatile unsigned char mouse_packet[3];
extern volatile unsigned char packet_ready;

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

extern unsigned char mouse_get_packet(unsigned char *b0,
                                      unsigned char *b1,
                                      unsigned char *b2);

void pollMouse(void) {
	if (!packet_ready) return;
	packet_ready = 0;

	int dx = (char)mouse_packet[1];
	int dy = (char)mouse_packet[2];
	int b0 = mouse_packet[0];

	mouseX += dx;
	mouseY -= dy;

    if (mouseX < 0) mouseX = 0;
    if (mouseY < 0) mouseY = 0;
    if (mouseX > WIDTH - 16) mouseX = WIDTH - 16;
    if (mouseY > HEIGHT - 18) mouseY = HEIGHT - 18;

    leftClicked   = b0 & 1;
    rightClicked  = (b0 >> 1) & 1;
    middleClicked = (b0 >> 2) & 1;
}

void fetchMouseTile(unsigned char *dest, int x, int y) {
    int i, j, k = 0;
    for (i = 0; i < 18; i++) {
        for (j = 0; j < 16; j++) {
            int pixel = fetchPixel(x + j, y + i);
            dest[k++] = (unsigned char)pixel;
        }
    }
}

void setMouseTile(void) {
    fetchMouseTile(mousebackupTile, mouseX, mouseY);
}

void drawMouse(void) {
    static int prevMouseX = -1;
    static int prevMouseY = -1;

    if ((prevMouseX == mouseX && prevMouseY == mouseY) || !isEnabled) return;

    if (prevMouseX != -1 && prevMouseY != -1) {
        drawTileNoFramebuf(mousebackupTile, prevMouseX, prevMouseY, 16, 18, 1);
    }

    fetchMouseTile(mousebackupTile, mouseX, mouseY);
    drawTileNoFramebuf(cursorPointer, mouseX, mouseY, 16, 18, 1);

    prevMouseX = mouseX;
    prevMouseY = mouseY;
}

void toggleMouse(void) {
    isEnabled = !isEnabled;
    if (!isEnabled) {
        drawTileNoFramebuf(mousebackupTile, mouseX, mouseY, 16, 18, 1);
    }
}
