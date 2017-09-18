

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Huawei AP";
const char* password = "teamtitanic";

const char* host = "http://pacman.autonomic-networks.ele.tue.nl/register";
const int httpsPort = 80;
HTTPClient http;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //connect to wifi hotspot
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("connecting to ");
  Serial.println(host);

  
  
}


void loop() {
  // put your main code here, to run repeatedly:
  http.begin(host);
  String message = "{ \"name\": \"Grappig\" }";
  Serial.println("Send Post");
  int httpCode = http.POST(message);
  
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
  delay(5000);
}
