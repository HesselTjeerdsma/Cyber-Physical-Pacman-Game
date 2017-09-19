

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(50001);



const char* ssid = "Huawei AP";
const char* password = "teamtitanic";

char* host = NULL;
String message = "";
int httpCode = 0;
HTTPClient http;
int i=0;
void handleRoot() {
  i++;
  Serial.print("Got request: ");
  Serial.println(i);
  Serial.println(server.args());
  Serial.println(server.arg(0));
  server.send(200,"text/plain", "hello from esp8266!");
}

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
  server.begin();

  server.on("/event/location", handleRoot);
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
  delay(100);
  
  
}
