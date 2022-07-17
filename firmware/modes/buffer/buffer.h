#include <stdio.h>

#define BF_BUFFER_SIZE		CP_LED_COUNT / 8	// also each column is made of 8 bits, so it'll be basically one byte per column

volatile char bf_offset_init = 0;
volatile char bf_offset_length = 0;

void buffer_set_buffer_char(unsigned char a, int pos) {
	leds_status[pos] = a;
}

// required by mode implementation but unused
void buffer_init() {
	
}

void buffer_step() {

} 