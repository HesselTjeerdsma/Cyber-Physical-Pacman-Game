#include "PacmanPozyx.h"

uint8_t num_anchors = 4;                                    // the number of anchors
uint16_t anchors[4] = {0x6847, 0x6877, 0x6170, 0x6169};     // the network id of the anchors: change these to the network ids of your anchors.
int32_t anchors_x[4] = {0, 819, 11745, 17923};               // anchor x-coorindates in mm
int32_t anchors_y[4] = {5, 25828, 0, 25836};                  // anchor y-coordinates in mm
int32_t anchors_z[4] = {2499, 2595, 2621, 2655};              // anchor z-coordinates in mm
int strength_filter = 3;
PacmanPozyx pozyx(num_anchors, anchors,anchors_x,anchors_y,anchors_z, strength_filter);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

pozyx.doPositioning();
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available())
 {
  switch(Serial.read())
  {
     case 0x0:
       int32_t* location;
       location =  pozyx.getLocation();
       Serial.write((uint8_t*)location, 8);
       pozyx.doPositioning();
     break;
     case 0x1:
       float32_t orientation;
       orientation = pozyx.getOrientation();
       Serial.write((uint8_t*)&orientation,4);
     break;
  }
}
}

