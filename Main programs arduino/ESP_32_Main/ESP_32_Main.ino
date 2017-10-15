#include <WiFi.h>
#include "esp_wpa2.h"

#include "Pacman_definitions.h"

#include "PacmanServer.h"
#include "PacmanScreen.h"
#include "PacmanOled.h"


const char* ssid = "tue-wpa2"; // your ssid
#define EAP_ID "h.a.tjeerdsma@student.tue.nl"
#define EAP_USERNAME "s161743"
#define EAP_PASSWORD "cYxD35$1"


HardwareSerial Serial1(2);

int ledpins[] = {7,8,9};
int sda_pin = 21;
int scl_pin = 22;

PacmanServer server("http://pacman.autonomic-networks.ele.tue.nl/register", "https://vrcfpa5qvi.execute-api.eu-west-2.amazonaws.com/dev", "titanic", 50001);
PacmanScreen screen(ledpins);  

int32_t xpos;
int32_t ypos;

float yaw;

long score;
int lives;

Status gameStatus;

bool energized;
bool quarantaine;

void setup() {
    Serial.begin(115200);
    Serial1.begin(115200);
    delay(10);

    Serial.println();
    Serial.print("Connecting to ");
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

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
    gameStatus = server.getGameStatus();
    screen.setRole(server.getRole());
    
}


void loop ()
{

  if(gameStatus == PLAYING)
  {
    //get yaw and set yaw
    Serial1.write(0x1);
    while(Serial1.available() == false);
    Serial1.readBytes((uint8_t*)&yaw,4);
  
    //get new location
    if(server.needUpdatedLocation() == true)
    {
      Serial1.write(0x0);
      while(Serial1.available() == false);
      Serial1.readBytes((uint8_t*)&xpos,4);
      Serial1.readBytes((uint8_t*)&ypos,4);
      server.setLocation(xpos,ypos);
    }
    //update server events
    
    //set variables got by the server
    score = server.getScore();
    lives = server.getLives();
    quarantaine = server.inQuarantaine();
    energized = server.isEnergized();
    
    
  }

  
  
    server.handleEvents();
    gameStatus = server.getGameStatus();

    screen.update(lives,quarantaine,score,energized,gameStatus);


    
}



