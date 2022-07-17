#include "letters_constants.h"
#include <stdlib.h>

#define LT_OFFSET_INIT		(CP_COLUMNS - 1)

#define LT_BUFFER_SIZE		300			// going over the buffer will truncate it to small numbers
										// (but will probably fail somehow since the primary device
										//  will still send more bytes than the ones required here)

// buffer must be already init with proper length
// (this is useful to hardcode a buffer instead of adding char-by-char, internal use only for testing and stuff)
#define letters_set_buffer(a, s) memcpy((char *)lt_str_bf, a, s);

static int lt_str_cursor = 0;			// current string cursor position when drawing letters (needs to be combined with the offset to get the absolute position in the matrix)
static int lt_offset = LT_OFFSET_INIT;	// offset in the matrix to start drawing (can be < 0 or >= CP_COLUMNS)

volatile unsigned char lt_str_bf[LT_BUFFER_SIZE];

volatile char lt_scroll = 1; 			// 1: scroll text, 0: static (starts at left)

volatile char lt_offset_init = 0;
volatile char lt_offset_length = 0;

// return 1 if the letter is total or partially visible on the matrix
// return -1 if it's not visible and appears "AFTER" the matrix
static int lt_copy_letter(int l) {
	if (l >= LT_BUFFER_SIZE || lt_str_bf[l] == '\0') return -1;

	for (int i = 0; i < LETTERS_WIDTH; i++) {

		if (lt_str_cursor + lt_offset + i < 0) { // draw only if the current column is inside the matrix
			continue; // this doesn't mean the current letter won't be displayed at all (just that this column is < 0 in the column count)
		}

		if (lt_str_cursor + lt_offset + i >= CP_COLUMNS) { // if we're about to draw something over the max CP_COLUMNS stop doing that, we just reached the end of the matrix
			lt_str_cursor += i;
			return -1;
		}

		// our ascii table starts at SPACE (32, ' ') and goes up to ~ (126) so anytwhing between is a) valid and b) an offset from ' '
		if ((lt_str_bf[l] >= LETTERS_FIRST_CHAR) & (lt_str_bf[l] <= LETTERS_LAST_CHAR)) {
			leds_status[lt_str_cursor + lt_offset + i] = pgm_read_byte(letters + ( (lt_str_bf[l] - ' ') * LETTERS_WIDTH ) + i);
		} else {
			// other characters will be replaced by space
			leds_status[lt_str_cursor + lt_offset + i] = pgm_read_byte(letters + ( (0) * LETTERS_WIDTH ) + i);
		}
	}

	lt_str_cursor += LETTERS_WIDTH;

	// after drawing the letter, add an empty column if we're still in the matrix bounds (doesn't matter if it's the last character, do it anyway)
	if ((lt_str_cursor + lt_offset + 1 >= 0) && (lt_str_cursor + lt_offset + 1 < CP_COLUMNS)) {
		leds_status[lt_str_cursor + lt_offset + 1] = 0x00;
		++lt_str_cursor;
	}	

	return 1;
}

void letters_set_buffer_char(char a, int pos) {
	if (pos < LT_BUFFER_SIZE) lt_str_bf[pos] = a;
}

void letters_init() {
	lt_str_cursor = 0;
	lt_offset = LT_OFFSET_INIT;
}

void letters_step() {

	if (!lt_scroll) lt_offset = 0;

	lt_str_cursor = 0;

	// set columns to 0
	for (int i = 0; i < CP_COLUMNS; i++) {
		leds_status[i] = 0;
	}

	// start copying the string to the cursor position
	int lt_count = 0;
	for (int i = 0; i < LT_BUFFER_SIZE; i++) {
		if (lt_copy_letter(i) < 0) {
			lt_count = i;
			break;
		}
	}

	// if the offset is >= the string-to-display total length, reset to start looping again
	// (the string-to-display total length uses the total amount of letters that has been
	// successfully copied to the led_status array - we copy until we found '\0' or are out of bound)
	if (--lt_offset * -1 >= lt_count * LETTERS_WIDTH) {
		lt_offset = LT_OFFSET_INIT;
	}

} 