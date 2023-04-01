#include <HardwareSerial.h>
#include <Arduino.h>
#include <ArduinoJson.h>



void setup() {
  Serial.begin(115200);
  initWiFi();
  initSPIFFS();


    // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

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

   server.on("/updateJoyStickValue", HTTP_POST, [](AsyncWebServerRequest *request){  
      int params = request->params();
      AsyncWebParameter *p = request->getParam(0);
      joystick.x = atoi(p->value().c_str());
      p = request->getParam(1);
      joystick.y = atoi(p->value().c_str());
      
      request->send(SPIFFS, "/index.html", "text/html");
   });
   

  server.serveStatic("/", SPIFFS, "/");

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
  Serial.println("x: " + String(x) + "\ty: " + String(y));
}
