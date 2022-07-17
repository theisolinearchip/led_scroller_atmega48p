
static int di_current_byte = 0;

void diagnostic_init() {
	di_current_byte = 0;
	leds_status[0] = 0b10000000;

	for (int i = 1; i < CP_LED_STATUS_COUNT; i++) {
		leds_status[i] = 0b00000000;
	}
}

// full charlieplexing swipe setting all the leds
void diagnostic_step() {

	leds_status[di_current_byte] = (leds_status[di_current_byte] >> 1);

	if (leds_status[di_current_byte] == 0) {

		leds_status[di_current_byte] >>= 1;

		if (leds_status[di_current_byte] == 0) {
			if (++di_current_byte >= CP_COLUMNS) {
				di_current_byte = 0;
			}
			leds_status[di_current_byte] = 0b10000000;
		}
	}

}