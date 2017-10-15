#pragma once
#include <HTTPClient.h>
#include <ESP32WebServer.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Pacman_definitions.h"



class PacmanServer
{
public:
	PacmanServer(String registerUrl, String algorithmUrl, String name = "titanic", int serverPort = 50001);
	~PacmanServer();

	void begin();

	void handleEvents();
	bool needUpdatedLocation();
	void setLocation(int32_t x, int32_t y);
	Role getRole();
	long getScore();
	int getLives();
	Direction getDirection();
	bool inQuarantaine();
	bool isEnergized();
	Status getGameStatus();
	void endGame();


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
	bool needUpdate;
	long score;
	int lives;
	Direction direction;
	unsigned long quarantaine;
	unsigned long ended;
	unsigned long energizer;
	Status gameStatus;
	Role character;
	const String algo_url;
	const String reg_url;
	const String name;
};
