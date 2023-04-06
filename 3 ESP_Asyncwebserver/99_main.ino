#include <HardwareSerial.h>
#include <Arduino.h>
#include <ArduinoJson.h>


void setup() {
  Serial.begin(115200);
  initWiFi();
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("GETTING /");
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      json["status"] = "ok";
      json["ssid"] = WiFi.SSID();
      json["ip"] = WiFi.softAPIP().toString();
      serializeJson(json, *response);
      request->send(response);
    });
   server.on("/posts", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("GETTING");
      int paramsNr = request->params();
      Serial.println(paramsNr);
      for(int i=0;i<paramsNr;i++){
 
         AsyncWebParameter* p = request->getParam(i);
     
         Serial.print("Param name: ");
         Serial.println(p->name());
     
         Serial.print("Param value: ");
         Serial.println(p->value());
     
         Serial.println("------");
      }
      
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      json["status"] = "ok";
      json["ssid"] = WiFi.SSID();
      json["ip"] = WiFi.softAPIP().toString();
      serializeJson(json, *response);
      request->send(response);
   });
   server.on("/posts", HTTP_POST, [](AsyncWebServerRequest *request){  
      Serial.println("ACTION!");
      
      int params = request->params();
      for (int i = 0; i < params; i++)
      {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
      
      
      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      json["status"] = "ok";
      json["ssid"] = WiFi.SSID();
      json["ip"] = WiFi.softAPIP().toString();
      serializeJson(json, *response);
      request->send(response);
   });
   

//  server.serveStatic("/", SPIFFS, "/");

  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);

  // Start server
  server.begin();
}


void loop() {
  updatePositionXY();
//  Serial.println("x: " + String(x) + "\ty: " + String(y));
}
