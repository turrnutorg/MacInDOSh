#include "text.h"
#include "video.h"
#include "gui.h"
#include "tiles.h"
#include "render.h"
#include "time.h"

void main(void) __attribute__((section(".main")));

int i, j;

void main(void) {
    pit_init_for_polling();
	set_palette_color(0x09, ega_color(0, 3, 3));
	set_palette_color(0x06, ega_color(2, 1, 0));
    loadText();
	drawBackground(1);
	setTile(happyMac, ((WIDTH / 2) - 26), ((HEIGHT / 2) - 32), 26, 32, 2);
	drawBuffer();
	delay_ms(3000);

	clearScreen();
	drawDesktop();

	while(1) {
	}
}