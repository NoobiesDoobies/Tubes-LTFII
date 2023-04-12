#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "kontol";
const char* password = "kontol1234";

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_AP);
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);


  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}
