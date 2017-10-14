#include <WiFi.h>
#include "esp_wpa2.h"
#include "PacmanServer.h"


const char* ssid = "tue-wpa2"; // your ssid
#define EAP_ID "h.a.tjeerdsma@student.tue.nl"
#define EAP_USERNAME "s161743"
#define EAP_PASSWORD "cYxD35$1"

PacmanServer server("http://pacman.autonomic-networks.ele.tue.nl/register", "https://vrcfpa5qvi.execute-api.eu-west-2.amazonaws.com/dev", "titanic", 50001);
  

void setup() {
    Serial.begin(115200);
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
}


void loop ()
{
  delay(1000000);
}


