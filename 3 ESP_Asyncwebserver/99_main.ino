#include <HardwareSerial.h>
#include <Arduino.h>


int timer = 0;



void setup() {
  Serial.begin(115200);

  // initEEPROM();
  initWiFi(); 

  while(!Serial.available()){}
  int maxVelocity = Serial.parseInt();
  int accelaration = Serial.parseInt();
  Arm1.setMaxSpeed(maxVelocity);
  Arm1.setAcceleration(accelaration);

  Serial.println("MaxSpeed = " + String(maxVelocity) + "\tAccel: " + String(accelaration));
  
  initActuator();
    
  handleHTTP();


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
  // if(!firstPing){
  //   checkConnection();
  // }
}
