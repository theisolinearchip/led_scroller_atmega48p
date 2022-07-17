#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h> 
#include <string.h>

#include "i2c/i2c_primary.c"

// sample demo for an attiny85
//
// will cycle through different options and modes
// and end up in an endless charset scroll loop
//
// uses a push button on PB3 + 2 leds on PB4
// and PB1 for status (red means error, green means
// success in sending all the commands)

// PB2 & PB0 reserved for SCL and SDA
#define PIN_LED_RED						PB4
#define PIN_LED_GREEN					PB1
#define PIN_BUTTON						PB3

#define SMALL_DELAY 					20

#define SCROLLER_I2C_ADDRESS			0x42

#define COMMAND_MODE_DIAGNOSTIC 		0xA1
#define COMMAND_MODE_LETTERS 			0xB1
#define COMMAND_MODE_BUFFER 			0xC1

#define COMMAND_LETTERS_SCROLL			0xB2
#define COMMAND_LETTERS_STATIC			0xB3
#define COMMAND_ENABLE					0x11
#define COMMAND_DISABLE					0x10
#define COMMAND_SPEED 					0x20
#define COMMAND_DISPLAY_REGULAR			0x30
#define COMMAND_DISPLAY_INVERT 			0x31

#define error_loop()					led_loop(PIN_LED_RED);
#define success_loop()					led_loop(PIN_LED_GREEN);

void led_loop(int led) {
	while(1) { // inifinte loop
		PORTB |= (1 << led);
		_delay_ms(250);
		PORTB &= ~(1 << led);
		_delay_ms(250);
	}
}

void command_set_buffer(char base, int init, int length) {
		
	i2c_start();

	if (i2c_write_byte(SCROLLER_I2C_ADDRESS) & 0x01) error_loop();
	if (i2c_write_byte(COMMAND_MODE_BUFFER) & 0x01) error_loop();

	if (i2c_write_byte(init) & 0x01) error_loop(); // buffer init
	if (i2c_write_byte(length) & 0x01) error_loop(); // buffer end
	for (int i = 0; i < length; i++) {

		if (i2c_write_byte(base) & ((i == length-1) ? 0x00 : 0x01)) error_loop();
	}

	i2c_stop();
}

void command_send_single(char command) {
	i2c_start();

	if (i2c_write_byte(SCROLLER_I2C_ADDRESS) & 0x01) error_loop();
	if (i2c_write_byte(command) & 0x01) error_loop();

	i2c_stop();
}

void command_send_letters(char *a, int s, int p) {

	i2c_start();
	
	if (i2c_write_byte(SCROLLER_I2C_ADDRESS) & 0x01) error_loop();
	if (i2c_write_byte(COMMAND_MODE_LETTERS) & 0x01) error_loop();

	if (i2c_write_byte(p) & 0x01) error_loop(); // init point
	if (i2c_write_byte(s) & 0x01) error_loop(); // total size

	for (int i = 0; i < s-1; i++) {
		if (i2c_write_byte(a[i]) & 0x01) error_loop();
	}
	if (i2c_write_byte(a[s-1]) & 0x00) error_loop();

	i2c_stop();
}

void command_set_speed(unsigned char s) {
	i2c_start();
	
	if (i2c_write_byte(SCROLLER_I2C_ADDRESS) & 0x01) error_loop();
	if (i2c_write_byte(COMMAND_SPEED) & 0x01) error_loop();
	if (i2c_write_byte(s) & 0x00) error_loop();
	i2c_stop();
}

int main() {

	DDRB |= (1 << PIN_LED_RED);
	DDRB |= (1 << PIN_LED_GREEN);

	DDRB &= ~(1 << PIN_LED_GREEN);
	PORTB |= (1 << PIN_BUTTON); // activate pull-up (input)

	// init sequence
	PORTB |= (1 << PIN_LED_RED);
	PORTB |= (1 << PIN_LED_GREEN);
	_delay_ms(500);
	PORTB &= ~(1 << PIN_LED_RED);
	PORTB &= ~(1 << PIN_LED_GREEN);
	_delay_ms(500); // some min init

	i2c_init();

	while(PINB & (1 << PIN_BUTTON)) { // not pressed

	}

	command_set_speed(2);
	_delay_ms(SMALL_DELAY);

	command_send_single(COMMAND_DISPLAY_REGULAR);
	_delay_ms(SMALL_DELAY);

	command_send_single(COMMAND_ENABLE);
	_delay_ms(SMALL_DELAY);

	command_send_single(COMMAND_LETTERS_STATIC);
	_delay_ms(SMALL_DELAY);

	// show and edit letter buffer
	command_send_letters("Wel\0", 4, 0);
	_delay_ms(500);

	command_send_letters("come!\0", 6, 3);
	_delay_ms(2000);

	command_send_single(COMMAND_LETTERS_SCROLL);
	_delay_ms(4000);

	command_set_buffer(0xAA, 0, 47);
	_delay_ms(2000);

	// poke with buffer
	for (int i = 0; i < 4; i++) {
		command_set_buffer(0x00, i * 10, 10);
		_delay_ms(250);
	}
	command_set_buffer(0x00, 40, 7);
	_delay_ms(1000);

	// quick animation
	for (int i = 0; i < 47; i++) {
		command_set_buffer(0xFF, i, 1);
		_delay_ms(50);
	}
	for (int i = 46; i >= 0; i--) {
		command_set_buffer(0x00, i, 1);
		_delay_ms(50);
	}

	// inverse mode demo
	command_send_letters("Inverse mode!\0", 14, 0);
	_delay_ms(2000);

	command_send_single(COMMAND_DISPLAY_INVERT);
	_delay_ms(6000);

	// variable speed

	command_send_single(COMMAND_DISPLAY_REGULAR);
	_delay_ms(SMALL_DELAY);

	command_send_letters("Variable speed\0", 15, 0);
	_delay_ms(SMALL_DELAY);
	
	command_set_speed(1);
	_delay_ms(6000);

	command_set_speed(31);
	_delay_ms(6000);

	command_set_speed(50);
	_delay_ms(6000);

	command_send_letters("Full charset: ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~\0", 99, 0);
	command_set_speed(2);
	_delay_ms(SMALL_DELAY);

	success_loop();

}