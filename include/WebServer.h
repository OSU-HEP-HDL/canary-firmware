#ifndef webserver_h
#define webserver_h

    #include "constants.h"

    #if defined(ESP8266)
        #include <ESP8266WiFi.h>
        #include <ESPAsyncTCP.h>
    #elif defined(ESP32)
        #include <WiFi.h>
        #include <AsyncTCP.h>
    #endif

    #include <ESPAsyncWebServer.h>
    static const char* WEB = "WebServer";
    void initWebServer(int port);

#endif

