#include <HardwareSerial.h>
#include <Arduino.h>
#include <ArduinoJson.h>



void setup() {
  Serial.begin(115200);
  initWiFi();
//  initSPIFFS();


    // Web Server Root URL
//  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send(SPIFFS, "/index.html", "text/html");
//  });

//  server.on("/updatePos", HTTP_GET, [](AsyncWebServerRequest *request){
//    AsyncResponseStream *response = request->beginResponseStream("application/json");
//      DynamicJsonDocument json(1024);
//      json["x_pos"] = x_pos;
//      json["y_pos"] = y_pos;
//      json["theta_pos"] = theta_pos;
//      Serial.print("x_pos: ");
//      Serial.println(x_pos);
//      serializeJson(json, *response);
//      request->send(response);
//  });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", "Hello world");
    });
   server.on("/posts", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("GETTING");
    request->send(200, "text/plain", "HALLOO");
   });
   server.on("/posts", HTTP_POST, [](AsyncWebServerRequest *request){  
      Serial.println("ACTION!");
    
      int params = request->params();
      for (int i = 0; i < params; i++)
      {
        AsyncWebParameter* p = request->getParam(i);
        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
      
      AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "OK");
      response->addHeader("Test-Header", "My Header value");
      
      request->send(200, "text/plain", "OK");
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
