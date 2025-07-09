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
    loadGenevaFont();
	loadChicagoFont();
	drawBackground(1);
	setTile(happyMac, ((WIDTH / 2) - 12), ((HEIGHT / 2) - 16), 24, 32, 1);
	drawBuffer();
	delay_ms(3000);
	drawFilledRect(WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2, 15);
	print("Welcome to MacInDOSh.\nWritten by tuvalutorture.\ngo try beacon!", WIDTH / 4, HEIGHT / 4);
	print("Not affiliated with apple.\nMacintosh, Finder, Mac OS, are all trademarks of Apple Incorporated.", WIDTH / 4, HEIGHT / 3 + 16);
	delay_ms(3000);
	drawDesktop();

	while(1) {
	}
}