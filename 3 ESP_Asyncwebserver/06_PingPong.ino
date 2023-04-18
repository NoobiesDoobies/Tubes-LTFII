unsigned int timerPing = 0;
bool firstPing = true;
int timeOutPing = 5000;
void checkConnection(){
  if((millis() - timerPing) > timeOutPing){
    Serial.println("Device disconnected Time out: " + String(millis() - timerPing));
  } 
}