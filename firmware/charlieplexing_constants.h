
#define CP_LED_COUNT 376

#define CP_COLUMNS 47
#define CP_ROWS 8

#define CP_LED_STATUS_COUNT (CP_LED_COUNT / 8)

#define CP_LED_STRUCT_SIZE 2 // positive [pin - port], negative [pin - port]

#define CP_PORT_B 1
#define CP_PORT_C 2
#define CP_PORT_D 3

#define led_get_port(d) (d & 0x0F)
#define led_get_pin(d) (d >> 4)

typedef struct {
	unsigned char positive;
	unsigned char negative;
}led;

// the 4 "extra" leds are not mapped here, but as a reference:
//
// led 377; POS: pin 7, CP_PORT_D; NEG: pin 3, CP_PORT_D
// led 378; POS: pin 7, CP_PORT_D; NEG: pin 4, CP_PORT_D
// led 379; POS: pin 7, CP_PORT_D; NEG: pin 5, CP_PORT_D
// led 380; POS: pin 7, CP_PORT_D; NEG: pin 6, CP_PORT_D

// positive / negative: left 4 bits set the pin number; right 4 bits set port (B/C/D)
PROGMEM const static char leds[CP_LED_COUNT * CP_LED_STRUCT_SIZE] = {
	
	// column 1
	0x00 | CP_PORT_B,		(1 << 4) | CP_PORT_B, // led 1
	0x00 | CP_PORT_B,		(2 << 4) | CP_PORT_B, // led 2
	0x00 | CP_PORT_B,		(3 << 4) | CP_PORT_B, // led 3
	0x00 | CP_PORT_B,		(4 << 4) | CP_PORT_B, // led 4
	0x00 | CP_PORT_B,		(5 << 4) | CP_PORT_B, // led 5
	0x00 | CP_PORT_B,		(6 << 4) | CP_PORT_B, // led 6
	0x00 | CP_PORT_B,		(7 << 4) | CP_PORT_B, // led 7
	0x00 | CP_PORT_B,		(0 << 4) | CP_PORT_C, // led 8

	// column 2
	0x00 | CP_PORT_B,		(1 << 4) | CP_PORT_C, // led 9
	0x00 | CP_PORT_B,		(2 << 4) | CP_PORT_C, // led 10
	0x00 | CP_PORT_B,		(3 << 4) | CP_PORT_C, // led 11
	0x00 | CP_PORT_B,		(0 << 4) | CP_PORT_D, // led 12
	0x00 | CP_PORT_B,		(1 << 4) | CP_PORT_D, // led 13
	0x00 | CP_PORT_B,		(2 << 4) | CP_PORT_D, // led 14
	0x00 | CP_PORT_B,		(3 << 4) | CP_PORT_D, // led 15
	0x00 | CP_PORT_B,		(4 << 4) | CP_PORT_D, // led 16

	// column 3
	0x00 | CP_PORT_B,		(5 << 4) | CP_PORT_D, // led 17
	0x00 | CP_PORT_B,		(6 << 4) | CP_PORT_D, // led 18
	0x00 | CP_PORT_B,		(7 << 4) | CP_PORT_D, // led 19
	(1 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_B, // led 20
	(1 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_B, // led 21
	(1 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_B, // led 22
	(1 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_B, // led 23
	(1 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_B, // led 24

	// column 4
	(1 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_B, // led 25
	(1 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_B, // led 26
	(1 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_C, // led 27
	(1 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_C, // led 28
	(1 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_C, // led 29
	(1 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_C, // led 30
	(1 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_D, // led 31
	(1 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_D, // led 32

	// column 5
	(1 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_D, // led 33 
	(1 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_D, // led 34
	(1 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_D, // led 35
	(1 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_D, // led 36
	(1 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_D, // led 37
	(1 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_D, // led 38
	(2 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_B, // led 39
	(2 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_B, // led 40

	// column 6
	(2 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_B, // led 41 
	(2 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_B, // led 42
	(2 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_B, // led 43
	(2 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_B, // led 44
	(2 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_B, // led 45
	(2 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_C, // led 46
	(2 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_C, // led 47
	(2 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_C, // led 48

	// column 7
	(2 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_C, // led 49 
	(2 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_D, // led 50
	(2 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_D, // led 51
	(2 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_D, // led 52
	(2 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_D, // led 53
	(2 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_D, // led 54
	(2 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_D, // led 55
	(2 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_D, // led 56

	// column 8
	(2 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_D, // led 57
	(3 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_B, // led 58
	(3 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_B, // led 59
	(3 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_B, // led 60
	(3 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_B, // led 61
	(3 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_B, // led 62
	(3 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_B, // led 63
	(3 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_B, // led 64

	// column 9
	(3 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_C, // led 65
	(3 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_C, // led 66
	(3 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_C, // led 67
	(3 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_C, // led 68
	(3 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_D, // led 69
	(3 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_D, // led 70
	(3 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_D, // led 71
	(3 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_D, // led 72

	// column 10
	(3 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_D, // led 73
	(3 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_D, // led 74
	(3 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_D, // led 75
	(3 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_D, // led 76
	(4 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_B, // led 77
	(4 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_B, // led 78
	(4 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_B, // led 79
	(4 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_B, // led 80

	// ------------------------

	// column 11
	(4 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_B, // led 81
	(4 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_B, // led 82
	(4 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_B, // led 83
	(4 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_C, // led 84
	(4 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_C, // led 85
	(4 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_C, // led 86
	(4 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_C, // led 87
	(4 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_D, // led 88

	// column 12
	(4 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_D, // led 89
	(4 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_D, // led 90
	(4 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_D, // led 91
	(4 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_D, // led 92
	(4 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_D, // led 93
	(4 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_D, // led 94
	(4 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_D, // led 95
	(5 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_B, // led 96

	// column 13
	(5 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_B, // led 97
	(5 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_B, // led 98
	(5 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_B, // led 99
	(5 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_B, // led 100
	(5 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_B, // led 101
	(5 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_B, // led 102
	(5 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_C, // led 103
	(5 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_C, // led 104

	// column 14
	(5 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_C, // led 105
	(5 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_C, // led 106
	(5 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_D, // led 107
	(5 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_D, // led 108
	(5 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_D, // led 109
	(5 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_D, // led 110
	(5 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_D, // led 111
	(5 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_D, // led 112

	// column 15
	(5 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_D, // led 113
	(5 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_D, // led 114
	(6 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_B, // led 115
	(6 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_B, // led 116
	(6 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_B, // led 117
	(6 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_B, // led 118
	(6 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_B, // led 119
	(6 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_B, // led 120

	// column 16
	(6 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_B, // led 121
	(6 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_C, // led 122
	(6 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_C, // led 123
	(6 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_C, // led 124
	(6 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_C, // led 125
	(6 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_D, // led 126
	(6 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_D, // led 127
	(6 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_D, // led 128

	// column 17
	(6 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_D, // led 129
	(6 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_D, // led 130
	(6 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_D, // led 131
	(6 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_D, // led 132
	(6 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_D, // led 133
	(7 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_B, // led 134
	(7 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_B, // led 135
	(7 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_B, // led 136

	// column 18
	(7 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_B, // led 137
	(7 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_B, // led 138
	(7 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_B, // led 139
	(7 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_B, // led 140
	(7 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_C, // led 141
	(7 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_C, // led 142
	(7 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_C, // led 143
	(7 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_C, // led 144

	// column 19
	(7 << 4) | CP_PORT_B,	(0 << 4) | CP_PORT_D, // led 145
	(7 << 4) | CP_PORT_B,	(1 << 4) | CP_PORT_D, // led 146
	(7 << 4) | CP_PORT_B,	(2 << 4) | CP_PORT_D, // led 147
	(7 << 4) | CP_PORT_B,	(3 << 4) | CP_PORT_D, // led 148
	(7 << 4) | CP_PORT_B,	(4 << 4) | CP_PORT_D, // led 149
	(7 << 4) | CP_PORT_B,	(5 << 4) | CP_PORT_D, // led 150
	(7 << 4) | CP_PORT_B,	(6 << 4) | CP_PORT_D, // led 151
	(7 << 4) | CP_PORT_B,	(7 << 4) | CP_PORT_D, // led 152

	// column 20
	(0 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_B, // led 153
	(0 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_B, // led 154
	(0 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_B, // led 155
	(0 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_B, // led 156
	(0 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_B, // led 157
	(0 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_B, // led 158
	(0 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_B, // led 159
	(0 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_B, // led 160

	// ------------------------

	// column 21
	(0 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_C, // led 161
	(0 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_C, // led 162
	(0 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_C, // led 163
	(0 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_D, // led 164
	(0 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_D, // led 165
	(0 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_D, // led 166
	(0 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_D, // led 167
	(0 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_D, // led 168

	// column 22
	(0 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_D, // led 169
	(0 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_D, // led 170
	(0 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_D, // led 171
	(1 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_B, // led 172
	(1 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_B, // led 173
	(1 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_B, // led 174
	(1 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_B, // led 175
	(1 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_B, // led 176

	// column 23
	(1 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_B, // led 177
	(1 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_B, // led 178
	(1 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_B, // led 179
	(1 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_C, // led 180
	(1 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_C, // led 181
	(1 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_C, // led 182
	(1 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_D, // led 183
	(1 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_D, // led 184

	// column 24
	(1 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_D, // led 185
	(1 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_D, // led 186
	(1 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_D, // led 187
	(1 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_D, // led 188
	(1 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_D, // led 189
	(1 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_D, // led 190
	(2 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_B, // led 191
	(2 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_B, // led 192

	// column 25
	(2 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_B, // led 193
	(2 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_B, // led 194
	(2 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_B, // led 195
	(2 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_B, // led 196
	(2 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_B, // led 197
	(2 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_B, // led 198
	(2 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_C, // led 199
	(2 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_C, // led 200

	// column 26
	(2 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_C, // led 201
	(2 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_D, // led 202
	(2 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_D, // led 203
	(2 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_D, // led 204
	(2 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_D, // led 205
	(2 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_D, // led 206
	(2 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_D, // led 207
	(2 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_D, // led 208

	// column 27
	(2 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_D, // led 209
	(3 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_B, // led 210
	(3 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_B, // led 211
	(3 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_B, // led 212
	(3 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_B, // led 213
	(3 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_B, // led 214
	(3 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_B, // led 215
	(3 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_B, // led 216

	// column 28
	(3 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_B, // led 217
	(3 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_C, // led 218
	(3 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_C, // led 219
	(3 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_C, // led 220
	(3 << 4) | CP_PORT_C,	(0 << 4) | CP_PORT_D, // led 221
	(3 << 4) | CP_PORT_C,	(1 << 4) | CP_PORT_D, // led 222
	(3 << 4) | CP_PORT_C,	(2 << 4) | CP_PORT_D, // led 223
	(3 << 4) | CP_PORT_C,	(3 << 4) | CP_PORT_D, // led 224

	// column 29
	(3 << 4) | CP_PORT_C,	(4 << 4) | CP_PORT_D, // led 225
	(3 << 4) | CP_PORT_C,	(5 << 4) | CP_PORT_D, // led 226
	(3 << 4) | CP_PORT_C,	(6 << 4) | CP_PORT_D, // led 227
	(3 << 4) | CP_PORT_C,	(7 << 4) | CP_PORT_D, // led 228
	(0 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 229
	(0 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 230
	(0 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 231
	(0 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 232

	// column 30
	(0 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 233
	(0 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 234
	(0 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 235
	(0 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 236
	(0 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 237
	(0 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 238
	(0 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 239
	(0 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 240

	// ------------------------

	// column 31
	(0 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_D, // led 241
	(0 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_D, // led 242
	(0 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_D, // led 243
	(0 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_D, // led 244
	(0 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_D, // led 245
	(0 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_D, // led 246
	(0 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_D, // led 247
	(1 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 248

	// column 32
	(1 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 249
	(1 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 250
	(1 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 251
	(1 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 252
	(1 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 253
	(1 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 254
	(1 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 255
	(1 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 256

	// column 33
	(1 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 257
	(1 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 258
	(1 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 259
	(1 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_D, // led 260
	(1 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_D, // led 261
	(1 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_D, // led 262
	(1 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_D, // led 263
	(1 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_D, // led 264

	// column 34
	(1 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_D, // led 265
	(1 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_D, // led 266
	(2 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 267
	(2 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 268
	(2 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 269
	(2 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 270
	(2 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 271
	(2 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 272

	// column 35
	(2 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 273
	(2 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 274
	(2 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 275
	(2 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 276
	(2 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 277
	(2 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 278
	(2 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_D, // led 279
	(2 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_D, // led 280

	// column 36
	(2 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_D, // led 281
	(2 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_D, // led 282
	(2 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_D, // led 283
	(2 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_D, // led 284
	(2 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_D, // led 285
	(3 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 286
	(3 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 287
	(3 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 288

	// column 37
	(3 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 289
	(3 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 290
	(3 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 291
	(3 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 292
	(3 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 293
	(3 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 294
	(3 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 295
	(3 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 296

	// column 38
	(3 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 297
	(3 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_D, // led 298
	(3 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_D, // led 299
	(3 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_D, // led 300
	(3 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_D, // led 301
	(3 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_D, // led 302
	(3 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_D, // led 303
	(3 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_D, // led 304

	// column 39
	(4 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 305
	(4 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 306
	(4 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 307
	(4 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 308
	(4 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 309
	(4 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 310
	(4 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 311
	(4 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 312

	// column 40
	(4 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 313
	(4 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 314
	(4 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 315
	(4 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 316
	(4 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_D, // led 317
	(4 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_D, // led 318
	(4 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_D, // led 319
	(4 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_D, // led 320

	// ------------------------

	// column 41
	(4 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_D, // led 321
	(4 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_D, // led 322
	(4 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_D, // led 323
	(5 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 324
	(5 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 325
	(5 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 326
	(5 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 327
	(5 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 328

	// column 42
	(5 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 329
	(5 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 330
	(5 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 331
	(5 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 332
	(5 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 333
	(5 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 334
	(5 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 335
	(5 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_D, // led 336

	// column 43
	(5 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_D, // led 337
	(5 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_D, // led 338
	(5 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_D, // led 339
	(5 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_D, // led 340
	(5 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_D, // led 341
	(5 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_D, // led 342
	(6 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 343
	(6 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 344

	// column 44
	(6 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 345
	(6 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 346
	(6 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 347
	(6 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 348
	(6 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 349
	(6 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 350
	(6 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 351
	(6 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 352

	// column 45
	(6 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 353
	(6 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 354
	(6 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_D, // led 355
	(6 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_D, // led 356
	(6 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_D, // led 357
	(6 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_D, // led 358
	(6 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_D, // led 359
	(6 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_D, // led 360

	// column 46
	(6 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_D, // led 361
	(7 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_B, // led 362
	(7 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_B, // led 363
	(7 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_B, // led 364
	(7 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_B, // led 365
	(7 << 4) | CP_PORT_D,	(4 << 4) | CP_PORT_B, // led 366
	(7 << 4) | CP_PORT_D,	(5 << 4) | CP_PORT_B, // led 367
	(7 << 4) | CP_PORT_D,	(6 << 4) | CP_PORT_B, // led 368

	// column 47
	(7 << 4) | CP_PORT_D,	(7 << 4) | CP_PORT_B, // led 369
	(7 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_C, // led 370
	(7 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_C, // led 371
	(7 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_C, // led 372
	(7 << 4) | CP_PORT_D,	(3 << 4) | CP_PORT_C, // led 373
	(7 << 4) | CP_PORT_D,	(0 << 4) | CP_PORT_D, // led 374
	(7 << 4) | CP_PORT_D,	(1 << 4) | CP_PORT_D, // led 375
	(7 << 4) | CP_PORT_D,	(2 << 4) | CP_PORT_D, // led 376

};