#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"
#include "constants.h"
#include "console.h"
#include "provisioning.h"
#include "WebServer.h"
#include "myPreferences.h"
#include "ota.h"


// There are the following verbosity levels for logging:

// Error (lowest)
// Warning
// Info
// Debug
// Verbose (highest)

void setup()
{
    esp_log_level_set("*",ESP_LOG_VERBOSE);
    Serial.begin(115200);
    setupPreferences();
    setupConsole();
    
    pinMode(LED, OUTPUT);

    
    
    
    Provision();
    basic_ota(); // setup OTA on port 3232
    // initWebServer(80);

}

void loop()
{
    ArduinoOTA.handle();
    // esp_wifi_get_config();
    // Serial.print(btStarted());
}