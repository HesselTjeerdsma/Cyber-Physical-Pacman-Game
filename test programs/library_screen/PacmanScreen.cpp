#include <Wire.h>
#include "SSD1306.h"
#include <Arduino.h>

#include "PacmanScreen.h"
#include "images.h"

PacmanScreen::PacmanScreen(int)
	:display(SCREENADRESS, SCREENPIN_SDA, SCREENPIN_SCL),
	quarantaine_timer(0),
	quarantaine_leds(true),
	start_timer(millis())
{
	Serial.begin(115200);
	Serial.println("running screen");
	
	pinMode(SCREENPIN_SDA, OUTPUT);
	pinMode(SCREENPIN_SCL, OUTPUT);
	Serial.println("setting up screen");
	display->init();
	
	display.flipScreenVertically();
	display.setFont(ArialMT_Plain_24);
	Serial.println("building begin screen");
	display.clear();
	display.drawXbm(0, 0, 128, 64, Startup);
	display.display();
	
	Serial.println("screen builded");
	
	pinMode(PIN_LED1, OUTPUT);
	pinMode(PIN_LED2, OUTPUT);
	pinMode(PIN_LED3, OUTPUT);
	
	Serial.println("pin setted");
}

PacmanScreen::~PacmanScreen()
{

}

void PacmanScreen::setRole(Role role)
{
	character = role;
}

void PacmanScreen::update(int lives, bool quarantaine, int score, bool energized, Status gamestatus)
{
	if (millis() < start_timer + STARTSCREEN)
	{
		return;
	}
	else if (millis() < start_timer + STARTSCREEN + ROLESCREEN)
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
	if (quarantaine == true && millis() > quarantaine_timer)
	{
		quarantaine_timer = millis() + LED_BLINK;
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


