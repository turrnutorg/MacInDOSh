#include "text.h"
#include "video.h"
#include "video.h"
#include "gui.h"
#include "tiles.h"
#include "render.h"
#include "time.h"

void main(void) __attribute__((section(".main")));

int i, j;

void main(void) {
    pit_init_for_polling();
    loadText();
	drawBackground(2);
	setTile(happyMac, ((WIDTH / 2) - 13), ((HEIGHT / 2) - 16), 26, 32, 1);
	drawBuffer();
	delay_ms(3000);

	drawBorderedRectNoFramebuf(160, 70, 320, 210, 0, 1, 2);
	printNoFramebuf("Welcome to MacInDOSh.", 168, 78);
	delay_ms(2000);
	
	drawDesktop();

	while(1);
}