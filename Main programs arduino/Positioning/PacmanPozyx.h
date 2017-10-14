#pragma once
#include <Arduino.h>

#include <Pozyx.h>
#include <Pozyx_definitions.h>
#include <Wire.h>

class PacmanPozyx
{
public:
	PacmanPozyx(int nAnchors, uint16_t *anchors, int32_t *anchors_x, int32_t *anchors_y, int32_t *anchors_z, int strength_filter);
	~PacmanPozyx();

	int32_t* getLocation();
	void doPositioning();
	float32_t getOrientation();

private:
	void setAnchorsManual(int nAnchors, uint16_t *anchors, int32_t *anchors_x, int32_t *anchors_y, int32_t *anchors_z);
	
	const uint8_t algorithm;
	const uint8_t dimension;
	const uint8_t strength_filter;
	coordinates_t position;
};