#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "kontol";
const char* password = "kontol1234";
//void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
//   
//  Serial.println("Station connected");
//   
//  for(int i = 0; i< 6; i++){
//     
//    Serial.printf("%02X", info.sta_connected.mac[i]);  
//    if(i<5)Serial.print(":");
//  }
// 
//  Serial.println("\n------------");
//}
//void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
//   
//  Serial.println("Station disconnected");
//   
//  for(int i = 0; i< 6; i++){
//     
//    Serial.printf("%02X", info.sta_disconnected.mac[i]);  
//    if(i<5)Serial.print(":");
//  }
// 
//  Serial.println("\n------------");
//}

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_AP);
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);


  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

//  // Register a callback for client disconnect event
//  WiFi.onEvent(WiFiStationConnected, SYSTEM_EVENT_AP_STACONNECTED);
//  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_AP_STADISCONNECTED);

}
