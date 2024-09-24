#include "console.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
static const char* TAG = "console_logging";

// ESP_LOGE - error (lowest)
// ESP_LOGW - warning
// ESP_LOGI - info
// ESP_LOGD - debug
// ESP_LOGV - verbose (highest)
// ESP_EARLY_LOGx - log before log levels are initialized
// esp_log_level_set("*", ESP_LOG_ERROR);        // set all components to ERROR level
// esp_log_level_set("wifi", ESP_LOG_WARN);      // enable WARN logs from WiFi stack
// esp_log_level_set("dhcpc", ESP_LOG_INFO);     // enable INFO logs from DHCP client

// Master logging level is CONFIG_LOG_DEFAULT_LEVEL at start up and = ESP_LOG_INFO
// ESP_LOGI("lib_name", "Message for print");          // prints a INFO message
// esp_log_level_set("lib_name", ESP_LOG_WARN);        // enables WARN logs from lib_name

// esp_log_set_level_master(ESP_LOG_NONE);             // disables all logs globally. esp_log_level_set has no effect at the moment.

// ESP_LOGW("lib_name", "Message for print");          // no print, Master logging level blocks it
// esp_log_level_set("lib_name", ESP_LOG_INFO);        // enable INFO logs from lib_name
// ESP_LOGI("lib_name", "Message for print");          // no print, Master logging level blocks it

// esp_log_set_level_master(ESP_LOG_INFO);             // enables all INFO logs globally.

// ESP_LOGI("lib_name", "Message for print");          // prints a INFO message

int logging(int argc, char **argv)
{
    // Ensure that we have an argument to parse
    if (argc != 2)
    {
        printf("You have to give 'on' or 'off' as a argument (e.g. 'led on')\n");

        // Return EXIT_FAILURE if something did not worked.
        return EXIT_FAILURE;
    }

    // Take the first argument...
    auto arg = String(argv[1]);

    // and use it to decide what to do with the LED
    if (arg == "on")
    {
        digitalWrite(LED, HIGH);
        printf("LED is now on\n");
    }
    else if (arg == "off")
    {
        digitalWrite(LED, LOW);
        printf("LED is now off\n");
    }
    else
    {
        printf("Unknown argument!\n");
        return EXIT_FAILURE;
    }

    // Return EXIT_SUCCESS if everything worked as intended.
    return EXIT_SUCCESS;
}
