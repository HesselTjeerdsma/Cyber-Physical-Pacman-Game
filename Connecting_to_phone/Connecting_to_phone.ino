

#include <WiFi.h>
#include "esp_wpa2.h"
#include <HTTPClient.h>
#include <ESP32WebServer.h>

ESP32WebServer server(50001);


const char* ssid = "tue-wpa2"; // your ssid
#define EAP_ID "d.a.w.markus@student.tue.nl"
#define EAP_USERNAME "s169013"
#define EAP_PASSWORD ""

char* host = NULL;
String message = "";
int httpCode = 0;
HTTPClient http;
int i=0;

void event_location(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Location request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_food(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Food request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_cherry(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Cherry request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_energizer(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Energizer request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_cherry_spawned(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Cherry Spawned request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_collision(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Collision request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_quarantine(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Quarantine request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_game_over(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Game over request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void event_game_won(){
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println("Game won request");
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"application/json; charset=utf-8", "hello from esp8266!");
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //connect to wifi hotspot
  delay(10);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  
  // WPA2 enterprise magic starts here
  WiFi.disconnect(true);      
  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ID, strlen(EAP_ID));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_USERNAME, strlen(EAP_USERNAME));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);
  // WPA2 enterprise magic ends here
  WiFi.begin(ssid);
    
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //wifi is setup

  //setup http server
  server.begin();
  
  //setting up all listing ports
  server.on("/event/location", event_location);
  server.on("/event/food", event_food);
  server.on("/event/cherry", event_cherry);
  server.on("/event/energizer", event_energizer);
  server.on("/event/cherry_spawned", event_cherry_spawned);
  server.on("/event/collision", event_collision);
  server.on("/event/quarantine", event_quarantine);
  server.on("/event/game_over", event_game_over);
  server.on("/event/game_won", event_game_won);


  //register to server
  host = "http://pacman.autonomic-networks.ele.tue.nl/register";
  Serial.print("connecting to ");
  Serial.println(host);  
  http.begin(host);
  message = "{ \"name\": \"Grappig\" }";
  Serial.println("Send Post");
  httpCode = http.POST(message);
  
  if(httpCode > 0){
    Serial.printf("[HTTP] POST... code: %d\n", httpCode);
  if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
        }
    } else {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  
  http.end();
  
}


void loop() {
  // put your main code here, to run repeatedly:
  

  server.handleClient();
  delay(50);
  
  
}
