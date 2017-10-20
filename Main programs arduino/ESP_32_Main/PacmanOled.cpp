#include <Arduino.h>
#include "PacmanOled.h"

PacmanOled::PacmanOled(int num_leds)
:
	nLeds(num_leds),
	energized_timer(0),
	rainbowcolor(0),
	quarantaine_color(true),
	quarantaine_timer(0)
{


}

PacmanOled::~PacmanOled()
{
	free(leds);
}

void PacmanOled::begin()
{

	leds = (CRGB*)malloc(sizeof(CRGB)*nLeds);
	FastLED.setBrightness(BRIGHTNESS);
	FastLED.addLeds<WS2812B, OLEDPIN>(leds, nLeds);
	oneColorRing(COLOR_BEGIN);

	FastLED.show();
}

void PacmanOled::updateRing(Direction direction, float orientation, int lives, bool energized, bool quarantaine, Status gameStatus)
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
			Serial.println("print direction");
			directionRing(direction, orientation);
			Serial.println("printed direction");
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
	for (int i = 0; i < nLeds; i++)
	{
		leds[i] = color;
	}
}

void PacmanOled::energizedRing()
{
	if (millis() > energized_timer)
	{
		energized_timer = millis() + ENERGIZER_SPEED;
		rainbowcolor = (rainbowcolor + 1) % 256;
		for (int i = 0; i < nLeds; i++)
		{
			leds[i] = wheel((i * 256 / nLeds + rainbowcolor) % 256);
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

void PacmanOled::directionRing(Direction direction, float orientation)
{
	oneColorRing(COLOR_BACKGROUND);
	int i = (int)(16-(0.5 + orientation / 22.5) + (float)direction) % nLeds;
	leds[i] = COLOR_DIRECTION;
}

CRGB PacmanOled::wheel(int WheelPos) {
	CRGB color;
	if (85 > WheelPos) {
		color.r = 0;
		color.g = WheelPos;
		color.b = (255 - WheelPos);
	}
	else if (170 > WheelPos) {
		color.r = WheelPos;
		color.g = (255 - WheelPos);
		color.b = 0;
	}
	else {
		color.r = (255 - WheelPos);
		color.g = 0;
		color.b = WheelPos;
	}
	return color;
}