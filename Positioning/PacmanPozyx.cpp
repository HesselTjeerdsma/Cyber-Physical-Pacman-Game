#include "PacmanPozyx.h"
#include <Arduino.h>
#include <Pozyx.h>
#include <Pozyx_definitions.h>
#include <Wire.h>

PacmanPozyx::PacmanPozyx(int nAnchors, uint16_t *anchors, int32_t *anchors_x, int32_t *anchors_y, int32_t *anchors_z, int strength_filter)
:
	algorithm(POZYX_POS_ALG_TRACKING),
	dimension(POZYX_3D),
	strength_filter(strength_filter)

{
	Pozyx.begin();
	Pozyx.clearDevices();
	setAnchorsManual(nAnchors, anchors, anchors_x, anchors_y, anchors_z);
	Pozyx.setPositionFilter(POZYX_POS_FILTER_MOVING_AVERAGE, strength_filter);
	
	
}

PacmanPozyx::~PacmanPozyx()
{

}

int32_t* PacmanPozyx::getLocation()
{
	return &position.x;

}

void PacmanPozyx::doPositioning()
{
	while (Pozyx.doPositioning(&position, dimension, 1000, algorithm) != POZYX_SUCCESS);
}

float32_t PacmanPozyx::getOrientation()
{
	float32_t yaw;
	while (Pozyx.getEulerHeading_deg(&yaw) != POZYX_SUCCESS);

	return yaw;
}

void PacmanPozyx::setAnchorsManual(int nAnchors, uint16_t *anchors, int32_t *anchors_x, int32_t *anchors_y, int32_t *anchors_z)
{
	for (int i = 0; i < nAnchors; i++)
	{
		device_coordinates_t anchor;
		anchor.network_id = anchors[i];
		anchor.flag = POZYX_ANCHOR;
		anchor.pos.x = anchors_x[i];
		anchor.pos.y = anchors_y[i];
		anchor.pos.z = anchors_z[i];
		Pozyx.addDevice(anchor);
	}
	if (nAnchors > 4) {
		Pozyx.setSelectionOfAnchors(POZYX_ANCHOR_SEL_AUTO, nAnchors);
	}
}


