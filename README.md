# Led Scroller Matrix atmega48-based

This is the firmware for a [led scroller matrix I made](https://hackaday.io/project/186372-led-scroller-matrix-atmega48-based) using an atmega48p and some charliplexing techniques (check my page on [hackaday.io](https://hackaday.io/project/186372-led-scroller-matrix-atmega48-based) for more info about the project and the board itself).

![Led scroller 1](http://albertgonzalez.coffee/projects/led_scroller_atmega48p/img/1_1000.png)

## Usage

- __make all__ to compile
- __make flash__ to upload
- __make fuses__ to set the fuses

### Device starts DISABLED by default

(so use the 0x11 command - __ENABLE__ - to start displaying things)

### Device address

__0x42__ (set on __/firmware/twi.h)

### Commands

See the example on __/host__ for more info and examples about the different commands and modes.

- __0xA1__, DIAGNOSTIC MODE (changes to __diagnostic mode__: a single glowing led that iterates over all "pixels")
- __0xB1__, LETTERS MODE + INIT + STRING LENGTH + [MULTIPLE BYTES]: changes to __letters mode__ and receives a buffer offset + byte count + some chars to be set on the __letters__ buffer
- __0xC1__, BUFFER MODE + INIT + STRING LENGTH + [MULTIPLE BYTES]: changes to __buffer mode__ and receives a buffer offset + byte count + some chars to be set on the __leds_status__ buffer

- __0x11__, ENABLE (enables the matrix output; otherwise the device will perform "as usual" - modes and flags can be changed- but __without displaying anything__)
- __0x10__, DISABLE (disables the matrix output; by DEFAULT this is the initial state when powering up the display)

- __0x20__, SPEED + SPEED_VALUE (send a value between 0x00 and 0xFF to set the step function for the modes. The bigger the number, the longest the mode step intervals will be triggered - this is directly wired to the __timer0__ used to trigger those step functions. By DEFAULT this value is set to __2__ when powering up the display)

- __0x30__, DISPLAY REGULAR (shows the display in regular mode: "0" pixels are off and "1" pixels are on; this is the initial DEFAULT behaviour when powering up the display)
- __0x31__, DISPLAY INVERT (shows the display in inverse mode: "1" pixels are off and "0" pixels are on)

- __0xB2__, LETTERS SCROLL (When in __letters mode__, the scroll will be ACTIVE; this is the initial DEFAULT behaviour when powering up the display)
- __0xB3__, LETTERS STATIC (When in __letters mode__, the scroll will be INACTIVE - showing text from left to right, with some cropped characters if those are longest than the display size)

### Buffer sizes

- __leds_status__ buffer (the whole grid): 47 bytes (fixed size)
- __letters__ buffer (the whole grid): 300 bytes (fixed size)

## Examples on /host

On the __/host__ folder there's a sample program for an __attiny85__ wired as a __primary device__ that will control and show different options and modes from an attached board.

## Info

### /firmware

Contains the firmware for an __atmega48p__ properly wired in order to control the matrix and also act as a secondary __I2C device__.

The main program is an endless loop of constant led updating (__charlieplexing_step()__ on __charlieplexing.h__, controlling all the turn-on / turn-off led stuff), reading the status from each "pixel" (or led) from a __leds_status__ main buffer. This main buffer will be modified by different modes and actions in order to "change" whatever needs to be displayed.

Those __modes__ (on the __/modes__ folder) triggers an init function when switching to them and a "mode step" that will be executed according to a __timer__ set on the micro. On each step the __mode__ usually modifies the __leds_status__ buffer, like when "scrolling" some text on each step according to the scroll speed.

In addition to the __modes__ there's also a __twi.h__ file that handles the __I2C__ communication: this device will act as a __secondary device__ that will listen to different commands that will modify the __buffers__ or some options.

Some commands will __change the mode__, others will __change__ the __leds_status__ buffer and there's a bunch of __options__ that will modify small flags and variables like speed, inverted colors, etc.

#### modes

The mode wrapper takes a couple of defined functions for each mode: __*\_init__ and __*\_step__. Adding new modes is a matter of updating the numeric constants and set the new function pointers in order to be able to execute the proper _mode change_. Notice those changes are usually handled by the __twi__ communication.

#### twi

Using the [__Two-Wire Interface__ capabilities on the atmega48](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48P_88P_168P-DS40002065A.pdf) here we handle the different commands and stuff we can receive and properly handle.

Notice we're answering with an __ACK__ or __NACK__ depending on the circumstances: usually a NACK will be sent at the end of the whole transaction, but single bytes commands cannot return a NACK since the default state is to return an ACK (setting the TWEA bit to 0 will indicate a NACK on the NEXT byte transaction, not that one)

#### buffer mode

By controlling the whole buffer we're just modifying __leds_status__ on-the-fly (notice the __buffer.h__ mode file itself it's almost empty!): we're receiving an index + byte length + that amount of bytes to directly override that specific part of the buffer.

#### letters mode

Similar to __buffer mode__ but with a different __letters buffer__: instead of storing "pixels" on the matrix we're dealing with ascii characters that are later translated into differnent columns (there's a __letters_constants.h__ file with the ascii fonts and a small JS tool I made to design them on the __/tools__ folder).

The scrolling is handled on the __letters.h__ mode file (it iterates over and over if the __lt_scroll__ flag is active - otherwise just display the text from left to right).

The __letters buffer__ has a 300 bytes fixed size, meaning strings up to 300 chars can be displayed. In order to stop scrolling over all the buffer when dealing with smaller ones, a _\0_ char terminator must be used to set the end of the current string (this way the scrolling method will stop at that point and iterate only over the small subset and not the 300 chars).

#### game of life mode

A work in progress, yet not finished nor added into the whole code.

A classic __Conwell's Game Of Life__ implementation using the matrix as an infinite grid. Adding it to the whole __modes system__ will create a larger-than-4k firmware file and won't upload to the micro.
