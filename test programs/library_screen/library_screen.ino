#include "Pacman_definitions.h"

#include "PacmanScreen.h"
PacmanScreen screen(1);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial.println("running screen");
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("hoi");
}
