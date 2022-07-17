// UNUSED work in progress
//
// this was one of the first approach to the different modes, but it's not available
// since it's not finished nor optimized. Also it's kinda heavy right now for the
// 4k firmware size limitations and maaaybe is too specific (the goal here is to provide
// some "generic" firmware functions, methods and commands to use the scroll matrix
// and avoid being super specific, so...)
//
// anyway, I love implementing this Game Of Life thing everywhere and it was fun to do :_ D

static char gol_current_buffer = 0;

// using buffers the same size as the led_count from charlieplexing.h
static char buffer_0[CP_LED_COUNT / 8];
static char buffer_1[CP_LED_COUNT / 8];

char gol_get_cell(char *buffer, char row, char col) {
	int index = CP_ROWS * col + row;

	int position = index / 8;
	int offset = index % 8;

	return ( (*(buffer + position)) & (0x01 << (7 - offset)) ) != 0 ? 1 : 0;
}

void gol_set_cell(char *buffer, char row, char col, char status) {
	int index = CP_ROWS * col + row;

	int position = index / 8;
	int offset = index % 8;

	buffer += position;

	if (status != 0) {
		*buffer |= (0x01 << (7 - offset));
	} else {
		*buffer &= ~(0x01 << (7 - offset));
	}
}

void gol_copy_to_charlieplexing_buffer() {
	char *b;

	if (!gol_current_buffer) {
		b = buffer_0;
	} else {
		b = buffer_1;
	}

	for (int i = 0; i < CP_LED_COUNT / 8; i++) {
		leds_status[i] = *(b + i);
	}
}

// returns 1 if the next step is DIFFERENT than the current one
// otherwise returns 0 (to avoid get stucked in static states)
char gol_step() {

	char new_step_different = 0;

	char *initial_buffer;
	char *final_buffer;

	if (!gol_current_buffer) {
		initial_buffer = buffer_0;
		final_buffer = buffer_1;
	} else {
		initial_buffer = buffer_1;
		final_buffer = buffer_0;
	}

	// count the neighbours
	// 	if the cell is live
	// 		dies if < 2 neighbours
	// 		lives if == 2 || == 3 neighbours
	// 		dies if > 3 neighbours
	// if the cell is dead
	// 		lives if == 3 neighbours

	for (int i = 0; i < CP_ROWS; i++) {
		for (int j = 0; j < CP_COLUMNS; j++) {

			char current_cell = gol_get_cell(initial_buffer, i, j);
			char new_cell;
			char neighbours_count = 0;

			// when reaching the grid limits just loop to the opposite side
			char i_left = i-1 < 0 ? CP_ROWS-1 : i-1;
			char i_right = i+1 > CP_ROWS-1 ? 0 : i+1;

			char j_left = j-1 < 0 ? CP_COLUMNS-1 : j-1;
			char j_right = j+1 > CP_COLUMNS-1 ? 0 : j+1;

			// LEFT
			neighbours_count += gol_get_cell(initial_buffer, i_left, j_left);
			neighbours_count += gol_get_cell(initial_buffer, i_left, j);
			neighbours_count += gol_get_cell(initial_buffer, i_left, j_right);

			// MIDDLE
			neighbours_count += gol_get_cell(initial_buffer, i, j_left);
			neighbours_count += gol_get_cell(initial_buffer, i, j_right);

			// BOTTOM
			neighbours_count += gol_get_cell(initial_buffer, i_right, j_left);
			neighbours_count += gol_get_cell(initial_buffer, i_right, j);
			neighbours_count += gol_get_cell(initial_buffer, i_right, j_right);

			if (
				(current_cell && (neighbours_count < 2 || neighbours_count > 3)) ||
				(!current_cell && neighbours_count != 3)
			) {
				new_cell = 0;
			} else {
				new_cell = 1;
			}

			gol_set_cell(final_buffer, i, j, new_cell);

			new_step_different |= (new_cell != current_cell);
		}
	}

	gol_current_buffer ^= 1;

	return new_step_different;
}


void gol_init() {

	gol_current_buffer = 0;

	// TODO: handle random seeds

	// init with some random preset values
	// for (int i = 0; i < CP_LED_COUNT / 8; i++) {
	// 	buffer_0[i] = 0x00;
	// 	buffer_1[i] = 0x00;
	// }
	//
	// buffer_0[1] = 0x04;
	// buffer_0[3] = 0xBC;
	// buffer_0[5] = 0xA3;
	// buffer_0[6] = 0x86;


	//  x
	//   x
	// xxx
	gol_set_cell(buffer_0, 3, 4, 1);
	gol_set_cell(buffer_0, 4, 5, 1);
	gol_set_cell(buffer_0, 5, 3, 1);
	gol_set_cell(buffer_0, 5, 4, 1);
	gol_set_cell(buffer_0, 5, 5, 1);
}