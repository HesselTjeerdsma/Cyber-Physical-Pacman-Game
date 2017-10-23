#pragma once
#include <Arduino.h>
#include "Pacman_definitions.h"
#include "FastLED.h"


class PacmanOled
{
public:
	PacmanOled();
	~PacmanOled();

	void begin();
	void update(Direction direction, int intensity, float orientation, int lives, bool energized, bool quarantaine, Status gameStatus);

private:
	void energizedRing();
	void quarantaineRing();
	void directionRing(Direction direction, int intensity, float orientation);
	void oneColorRing(CRGB color);
	CRGB wheel(int WheelPos);
	CRGB leds[NUM_LED];
	int nLeds;
	unsigned long energized_timer;
	unsigned long quarantaine_timer;
	bool quarantaine_color;
	int rainbowcolor;
};