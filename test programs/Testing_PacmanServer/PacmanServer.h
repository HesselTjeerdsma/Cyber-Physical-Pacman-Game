#pragma once
#include <HTTPClient.h>
#include <ESP32WebServer.h>
#include <Arduino.h>

typedef enum Status{
	PLAYING,
	LOST,
	WON
}

class PacmanServer
{
public:
	PacmanServer(String registerUrl, String name = "titanic", int serverPort = 50001);
	~PacmanServer();

	//void begin(String registerUrl, int serverPort);
	void handleEvents();
	void setLocation(int x, int y);
	void getFood();
	void getCherry();
	void getEnergizer();
	void getSpawned();
	void getCollision();
	bool inQuarantine();
	Status getGameStatus();

private:
	HTTPClient http;
	ESP32WebServer server;
	void event_location();
	void event_food();
	void event_cherry();
	void event_energizer();
	void event_cherry_spawned();
	void event_collision();
	void event_quarantine();
	void event_event_game_over();
	void event_event_game_won();
	int posX;
	int posY;
	unsigned long quarantaine;
	Status gameStatus;
};