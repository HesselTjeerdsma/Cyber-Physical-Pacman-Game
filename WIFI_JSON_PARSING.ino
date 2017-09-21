#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Huawei AP";
const char* password = "teamtitanic";

const char* host = "http://pacman.autonomic-networks.ele.tue.nl/register";
const int httpsPort = 80;
HTTPClient http;

#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN 
Adafruit_SSD1306 display(OLED_RESET);
const char* type;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  while (!Serial) {
    // wait serial port initialization
  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  Serial.println();
  Serial.print("connecting to ");
  display.print("connecting to WiFI");
  display.display();
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  display.clearDisplay();
  display.display();
  display.print("WIFI connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("connecting to ");
  Serial.println(host);

}


void loop() {
  char json[400];
  // put your main code here, to run repeatedly:
  http.begin(host);
  String message = "{ \"name\": \"jeoktzeluf\" }";
  Serial.println("Send Post");
  int httpCode = http.POST(message);
  
  if(httpCode > 0){
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            payload.toCharArray(json, 400);
            Serial.println(payload);
        }
    } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }


  const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(11) + 12*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 260;
  DynamicJsonBuffer jsonBuffer(bufferSize);
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
  
  const char* type = root["type"]; // "ghost"
  http.end();
  Serial.println(type);
  display.clearDisplay();
  display.display();
  display.setCursor(5,5);
  display.print(type);
  display.display();
  delay(5000);
}
