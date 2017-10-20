#include <WiFi.h>
#include "esp_wpa2.h"

#include "Pacman_definitions.h"

#include "PacmanServer.h"
#include "PacmanScreen.h"
#include "PacmanOled.h"


const char* ssid = "tue-wpa2"; // your ssid
#define EAP_ID "d.a.w.markus@student.tue.nl"
#define EAP_USERNAME "s169013"
#define EAP_PASSWORD ""


HardwareSerial Serial1(2);



PacmanServer server("http://pacman.autonomic-networks.ele.tue.nl/register", "https://vrcfpa5qvi.execute-api.eu-west-2.amazonaws.com/dev/", "titanic", 50001);
PacmanScreen screen;
PacmanOled ring(16);  

int32_t xpos;
int32_t ypos;

float yaw;

long score;
int lives;

Status gameStatus;

bool energized;
bool quarantaine;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void handleEvents()
{
  portENTER_CRITICAL_ISR(&timerMux);
  server.handleEvents();
  portEXIT_CRITICAL_ISR(&timerMux);

}

void serialCommunication()
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
      portENTER_CRITICAL(&timerMux);
      server.setLocation(xpos,ypos);
      portEXIT_CRITICAL(&timerMux);
    }
    //update server events
    //set variables got by the server
    score = server.getScore();
    lives = server.getLives();
    quarantaine = server.inQuarantaine();
    energized = server.isEnergized();
    
    
  }
}

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
    bool pozyxArduino = false;
    do
    {
      Serial1.write(0x2);
      Serial.println("Trying connect Pozyx");
      delay(10);
      if(Serial1.available()>=2)
      {
        Serial.println("Serial available");
        if(Serial1.read()== 0x2 && Serial1.read() == 0x2)
        {
        pozyxArduino = true;
        Serial.println("Pozyx started");
        }
      }
      else
      {
      delay(20);
      }
    }while(pozyxArduino == false);
    while(Serial1.available())
    {
      Serial1.read();     
    }
    Serial1.write(0x0);
    while(Serial1.available() == false);
    Serial1.readBytes((uint8_t*)&xpos,4);
    Serial1.readBytes((uint8_t*)&ypos,4);
    //screen setup

    screen.begin();
    ring.begin();
    portENTER_CRITICAL(&timerMux);
    server.begin();
    server.setLocation(xpos,ypos);
    portEXIT_CRITICAL(&timerMux);
    gameStatus = server.getGameStatus();
    screen.setRole(server.getRole());

    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &handleEvents, true);
    timerAlarmWrite(timer, HANDLE_EVENTS_MICROSECONDS, true);
    timerAlarmEnable(timer);
    Serial.println("Setup done");
}


void loop ()
{

    serialCommunication();
    gameStatus = server.getGameStatus();
    Serial.println("Screenupdate");
    screen.update(lives,quarantaine,score,energized,gameStatus);
    ring.updateRing(N,yaw,lives,energized,quarantaine,gameStatus);


    
}



