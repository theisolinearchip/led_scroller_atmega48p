#include "charlieplexing_constants.h"

#define cp_get_led_status(index) (leds_status[index / 8] & (0x01 << (7 - index % 8)))

// using one bit per led, so we can store up to 8 leds in a single char
// start with high bits, so if leds_status[0] == b1010000 this means
// the first and third leds on the whole array are ON ("first" bits
// are  on the "top" of the column into the physical board)
volatile unsigned char leds_status[CP_LED_STATUS_COUNT];

volatile char cp_mode_trigger_step = 0;

volatile char cp_enabled = 0;
volatile char cp_inverse = 0;

volatile uint8_t *current_ddr = &DDRB;
volatile uint8_t *current_port = &PORTB;

led cp_get_led_struct(int index) {
	led l;

	l.positive = pgm_read_byte(leds + (index * 2)); 		// "leds" length = 2 bytes
	l.negative = pgm_read_byte(leds + (index * 2) + 1); 	// "leds" length = 2 bytes

	return l;
}

// DDRB and PORTB uses #define DDRB _SFR_IO8(0x04) to be defined
// which is a macro to _MMIO_BYTE((io_addr) + __SFR_OFFSET) (https://electronics.stackexchange.com/questions/463585/what-does-sfr-io80x04-do-avr)
// also: #define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr)) (https://garretlab.web.fc2.com/en/arduino/inside/hardware/tools/avr/avr/include/avr/sfr_defs.h/_MMIO_BYTE.html)
// basically means those DDRB / PORTB definitions are uint8_t volatile *

void cp_set_current_port(unsigned char port) {	
	if (port == CP_PORT_B) {
		current_ddr = &DDRB;
		current_port = &PORTB;
	} else if (port == CP_PORT_C) {
		current_ddr = &DDRC;
		current_port = &PORTC;
	} else { // CP_PORT_D
		current_ddr = &DDRD;
		current_port = &PORTD;
	}
}

static void cp_set_led_off(led l) {

	unsigned char pos = (1 << led_get_pin(l.positive));
	unsigned char neg = (1 << led_get_pin(l.negative));

	cp_set_current_port(led_get_port(l.positive));
	(*current_ddr) &= ~pos;
	(*current_port) &= ~pos; // deactivate pull-up

	cp_set_current_port(led_get_port(l.negative));
	(*current_ddr) &= ~neg;
	(*current_port) &= ~neg; // deactivate pull-up
}

static void cp_set_led_on(led l) {

	unsigned char pos = (1 << led_get_pin(l.positive));
	unsigned char neg = (1 << led_get_pin(l.negative));

	// positive
	cp_set_current_port(led_get_port(l.positive));
	(*current_ddr) |= pos;
	(*current_port) |= pos;

	// negative
	cp_set_current_port(led_get_port(l.negative));
	(*current_ddr) |= neg;
	(*current_port) &= ~neg;
}

// internal use only
void charlieplexing_set_led(int row, int col, char val) {
	int index = CP_ROWS * col + row;

	int position = index / 8;
	int offset = index % 8;

	if (val != 0) {
		leds_status[position] |= (0x01 << (7 - offset));
	} else {
		leds_status[position] &= (~0x01 << (7 - offset));
	}
}

void charlieplexing_init() {
	cp_mode_trigger_step = 0;

	// init to 0 by default
	for (int i = 0; i < CP_LED_STATUS_COUNT; i++) {
		leds_status[i] = 0x00;
	}
}

// full charlieplexing swipe setting all the leds
void charlieplexing_step() {

	led l;
	for (int i = 0; i < CP_LED_COUNT; i++) {

		l = cp_get_led_struct(i);

		if (
			(!cp_inverse && cp_get_led_status(i) != 0) ||
			(cp_inverse && cp_get_led_status(i) == 0)
		) {
			cp_set_led_on(l);

			// add some timed delay to ensure max display time (more brightness)
			__asm__ __volatile__ (
				"mov __tmp_reg__, r16" "\n\t"
				"ldi r16, 40" "\n\t"
				"loop:" "\n\t"
				"subi r16, 1" "\n\t"
				"cpi r16, 0" "\n\t"
				"brne loop" "\n\t"
				"mov r16, __tmp_reg__" "\n\t"
			);

			// similar to
			// for (int i = 0; i < 40; i++) {
			// 	__asm__ __volatile__ ("nop");
			// }
			// (but saving some bytes)
			//
			// https://www.nongnu.org/avr-libc/user-manual/inline_asm.html
			
		}

		// deactivate
		cp_set_led_off(l);

	}

}