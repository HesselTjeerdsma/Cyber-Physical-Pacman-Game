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
}

PacmanServer::~PacmanServer()
{
	http.end();
	server.close();
}

void PacmanServer::begin()
{
	int httpCode = 0;
	//register to server
	Serial.println("registration started");
	do
	{
		http.begin(reg_url);
		String message = "{ \"name\": \"" + name + "\" }";
		httpCode = http.POST(message);
	} while (httpCode != HTTP_CODE_OK);

	DynamicJsonBuffer jsonBuffer;
	String registrationResponse = http.getString();
	http.end();
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
	http.begin(algo_url);
	http.setReuse(true);
	http.addHeader("Content-Type", "application/json");
	http.POST(registrationResponse);
}

void PacmanServer::handleEvents()
{
	server.handleClient();
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
	http.addHeader("Content-Type", "application/json");
	http.POST("{\"direction\":True}");
	StaticJsonBuffer<JSON_OBJECT_SIZE(1)> jsonBuffer;
	JsonObject& root = jsonBuffer.parseObject(http.getString());
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
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "{\"x\":" + String(posX) + ",\"y\":"+String(posY)+"}");
	needUpdate = true;
}

void PacmanServer::event_location_error()
{
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
	needUpdate = true;
}

void PacmanServer::event_food() 
{
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");

}

void PacmanServer::event_cherry()
{
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
}

void PacmanServer::event_energizer()
{
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
}

void PacmanServer::event_cherry_spawned()
{
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
}

void PacmanServer::event_collision()
{
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
	server.send(200, "application/json; charset=utf-8", "");
}

void PacmanServer::event_quarantine()
{
	http.addHeader("Content-Type", "application/json");
	http.POST(server.arg(0));
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
