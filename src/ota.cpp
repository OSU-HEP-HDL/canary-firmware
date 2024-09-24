#include "constants.h"
#include "ota.h"

static const char *TAG = "OTA";

void basic_ota()
{
    ArduinoOTA.onStart([]()
                       {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    ESP_LOGI(TAG, "Start updating " + type); });
    ESP_LOGI(TAG, "Message for print");

    ArduinoOTA.onEnd([]()
                     { ESP_LOGI(TAG, "\nEnd"); });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                          { ESP_LOGI(TAG, "Progress: %u%%\r", (progress / (total / 100))); });

    ArduinoOTA.onError([](ota_error_t error)
                       {
    ESP_LOGE(TAG, "Error[%u]: ", error);
 
    switch (error) {

    case (OTA_AUTH_ERROR):
      ESP_LOGE(TAG, "Auth Failed");
     case (OTA_BEGIN_ERROR):
      ESP_LOGE(TAG, "Begin Failed");
     case (OTA_CONNECT_ERROR) :
      ESP_LOGE(TAG, "Connect Failed");
     case (OTA_RECEIVE_ERROR) :
      ESP_LOGE(TAG, "Receive Failed");
     case (OTA_END_ERROR) :
      ESP_LOGE(TAG, "End Failed");
     default: {
      ESP_LOGE(TAG, "Unknown Error");
    }
    } });

    ArduinoOTA.begin();
    // Serial.println("Ready");
    // Serial.print("IP address: ");
    // Serial.println(WiFi.localIP());
    // Serial.print("Hostname: ");
    // Serial.println(ArduinoOTA.getHostname());
}
