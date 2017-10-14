#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN 
Adafruit_SSD1306 display(OLED_RESET);
const char* type;
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait serial port initialization
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  

}

int jsonparser("\"" + const char* json + "\"") {
  jsonBuffer(bufferSize);
  JsonObject& root = jsonBuffer.parseObject(json);
  JsonArray& food_locations = root["food_locations"];
  int food_locations0_y = food_locations[0]["y"]; // 7500
  long food_locations0_x = food_locations[0]["x"]; // 72500
  int food_locations1_y = food_locations[1]["y"]; // 7500
  long food_locations1_x = food_locations[1]["x"]; // 70000
  int food_locations2_y = food_locations[2]["y"]; // 7500
  long food_locations2_x = food_locations[2]["x"]; // 67500
  int food_locations3_y = food_locations[3]["y"]; // 10000
  long food_locations3_x = food_locations[3]["x"]; // 53750
  int energizer_locations0_y = root["energizer_locations"][0]["y"]; // 7500
  long energizer_locations0_x = root["energizer_locations"][0]["x"]; // 75000
  type = root["type"]; // "ghost"

  }



void loop() {
  
}
