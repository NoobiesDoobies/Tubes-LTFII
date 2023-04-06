#include <WiFi.h>

// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_AP);
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);


  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
}
