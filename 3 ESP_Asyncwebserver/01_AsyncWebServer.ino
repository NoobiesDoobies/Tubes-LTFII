#include <ESPAsyncWebServer.h>
// Replace with your network credentials
const char* ssid = "kontol";
const char* password = "kontol1234";


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


// Create an Event Source on /events
AsyncEventSource events("/events");
