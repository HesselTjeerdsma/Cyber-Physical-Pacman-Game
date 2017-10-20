#pragma once
#include <Arduino.h>
#include "Pacman_definitions.h"
#include "FastLED.h"


class PacmanOled
{
public:
	PacmanOled(int num_leds);
	~PacmanOled();

	void begin();
	void updateRing(Direction direction, float orientation, int lives, bool energized, bool quarantaine, Status gameStatus);

private:
	void energizedRing();
	void quarantaineRing();
	void directionRing(Direction direction, float orientation);
	void oneColorRing(CRGB color);
	CRGB wheel(int WheelPos);

	CRGB* leds;
	int nLeds;
	unsigned long energized_timer;
	unsigned long quarantaine_timer;
	bool quarantaine_color;
	int rainbowcolor;
};