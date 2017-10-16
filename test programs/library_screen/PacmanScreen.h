#pragma once
#include <Arduino.h>
#include "SSD1306.h"
#include "Pacman_definitions.h"

class PacmanScreen
{
public:
	PacmanScreen(int i);
	~PacmanScreen();

	void setRole(Role role);
	void update(int lives, bool inQuarantaine, int score, bool energized, Status gamestatus);

private:
	void drawRole();
	void inGame(int lives, bool inQuarantaine, int score, bool energized);
	void endGame(Status gamestatus);

	SSD1306 display;
	const int *leds;
	bool quarantaine_leds;
	Role character;
	long quarantaine_timer;
	const long start_timer;
};
