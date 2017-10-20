#include <HTTPClient.h>
#include <ESP32WebServer.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PacmanServer.h"

PacmanServer::PacmanServer(String registerUrl, String algorithmUrl, String player_name, int serverPort)
:server(serverPort),
gameStatus(PLAYING),
quarantaine(0),
ended(0),
needUpdate(true),
score(0),
lives(3),
reg_url(registerUrl),
algo_url(algorithmUrl),
name(player_name)
{

	//setting up server on device

}

PacmanServer::~PacmanServer()
{
	http_register.end();
	http_location.end();
	http_location_error.end();
	http_food.end();
	http_cherry.end();
	http_energizer.end();
	http_cherry_spawned.end();
	http_collision.end();
	http_quarantine.end();
	http_game_over.end();
	http_game_won.end();
	http_direction.end();
	server.close();
}

void PacmanServer::begin()
{
	server.begin();
	server.on("/event/location", std::bind(&PacmanServer::event_location, this));
	server.on("/event/location_error", std::bind(&PacmanServer::event_location_error, this));
	server.on("/event/food", std::bind(&PacmanServer::event_food, this));
	server.on("/event/cherry", std::bind(&PacmanServer::event_cherry, this));
	server.on("/event/energizer", std::bind(&PacmanServer::event_energizer, this));
	server.on("/event/cherry_spawned", std::bind(&PacmanServer::event_cherry_spawned, this));
	server.on("/event/collision", std::bind(&PacmanServer::event_collision, this));
	server.on("/event/quarantine", std::bind(&PacmanServer::event_quarantine, this));
	server.on("/event/game_over", std::bind(&PacmanServer::event_game_over, this));
	server.on("/event/game_won", std::bind(&PacmanServer::event_game_won, this));
	
	int httpCode = 0;
	//register to server
	Serial.println("registration started");
	do
	{
		http_register.begin(reg_url);
		String message = "{ \"name\": \"" + name + "\" }";
		httpCode = http_register.POST(message);
	} while (httpCode != HTTP_CODE_OK);

	DynamicJsonBuffer jsonBuffer;
	String registrationResponse = http_register.getString();
	http_register.end();
	//set local variables
	JsonObject& root = jsonBuffer.parseObject(registrationResponse);
	if (root["type"] == "pacman")
	{
		character = PACMAN;
	}
	else
	{
		character = GHOST;
	}



	//start connection with algorithmserver
	http_register.begin(algo_url + "event/register");
	http_register.setReuse(true);
	http_register.addHeader("Content-Type", "application/json");
	
	http_location.begin(algo_url + "event/location");
	http_location.setReuse(true);
	http_location.addHeader("Content-Type", "application/json");

	http_location_error.begin(algo_url + "event/location_error");
	http_location_error.setReuse(true);
	http_location_error.addHeader("Content-Type", "application/json");

	http_food.begin(algo_url + "event/food");
	http_food.setReuse(true);
	http_food.addHeader("Content-Type", "application/json");

	http_cherry.begin(algo_url + "event/cherry");
	http_cherry.setReuse(true);
	http_cherry.addHeader("Content-Type", "application/json");

	http_energizer.begin(algo_url + "event/energizer");
	http_energizer.setReuse(true);
	http_energizer.addHeader("Content-Type", "application/json");

	http_cherry_spawned.begin(algo_url + "event/cherry_spawned");
	http_cherry_spawned.setReuse(true);
	http_cherry_spawned.addHeader("Content-Type", "application/json");

	http_collision.begin(algo_url + "event/collision");
	http_collision.setReuse(true);
	http_collision.addHeader("Content-Type", "application/json");

	http_quarantine.begin(algo_url + "event/quarantine");
	http_quarantine.setReuse(true);
	http_quarantine.addHeader("Content-Type", "application/json");

	http_game_over.begin(algo_url + "event/game_over");
	http_game_over.setReuse(true);
	http_game_over.addHeader("Content-Type", "application/json");

	http_game_won.begin(algo_url + "event/game_won");
	http_game_won.setReuse(true);
	http_game_won.addHeader("Content-Type", "application/json");


	http_direction.begin(algo_url + "event/direction");
	http_direction.setReuse(true);
	http_direction.addHeader("Content-Type", "application/json");

	//give register info to algo server
	http_register.POST(registrationResponse );
}

void PacmanServer::handleEvents()
{
	server.handleClient();
	Serial.println("events handled");
}

bool PacmanServer::needUpdatedLocation()
{
	return needUpdate;
}

void PacmanServer::setLocation(int32_t x_pixel, int32_t y_pixel)
{
	posX= 5* x_pixel;
	posY= 5* y_pixel;
	needUpdate = false;
}

Role PacmanServer::getRole()
{
	return character;
}

long PacmanServer::getScore()
{
	return score;
}

int PacmanServer::getLives()
{
	return lives;
}

Direction	PacmanServer::getDirection()
{
	http_direction.addHeader("Content-Type", "application/json");
	http_direction.POST("{\"direction\":True}");
	StaticJsonBuffer<JSON_OBJECT_SIZE(1)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(http_direction.getString());
	direction =Direction((int)root["direction"]);
	return direction;
}

bool PacmanServer::inQuarantaine()
{
	if (millis() > quarantaine)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PacmanServer::isEnergized()
{
	if (millis() > energizer)
	{
		return false;
	}
	else
	{
		return false;
	}
}

Status	PacmanServer::getGameStatus()
{
	if ((gameStatus == WON || gameStatus == LOST) && (millis() > ended))
	{
		abort();
	}
	return gameStatus;
}



void PacmanServer::event_location()
{
	http_location.addHeader("Content-Type", "application/json");
	http_location.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "{\"x\":" + String(posX) + ",\"y\":"+String(posY)+"}");
	Serial.println("location request");
	needUpdate = true;
}

void PacmanServer::event_location_error()
{
	http_location_error.addHeader("Content-Type", "application/json");
	http_location_error.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
	Serial.println("Location error");
	needUpdate = true;
}

void PacmanServer::event_food() 
{
	http_food.addHeader("Content-Type", "application/json");
	String message = server.arg(0);
	http_food.POST(message);
	server.send(200, "application/json; charset=utf-8", "");
	StaticJsonBuffer<JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(2)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(message);
	if (root["who"] == name)
	{
		score = root["score"];
	}

}

void PacmanServer::event_cherry()
{
	http_cherry.addHeader("Content-Type", "application/json");
	String message = server.arg(0);
	http_cherry.POST(message);
	server.send(200, "application/json; charset=utf-8", "");
	StaticJsonBuffer<JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(2)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(message);
	if (root["who"] == name)
	{
		score = root["score"];
	}
}

void PacmanServer::event_energizer()
{
	http_energizer.addHeader("Content-Type", "application/json");
	String message = server.arg(0);
	http_energizer.POST(message);
	server.send(200, "application/json; charset=utf-8", "");
	StaticJsonBuffer<JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(2)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(message);
	if (root["who"] == name)
	{
		score = root["score"];
		energizer = millis() + ENERGIZER;
	}
}

void PacmanServer::event_cherry_spawned()
{
	http_cherry_spawned.addHeader("Content-Type", "application/json");
	http_cherry_spawned.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
}

void PacmanServer::event_collision()
{
	http_collision.addHeader("Content-Type", "application/json");
	String message = server.arg(0);
	http_collision.POST(message);
	server.send(200, "application/json; charset=utf-8", "");
	StaticJsonBuffer<JSON_OBJECT_SIZE(3)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(message);
	lives = root["lives"];
	score = root["score"];
}

void PacmanServer::event_quarantine()
{
	http_quarantine.addHeader("Content-Type", "application/json");
	http_quarantine.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
	quarantaine = millis() + QUARANTAINE;
}

void PacmanServer::event_game_over()
{
	StaticJsonBuffer<JSON_OBJECT_SIZE(3)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(server.arg(0));
	lives = root["lives"];
	score = root["score"];
	ended = millis() + ENDSCREEN;
	server.send(200, "application/json; charset=utf-8", "");
	gameStatus = LOST;
}

void PacmanServer::event_game_won()
{
	StaticJsonBuffer<JSON_OBJECT_SIZE(3)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(server.arg(0));
	lives = root["lives"];
	score = root["score"];
	ended = millis() + ENDSCREEN;
	server.send(200, "application/json; charset=utf-8", "");
	gameStatus = WON;
}
