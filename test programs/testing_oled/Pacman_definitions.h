#pragma once
typedef enum {
	PACMAN,
	GHOST
} Role;

typedef enum {
	PLAYING,
	LOST,
	WON
}Status;

typedef enum {
	N,
	NNE,
	NE,
	EEN,
	E,
	EES,
	SE,
	SSE,
	S,
	SSW,
	SW,
	WWS,
	W,
	WWN,
	WN,
	NNW
} Direction;

//define pins
#define OLEDPIN 18
#define PIN_LED1 25
#define PIN_LED2 26
#define PIN_LED3 27
#define SCREENPIN_SDA 21
#define SCREENPIN_SCL 22

#define SCREENADRESS 0x3c

#define HANDLE_EVENTS_MICROSECONDS 100000 // 100 milliseconds

#define NUM_LED 16

//define miliseconds show of the screen
#define STARTSCREEN 5000
#define ROLESCREEN 15000
#define ENDSCREEN 5000 

//times of specialmodes in milliseconds
#define QUARANTAINE 10000
#define ENERGIZER   10000

//define visual time aspects in milliseconds
#define LED_BLINK 500
#define ENERGIZER_SPEED 2500 //micro
#define QUARANTAINE_SPEED 250

#define BRIGHTNESS 20
//define colors
#define COLOR_QUARANTAINE1		0x22FF00 //bright orange
#define COLOR_QUARANTAINE2		0x44FF00 //dark orange
#define COLOR_WON				0xFF0000 //green
#define COLOR_LOST				0x00FF00 //red
#define COLOR_BEGIN				0xFFFFFF //black
#define COLOR_DEAD				0x000000 //black
#define COLOR_BACKGROUND		0x110011 //light blue
#define COLOR_DIRECTION			0xFFFFFF //white
