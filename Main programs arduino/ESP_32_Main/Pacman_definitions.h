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
#define OLEDPIN 5
#define SCREENPIN_SDA 21
#define SCREENPIN_SCL 22

#define SCREENADRESS 0x3c


//define miliseconds show of the screen
#define STARTSCREEN 1000
#define ROLESCREEN 5000
#define ENDSCREEN 5000 

//times of specialmodes in milliseconds
#define QUARANTAINE 10000
#define ENERGIZER   10000

//define visual time aspects in milliseconds
#define LED_BLINK 500
#define ENERGIZER_SPEED 50
#define QUARANTAINE_SPEED 250

//define colors
#define COLOR_QUARANTAINE1		0xFF5500 //bright orange
#define COLOR_QUARANTAINE2		0xFF8800 //dark orange
#define COLOR_WON				0x00FF00 //green
#define COLOR_LOST				0xFF0000 //red
#define COLOR_BEGIN				0x000000 //black
#define COLOR_DEAD				0x000000 //black
#define COLOR_BACKGROUND		0x00FFFF //light blue
#define COLOR_DIRECTION			0xFFFFFF //white
