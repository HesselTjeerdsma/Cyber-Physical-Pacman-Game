#include <Arduino.h>
#include "PacmanOled.h"
#include "FastLED.h"

PacmanOled::PacmanOled()
:
	energized_timer(0),
	quarantaine_color(true),
	quarantaine_timer(0)
{
	randomSeed(micros());
	rainbowcolor = random(256);
}

PacmanOled::~PacmanOled()
{

}

void PacmanOled::begin()
{

	
	pinMode(OLEDPIN,OUTPUT);
	FastLED.addLeds<WS2812, OLEDPIN>(leds, NUM_LED);
	FastLED.setBrightness(BRIGHTNESS);
	delay(10);
	oneColorRing(COLOR_BEGIN);
	FastLED.show();
}

void PacmanOled::update(Direction direction, int intensity, float orientation, int lives, bool energized, bool quarantaine, Status gameStatus)
{
	if (lives == 0)
	{
		oneColorRing(COLOR_DEAD);
	}
	else if (gameStatus == PLAYING)
	{
		if (energized == true)
		{
			energizedRing();
		}
		else if (quarantaine == true)
		{
			quarantaineRing();
		}
		else
		{
			
			directionRing(direction,intensity, orientation);
		}

	}
	else if (gameStatus == LOST)
	{
		oneColorRing(COLOR_LOST); //red
	}
	else if (gameStatus == WON)
	{
		oneColorRing(COLOR_WON); //green
	}

	FastLED.show();
}

void PacmanOled::oneColorRing(CRGB color)
{
	for (int i = 0; i < NUM_LED; i++)
	{
		leds[i] = color;
	}
}

void PacmanOled::energizedRing()
{
	if (micros() > energized_timer)
	{
		energized_timer = micros() + ENERGIZER_SPEED;
		rainbowcolor = (rainbowcolor+4) % 256;
		for (int i = 0; i < NUM_LED; i++)
		{
			leds[i] = wheel((i * 256 / NUM_LED + rainbowcolor) % 256);
		}

	}

}

void PacmanOled::quarantaineRing()
{
	if (millis() > quarantaine_timer)
	{
		quarantaine_color = !quarantaine_color;
		quarantaine_timer = millis() + QUARANTAINE_SPEED;
	}

	if (quarantaine_color)
	{
		oneColorRing(COLOR_QUARANTAINE1);
	}
	else
	{
		oneColorRing(COLOR_QUARANTAINE2);
	}
}

void PacmanOled::directionRing(Direction direction, int intensity, float orientation)
{
	oneColorRing(COLOR_BACKGROUND);
	int i = (int)(16+(0.5 + orientation / 22.5) - (float)direction) % NUM_LED;
	leds[i] = ((((COLOR_DIRECTION & 0xFF0000)>>4)*intensity / 10)<<4) | ((((COLOR_DIRECTION & 0x00FF00) >> 2) * intensity / 10) << 2) | ((COLOR_DIRECTION & 0x0000FF) * intensity / 10);
}

CRGB PacmanOled::wheel(int WheelPos) {
	CRGB color;
	if (85 > WheelPos) {
		color.r = 0;
		color.g = 3*WheelPos;
		color.b = (255 - 3*WheelPos);
	}
	else if (170 > WheelPos) {
		color.r = 3*WheelPos;
		color.g = (255 - 3*WheelPos);
		color.b = 0;
	}
	else {
		color.r = (255 - 3*WheelPos);
		color.g = 0;
		color.b = 3*WheelPos;
	}
	return color;
}