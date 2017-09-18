#include <ESP8266WiFi.h>
#include "wpa2_enterprise.h"
const char* ssid = "tue-wpa2";
const char* password = "";
extern "C" {
  #include "user_interface.h"
  
}

void setup()
{
    static const char* ssid = "MarkusHome";
    wifi_set_opmode(STATION_MODE);
    struct station_config wifi_config;
    memset(&wifi_config,0,sizeof(wifi_config));
    strcpy((char*)wifi_config.ssid,ssid);
    
    wifi_station_set_config(&wifi_config);
    wifi_station_clear_cert_key();
    //wifi_station_clear_enterprise_ca_cert();  
}

void loop()
{
  
}

