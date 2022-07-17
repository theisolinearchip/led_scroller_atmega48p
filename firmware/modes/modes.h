
// #include "modes/gameoflife/gameoflife.h" // doesn't fit in the 4k firmware size, so... :_ D
#include "modes/diagnostic/diagnostic.h"
#include "modes/letters/letters.h"
#include "modes/buffer/buffer.h"

#define MODES 							3
#define MODES_FUNCTIONS_PER_MODE 		2

#define MODE_DIAGNOSTIC 				0
#define MODE_LETTERS					1
#define MODE_BUFFER						2

void (*mode_init)();
void (*mode_step)();

// each mode is a pair of "init" and "step" functions triggered when changing to that specific
// mode and on every charliplexing mode trigger step (speed-dependant via timer0_max_iterations)
//
// the buffer works on an eternal printable loop via charlieplexing_step() that basically scans
// and set whatever is in the leds_status status main buffer as fast as it can
//
// each time the exec_mode_step() is triggered, the proper mode function may or may not change
// this buffer content (according to it's own criteria: text scrolling, etc.) so it'll be
// different on the next charlieplexing_step() iteration
//
// (also notice some modes may directly change the leds_status buffer on the TWI command
// processing interrupt, which is completely valid and will work as well)
//
void (*modes_function[MODES * MODES_FUNCTIONS_PER_MODE])() = {
	diagnostic_init, diagnostic_step, 
	letters_init, letters_step,
	buffer_init, buffer_step
};

void init_modes() {
	mode_init = modes_function[0];
	mode_step = modes_function[1];
	
	(*mode_init)();
}

void exec_change_mode(char new_mode) {	
	mode_init = modes_function[new_mode * MODES_FUNCTIONS_PER_MODE];
	mode_step = modes_function[new_mode * MODES_FUNCTIONS_PER_MODE + 1];

	(*mode_init)();
}

void exec_mode_step() {
	(*mode_step)();
}