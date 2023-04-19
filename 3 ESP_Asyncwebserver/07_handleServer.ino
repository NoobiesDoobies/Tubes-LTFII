#include <ArduinoJson.h>

int calibrate = 0;

void handleHTTP(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println("GETTING /");
        timerPing = millis();
        firstPing = false;
        AsyncResponseStream *response = request->beginResponseStream("application/json");
        DynamicJsonDocument json(1024);
        json["message"] = "PONG";
        json["status"] = "ok";
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
      Serial.print(mode+"\t");
      if(mode.equals(String("Arrows"))){
          // Serial.println("Arrows");
          p = request->getParam(1);
          x = p->value().toFloat();
          p = request->getParam(2);
          y = p->value().toFloat();
          p = request->getParam(3);
          z = p->value().toFloat();
      }
      else if(mode.equals(String("JoyStick"))){
        // Serial.println("JOYSTICK");
          p = request->getParam(1);
          x = p->value().toFloat();
          p = request->getParam(2);
          y = p->value().toFloat();
          p = request->getParam(3);
          z = p->value().toFloat();
      }
      else if(mode.equals(String("Slider"))){
          // Serial.println("SLIDER");
          p = request->getParam(4);
          calibrate = p->value().toInt();
          if(calibrate){
            Serial.print("Calibrating\t");
            arm1Offset = arm1Offset + arm1Angle;
            arm2Offset = arm2Offset + arm2Angle;
          }
          p = request->getParam(1);
          arm1Angle = p->value().toFloat();
          p = request->getParam(2);
          arm2Angle = p->value().toFloat();
          p = request->getParam(3);
          endEffectorAngle = p->value().toFloat();
      }

        if(mode[0] == 'S'){
         Serial.println("Arm1: " + String(arm1Angle) + "\tArm2: " + String(arm2Angle) + "\tEnd Effector: " + String(endEffectorAngle) + "\tOffset1: " + String(arm1Offset) + "\tOffset2:  " + String(arm2Offset) + "\tCalibrate: " + String(calibrate));

        }
        else{
         Serial.println("x: " + String(x) + "\ty: " + String(y) + "\tz: " + String(z));
        }

      AsyncResponseStream *response = request->beginResponseStream("application/json");
      DynamicJsonDocument json(1024);
      json["status"] = "ok";
      json["ssid"] = WiFi.SSID();
      json["ip"] = WiFi.softAPIP().toString();
      serializeJson(json, *response);
      request->send(response);
   });

}