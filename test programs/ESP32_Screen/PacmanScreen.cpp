#include <Wire.h>
#include "SSD1306.h"
#include <Arduino.h>

#include "PacmanScreen.h"
#include "images.h"

PacmanScreen::PacmanScreen(uint8_t screenAdress, int sda, int scl, Role role, int *ledpins)
	:display(screenAdress, sda, scl),
	character(role),
	leds(ledpins),
	quarantaine_timer(0),
	quarantaine_leds(true),
	start_timer(millis())
{
	beginScreen();
	display.init();
	display.flipScreenVertically();
	display.setFont(ArialMT_Plain_24);

	pinMode(leds[0], OUTPUT);
	pinMode(leds[1], OUTPUT);
	pinMode(leds[2], OUTPUT);
}

PacmanScreen::~PacmanScreen()
{

}



void PacmanScreen::update(int lives, bool quarantaine, int score, bool energized, Status gamestatus)
{
	if (millis() < start_timer + 2000)
	{
		return;
	}
	else if (millis() < start_timer + 6000)
	{
		drawRole();
	}
	else
	{
		
		if (gamestatus == PLAYING)
		{
			inGame(lives, quarantaine, score, energized);
		}
		else
		{
			endGame(gamestatus);
		}
		
	}
}

void PacmanScreen::inGame(int lives, bool quarantaine, int score, bool energized)
{
	display.clear();
	if (character == PACMAN)
	{
		display.drawXbm(0, 0, 128, 64, Pacman_Small);
	}
	else if (character == GHOST)
	{
		display.drawXbm(0, 0, 128, 64, Ghost_Small);
	}
  if (energized == true)
  {
    display.drawXbm(0, 0, 128, 64, Energizer);
  }
	display.setTextAlignment(TEXT_ALIGN_CENTER);
	display.drawString(64, 25, String(score));
	display.display();
	if (quarantaine == true && millis() > quarantaine_timer + 500)
	{
		quarantaine_timer = millis();
		quarantaine_leds = !quarantaine_leds;
	}

	if (quarantaine == true & quarantaine_leds == false)
	{
		lives = 0;
	}

	switch (lives)
	{
	case 3:
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], HIGH);
		break;
	case 2:
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], HIGH);
		digitalWrite(leds[2], LOW);
		break;
	case 1:
		digitalWrite(leds[0], HIGH);
		digitalWrite(leds[1], LOW);
		digitalWrite(leds[2], LOW);
		break;
	case 0:
		digitalWrite(leds[0], LOW);
		digitalWrite(leds[1], LOW);
		digitalWrite(leds[2], LOW);
		break;
	}
}

void PacmanScreen::endGame(Status gamestatus)
{
	display.clear();
	if (gamestatus == WON)
	{
		display.drawXbm(0, 0, 128, 64, Winner);
	}
	else
	{
		display.drawXbm(0, 0, 128, 64, Loser);
	}
	display.display();
}

void PacmanScreen::drawRole()
{
	display.clear();
	if (character == PACMAN)
	{
		display.drawXbm(0, 0, 128, 64, Pacman);
	}
	else if (character == GHOST)
	{
		display.drawXbm(0, 0, 128, 64, Ghost);
	}
	display.display();
}

void PacmanScreen::beginScreen()
{
		display.clear();
		display.drawXbm(0, 0, 128, 64, Startup);
		display.display();
}
