#pragma once
#include <Arduino.h>
typedef enum {
	PACMAN,
	GHOST
} Role;

typedef enum {
	PLAYING,
	LOST,
	WON
}Status;

class PacmanScreen
{
public:
	PacmanScreen(uint8_t screenAdress, int sda, int scl, Role role, int *ledpins);
	~PacmanScreen();

	void update(int lives, bool inQuarantaine, int score, Status gamestatus);

private:
	void drawRole();
	void beginScreen();
	void inGame(int lives, bool inQuarantaine, int score);
	void endGame(Status gamestatus);

	SSD1306 display;
	int *leds;
	bool quarantaine_leds;
	Role character;
	long quarantaine_timer;
	long start_timer;
};