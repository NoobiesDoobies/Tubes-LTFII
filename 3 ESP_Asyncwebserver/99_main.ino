#include <ArduinoJson.h>
#include <HardwareSerial.h>
#include <Arduino.h>


int timer = 0;
int calibrate = 0;

void setup() {
  Serial.begin(115200);

  initWiFi(); 

  while(!Serial.available()){
    
  }
  int maxVelocity = Serial.parseInt();
  int accelaration = Serial.parseInt();
  Arm1.setMaxSpeed(maxVelocity);
  Arm1.setAcceleration(accelaration);

  Serial.println("MaxSpeed = " + String(maxVelocity) + "\tAccel: " + String(accelaration));
  initActuator();
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
//      int paramsNr = request->params();
//      Serial.println(paramsNr);
//      for(int i=0;i<paramsNr;i++){
// 
//         AsyncWebParameter* p = request->getParam(i);
//     
//         Serial.print("Param name: ");
//         Serial.println(p->name());
//     
//         Serial.print("Param value: ");
//         Serial.println(p->value());
//     
//         Serial.println("------");
//      }
//
//      int params = request->params();
//      for (int i = 0; i < params; i++)
//      {
//        AsyncWebParameter* p = request->getParam(i);
//        Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
//      }

      AsyncWebParameter* p = request->getParam(0);
//      const char *mode = p->value().c_str();
      String mode = String(p->value());
      Serial.println(mode);
      if(mode.equals(String("Arrows"))){
          p = request->getParam(1);
          x = p->value().toFloat();
          p = request->getParam(2);
          y = p->value().toFloat();
          p = request->getParam(3);
          z = p->value().toFloat();
      }
      else if(mode.equals(String("JoyStick"))){
        Serial.println("JOYSTICK");
          p = request->getParam(1);
          x = p->value().toFloat();
          p = request->getParam(2);
          y = p->value().toFloat();
          p = request->getParam(3);
          z = p->value().toFloat();
      }
      else if(mode.equals(String("Slider"))){
          Serial.println("SLIDER");
          p = request->getParam(1);
          arm1Angle = p->value().toFloat();
          p = request->getParam(2);
          arm2Angle = p->value().toFloat();
          p = request->getParam(3);
          endEffectorAngle = p->value().toFloat();
          p = request->getParam(4);
          calibrate = p->value().toInt();
      }

        if(mode[0] == 'S'){
//          Serial.println("Arm1: " + String(arm1Angle) + "\tArm2: " + String(arm2Angle) + "\tEnd Effector: " + String(endEffectorAngle) + "\tCalibrate: " + String(calibrate));
          if(calibrate){
            arm1Offset = arm1Angle;
            arm2Offset = arm2Angle;
          }
        }
        else{
//          Serial.println("x: " + String(x) + "\ty: " + String(y) + "\tz: " + String(z));
        }

      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      json["status"] = "ok";
      json["ssid"] = WiFi.SSID();
      json["ip"] = WiFi.softAPIP().toString();
      serializeJson(json, *response);
      request->send(response);
   });

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
  moveActuator();
}
