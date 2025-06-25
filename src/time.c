 #include "time.h"
 #include "port.h"
 #include "stdlib.h"
 #include <stdint.h>
 
 #define PIT_CHANNEL0  0x40
 #define PIT_COMMAND   0x43
 #define PIT_MODE_RATE 0x34   /* Channel 0 | Access lobyte/hibyte | Mode 2 | Binary */
 #define PIT_FREQUENCY 1193182
 #define PIT_READBACK  0xE2   /* Latch status of channel 0 */
 
 static const int month_days_norm[12] = {
     31, 28, 31, 30, 31, 30,
     31, 31, 30, 31, 30, 31
 };
 static const int month_days_leap[12] = {
     31, 29, 31, 30, 31, 30,
     31, 31, 30, 31, 30, 31
 };
 
 /*─ PIT/Delay routines ──────────────────────────────────────────────────────*/
 
 void pit_init_for_polling(void) {
     uint16_t divisor = PIT_FREQUENCY / 1000; /* 1 ms tick */
     outb(PIT_COMMAND, PIT_MODE_RATE);
     outb(PIT_CHANNEL0, divisor & 0xFF);
     outb(PIT_CHANNEL0, (divisor >> 8));
 }
 
// Variable to store the number of PIT ticks
static uint32_t pit_ticks = 0;

// This function is called in PIT interrupt handler
// Increment the pit_ticks counter every time the PIT generates a tick (1ms)
void pit_tick_increment(void) {
    pit_ticks++;
}

// Function to get the current time in milliseconds
uint32_t get_time_ms(void) {
    return pit_ticks;
}

 int pit_out_high(void) {
     outb(PIT_COMMAND, PIT_READBACK);
     return inb(PIT_CHANNEL0) & 0x80; /* OUT is bit 7 */
 }
 
 void delay_ms(uint32_t ms) {
     uint32_t changes = 0;
     int prev = pit_out_high();
     while (changes < ms) {
         int now = pit_out_high();
         if (now != prev) {
             changes++;
             prev = now;
         }
     }
 }