#include <stdint.h>
#include "port.h"
#include "speaker.h"
#include "time.h"
 
void beep(uint32_t frequency, uint32_t ms) {
    if (frequency == 0) {
        return;
    }

    uint32_t div = 1193180 / frequency;

    outb(0x43, 0xB6);
    outb(0x42, (uint8_t)(div & 0xFF));
    outb(0x42, (uint8_t)((div >> 8) & 0xFF));

    uint8_t tmp = inb(0x61);
    outb(0x61, tmp | 0x03);

    delay_ms(ms);

    tmp = inb(0x61) & 0xFC;
    outb(0x61, tmp);
}

