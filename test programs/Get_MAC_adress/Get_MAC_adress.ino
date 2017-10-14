#include <WiFi.h>

byte mac[6];

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.print("Program Start...");

    WiFi.begin();
    Serial.println("WiFi began");
    WiFi.macAddress(mac);
    
    Serial.print("MAC: ");
    Serial.print(mac[0],HEX);
    Serial.print(":");
    Serial.print(mac[1],HEX);
    Serial.print(":");
    Serial.print(mac[2],HEX);
    Serial.print(":");
    Serial.print(mac[3],HEX);
    Serial.print(":");
    Serial.print(mac[4],HEX);
    Serial.print(":");
    Serial.println(mac[5],HEX);

}

void loop(){

}
