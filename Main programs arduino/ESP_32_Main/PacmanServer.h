#pragma once
#include <HTTPClient.h>
#include <ESP32WebServer.h>
#include <Arduino.h>
#include <ArduinoJson.h>

typedef enum{
	PLAYING,
	LOST,
	WON
}Status;

typedef enum {
	PACMAN,
	GHOST
} Role;

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
	NNW,
} Direction;

class PacmanServer
{
public:
	PacmanServer(String registerUrl, String algorithmUrl, String name = "titanic", int serverPort = 50001);
	~PacmanServer();

	void begin();

	//void begin(String registerUrl, int serverPort);
	void handleEvents();
	void setLocation(int x, int y);
	Role getRole();
	int getScore();
	int getLives();
	Direction getDirection();
	bool inQuarantaine();
	Status getGameStatus();


private:
	
	//classes needed for internet communication
	HTTPClient http;
	ESP32WebServer server;

	//server side request handler
	void event_location();
	void event_location_error();
	void event_food();
	void event_cherry();
	void event_energizer();
	void event_cherry_spawned();
	void event_collision();
	void event_quarantine();
	void event_game_over();
	void event_game_won();

	//game variables
	long posX;
	long posY;
	int score;
	int lives;
	Direction direction;
	unsigned long quarantaine;
	Status gameStatus;
	Role character;
	const String algo_url;
	const String reg_url;
	const String name;
};
