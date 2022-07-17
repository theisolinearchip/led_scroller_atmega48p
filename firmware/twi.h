#include <stdlib.h>

// SECONDARY RECEIVER MODE

#define SCROLLER_I2C_ADDRESS 			0x42

// COMMANDS
#define COMMAND_ENABLE					0x11
#define COMMAND_DISABLE					0x10

#define COMMAND_SPEED 					0x20

#define COMMAND_DISPLAY_REGULAR			0x30
#define COMMAND_DISPLAY_INVERT 			0x31

#define COMMAND_LETTERS_SCROLL 			0xB2
#define COMMAND_LETTERS_STATIC 			0xB3

// MODES
#define COMMAND_MODE_DIAGNOSTIC 		0xA1
#define COMMAND_MODE_LETTERS	 		0xB1
#define COMMAND_MODE_BUFFER		 		0xC1

#define twi_reset_currents() 			twi_current_processing_command = 0; twi_current_remaining_bytes = 0;
#define twi_reset_TWCR_ACK()			TWCR = (1 << TWIE) | (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
#define twi_reset_TWCR_NACK() 			TWCR = ((1 << TWIE) | (1 << TWINT) | (1 << TWEN)) & ~(1 << TWEA); // same as ACK but with TWEA = 1

volatile char twi_data_recieved = 0;

volatile unsigned char twi_current_processing_command = 0; // unsigned!
volatile char twi_current_remaining_bytes = 0;

//	after a command, a change to nack should be made if there's no
//	more data left (actually this work by setting the TWEA to 0 to send
//	a NACK after THE NEXT transfer - since the actual one has already been made)
//
//	if the command is a single char it'll expect an ACK, basically because
//	a single command cannot set it's own ACK/NACK signal (it sets the ACK/NACK
//	for the NEXT ONE, not for itself)
//
ISR (TWI_vect) {

	switch(TW_STATUS) {
		case TW_SR_DATA_ACK: // data recieved, 0x80

			if (twi_current_processing_command == 0) {
				switch(TWDR) {
					default:
						break;

					// COMMANDS
					case COMMAND_ENABLE: 
					case COMMAND_DISABLE:
						cp_enabled = TWDR & 0x01;
						twi_reset_currents();
						twi_reset_TWCR_ACK();
						break;
					case COMMAND_DISPLAY_REGULAR:
					case COMMAND_DISPLAY_INVERT:
						cp_inverse = TWDR & 0x01;
						twi_reset_currents();
						twi_reset_TWCR_ACK();
						break;
					case COMMAND_SPEED:
						twi_current_processing_command = COMMAND_SPEED;
						twi_reset_TWCR_NACK();
						break;
					case COMMAND_LETTERS_SCROLL:
						lt_scroll = 1;
						twi_reset_currents();
						twi_reset_TWCR_ACK();
						break;
					case COMMAND_LETTERS_STATIC:
						lt_scroll = 0;
						twi_reset_currents();
						twi_reset_TWCR_ACK();
						break;

					// MODES
					case COMMAND_MODE_DIAGNOSTIC:
						exec_change_mode(MODE_DIAGNOSTIC);
						twi_reset_currents();
						twi_reset_TWCR_ACK();
						break;
					case COMMAND_MODE_LETTERS:
						twi_current_processing_command = COMMAND_MODE_LETTERS;
						twi_current_remaining_bytes = -1; // string position init / string length will be passed on the next 2 bytes (adding until reach 0)
						twi_reset_TWCR_ACK();
						break;
					case COMMAND_MODE_BUFFER:
						twi_current_processing_command = COMMAND_MODE_BUFFER;
						twi_current_remaining_bytes = -1; // buffer init / end will be passed on the next 2 bytes (adding until reach 0)
						twi_reset_TWCR_ACK();
						break;
				}

			} else if (twi_current_processing_command == COMMAND_MODE_LETTERS) {
				// as described before, this block is quite similar to the one in the BUFFER mode,
				// need to fuse them together in a more handy way, probably...

				if (twi_current_remaining_bytes == -1) { // first byte, letters buffer initial position
					lt_offset_init = TWDR;
					if (lt_offset_init < 0 || lt_offset_init > LT_BUFFER_SIZE) lt_offset_init = 0;

					twi_current_remaining_bytes++;
					twi_reset_TWCR_ACK();
				} else if (twi_current_remaining_bytes == 0) { // second one, letters COUNT
					lt_offset_length = TWDR;
					if ( ((lt_offset_length + lt_offset_init) < 0) || (lt_offset_length + lt_offset_init) > LT_BUFFER_SIZE) lt_offset_length = 1;

					twi_current_remaining_bytes = lt_offset_length;

					if (twi_current_remaining_bytes == 1) { // there's only remaining! (this means buffer init X and buffer end X+1)
						twi_reset_TWCR_NACK();
					} else {
						twi_reset_TWCR_ACK();
					}
				} else {
					letters_set_buffer_char(TWDR, lt_offset_init + (lt_offset_length - twi_current_remaining_bytes) );

					if (--twi_current_remaining_bytes == 1) { // there's only one remaining!
						twi_reset_TWCR_NACK();
					} else {
						twi_reset_TWCR_ACK();
					}
				}

			} else if (twi_current_processing_command == COMMAND_MODE_BUFFER) {
				// same stuff as the LETTERS mode but with bf_* globals instead of lt_*
				// (this should probably be unified into one common thing)

				if (twi_current_remaining_bytes == -1) { // first byte, buffer offset INIT
					bf_offset_init = TWDR;
					if (bf_offset_init < 0 || bf_offset_init > BF_BUFFER_SIZE) bf_offset_init = 0;

					twi_current_remaining_bytes++;
					twi_reset_TWCR_ACK();
				} else if (twi_current_remaining_bytes == 0) { // second one, buffer offset LENGTH
					bf_offset_length = TWDR;
					if ( ((bf_offset_length + bf_offset_init) < 0) || (bf_offset_length + bf_offset_init) > BF_BUFFER_SIZE) bf_offset_length = 1;

					twi_current_remaining_bytes = bf_offset_length;

					if (twi_current_remaining_bytes == 1) { // there's only remaining! (this means buffer init X and buffer end X+1)
						twi_reset_TWCR_NACK();
					} else {
						twi_reset_TWCR_ACK();
					}
				} else {
					buffer_set_buffer_char(TWDR, bf_offset_init + (bf_offset_length - twi_current_remaining_bytes) );

					if (--twi_current_remaining_bytes == 1) { // there's only one remaining!
						twi_reset_TWCR_NACK();
					} else {
						twi_reset_TWCR_ACK();
					}
				}
			}

			break;
		case TW_SR_DATA_NACK: // last data byte, 0x88

			if (twi_current_processing_command == COMMAND_MODE_LETTERS) { // it's basically the last one!
				letters_set_buffer_char(TWDR, lt_offset_init + (lt_offset_length - twi_current_remaining_bytes) );

				exec_change_mode(MODE_LETTERS);

			} else if (twi_current_processing_command == COMMAND_MODE_BUFFER) {
				buffer_set_buffer_char(TWDR, bf_offset_init + (bf_offset_length - twi_current_remaining_bytes) );

				exec_change_mode(MODE_BUFFER);
			} else if (twi_current_processing_command == COMMAND_SPEED) { // set the speed
				timer0_max_iterations = TWDR;
			} 

			twi_reset_TWCR_ACK();
			twi_reset_currents();
			break;
		default:
			twi_reset_TWCR_ACK();
			twi_reset_currents();

			// case TW_SR_STOP: // stop received, 0xA0
			// case TW_ST_SLA_ACK: // primary is requesting data (not implemented - yet?), 0xA8
			// case TW_ST_ARB_LOST_SLA_ACK: // 0xB0
			// case TW_ST_DATA_ACK: // 0xB8
			// case TW_BUS_ERROR: // 0x00

			break;
	}
}

void twi_init() {
	TWAR = SCROLLER_I2C_ADDRESS;
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
}