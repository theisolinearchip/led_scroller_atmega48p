#include <avr/io.h>
#include <util/delay.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <util/twi.h>

volatile int timer0_iterations = 0;
volatile unsigned char timer0_max_iterations = 2; // 31 for 1 second interval

#include "charlieplexing.h"
#include "modes/modes.h"
#include "twi.h"

void prepare_timer0() {
	// custom interrupt (using timer 0, options in A)
	TCCR0A |= (1 << WGM01); // CTC mode (datasheet page 93)
	TCNT0 = 0; // clear previous value (just in case)
	OCR0A = 255; // compare match value 
	TIMSK0 |= (1 << OCIE0A); // enable compare match interrupt
	TCCR0B |= (1 << CS02) | (1 << CS00); // prescaler (notice that TCCR0 have registers A and B for different options, that's okay)
	// start
	// 1 / (8000000 / 1024) = 0,000128 ms period -> 0,000128 * 7800 = 0,9985 (1 sec approx)
	// count to 7800, but since it's an 8 bit timer can count only up to 255
	// count to 255 * 31, aprox, for 1 sec

	// sei() activated after this call
}

ISR (TIMER0_COMPA_vect) {

	// timer0_max_iterations can be modified with the speed command
	if (++timer0_iterations >= timer0_max_iterations) { // 2 /  31
		timer0_iterations = 0;

		cp_mode_trigger_step = 1;
	}
}

int main(void)  {

	_delay_ms(500); // wait

	// base inits
	charlieplexing_init();
	twi_init();
	prepare_timer0();

	// default module init
	init_modes();

	// enable interrupts
	sei();

	// some testing
	// cp_enabled = 1;
	// char *a = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~\0";
	// letters_set_buffer(a, strlen(a));
	// exec_change_mode(MODE_LETTERS);

	// event loop
	while (1) {

		if (!cp_enabled) continue;
		
		// handle animation steps
		charlieplexing_step();

		if (cp_mode_trigger_step) {
			cp_mode_trigger_step	= 0;

			exec_mode_step();
		}

		// I2C set in the twi file
	}

}