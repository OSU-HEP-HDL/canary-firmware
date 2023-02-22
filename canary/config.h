/*
 * Edit this file to configure any option.
 * Do not edit sleepMeasurePostRepeat.ino or other files.
 * To enable/disable a sensor uncomment/comment its definition.
 * To set a parameter uncomment its definition and provide its value.
 */

//******************************************
#ifndef CONFIG_H
#define CONFIG_H

#include <Preferences.h>
Preferences preferences;
// setup
// #define CAFFEINE true     // do not go to sleep; use if not battery operated
bool CAFFEINE;
int SLEEPTIME;       // sleep interval [s]
int INTEGRATIONTIME; // measurements integration time interval [s]
bool PRINTSERIAL;    // print measurements to serial output
bool POST;           // connect and post measurements to MQTT server
bool VERBOSE;        // print connection status and posting details
bool TLS;            // use TLS encryption; does not work with ESP8266
// #define ESP8266 //use an ESP8266 microcontroller instead of an ESP32 (default)

//******************************************
// wifi
String WIFISSID;     // wifi SSID
String WIFIPASSWORD; // wifi password

//******************************************
// MQTT
byte MQTTMESSAGESIZE; // maximum message length [byte]
String MQTTSERVER;    // MQTT server address
int MQTTPORT;         // MQTT server port
int MQTTTLSPORT;      // MQTT with TLS server port
String MQTTUSERNAME;  // MQTT username
String MQTTPASSWORD;  // MQTT password
String MQTTTOPIC;     // MQTT topic
// #define INSTITUTE "institute" //institute of the measuring device (optional)
// #define ROOM "room" //room of the measuring device (optional)
// #define LOCATION "location" //location of the measuring device (optional)
// #define NAME "name" //name of the measuring device (optional)
bool MACASNAME; // use the MAC address as device name (optional)
int MQTTTIME;   // MQTT broker check-in time interval [s]

//******************************************
// SHT temperature and humidity sensors
// #define SHT35A //enable SHT35 A (0x44 address)
bool SHT35B; // enable SHT35 B (0x45 address)
// Double check with Steven if bool ZA
//  #define SHT85 //enable SHT85 (0x44 address)

//******************************************
// MAX31865 RTD sensor
// #define MAX31865 //enable MAX31865
int MAX31865RNOM; // sensor nominal resistance at 0 C (100 Ohm or 1000 Ohm) [Ohm]
int MAX31865RREF; // reference resistor [Ohm]
bool ESP8266 = false;
// #ifdef ESP8266            // ESP8266
// #define MAX31865CS 15     // CS pin for ESP8266
// #else                     // ESP32
// #define MAX31865CS 33     // CS pin for ESP32
// #endif
int MAX31865CS;
String MAX31865RHSOURCE; // RH measurement source for dew point calculation; use instance name from sleepMeasurePostRepeat.ino

//******************************************
// SPS30 dust particle counter
bool SPS30;        // enable SPS30
bool SPS30AVERAGE; // average over multiple SPS30 measurements (one per second)
bool SPS30VERBOSE; // print SPS30 information

//******************************************
// ADS1x15 ADCs and NTCs (4 channels)
// #define ADS1015 //enable ADS1015 (12 bit)
// #define ADS1115 //enable ADS1115 (16 bit)
float ADS1x15VDD;   // VDD [V]
float ADS1x15VREF;  // ADC reference voltage [V] //NOTE valid for ADC gain set to 1, see ADS1x15GAIN
String ADS1x15GAIN; // ADC gain: 1x gain  +/- 4.096V  1 bit = 2mV (ADS1015) or 0.125mV (ADS1115), see ADS1x15VREF

// ADC0/NTC0 (channel 0)
// #define ADS1x150ADC //NOTE set also the voltage divider resistor value
// #define ADS1x150NTC //NOTE set also the voltage divider resistor value and NTC R0, T0 and B values
float ADS1x150RDIV; // ADC voltage divider resistor value [Ohm] //49.9e3
float ADS1x150R0;   // NTC R0 [Ohm] //1e4
float ADS1x150T0;   // NTC T0 [K] //298.15
int ADS1x150B;      // NTC B //3435

// ADC1/NTC1 (channel 1)
// #define ADS1x151ADC //NOTE set also the voltage divider resistor value
// #define ADS1x151NTC //NOTE set also the voltage divider resistor value and NTC R0, T0 and B values
float ADS1x151RDIV; // ADC voltage divider resistor value [Ohm] //49.9e3
float ADS1x151R0;   // NTC R0 [Ohm] //1e4
float ADS1x151T0;   // NTC T0 [K] //298.15
int ADS1x151B;      // NTC B //3435

// ADC2/NTC2 (channel 2)
// #define ADS1x152ADC //NOTE set also the voltage divider resistor value
// #define ADS1x152NTC //NOTE set also the voltage divider resistor value and NTC R0, T0 and B values
float ADS1x152RDIV; // ADC voltage divider resistor value [Ohm] //49.9e3
float ADS1x152R0;   // NTC R0 [Ohm] //1e4
float ADS1x152T0;   // NTC T0 [K] //298.15
int ADS1x152B;      // NTC B //3435

// ADC3/NTC3 (channel 3)
// #define ADS1x153ADC //NOTE set also the voltage divider resistor value
// #define ADS1x153NTC //NOTE set also the voltage divider resistor value and NTC R0, T0 and B values
float ADS1x153RDIV; // ADC voltage divider resistor value [Ohm] //49.9e3
float ADS1x153R0;   // NTC R0 [Ohm] //1e4
float ADS1x153T0;   // NTC T0 [K] //298.15
int ADS1x153B;      // NTC B //3435

// certification authority's ROOT certificate
// TrustID X3 Root
#define CACERT                                                         \
  "-----BEGIN CERTIFICATE-----\n"                                      \
  "MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\n" \
  "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
  "DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\n" \
  "PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\n" \
  "Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n" \
  "AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\n" \
  "rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\n" \
  "OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\n" \
  "xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\n" \
  "7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\n" \
  "aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\n" \
  "HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\n" \
  "SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\n" \
  "ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\n" \
  "AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\n" \
  "R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\n" \
  "JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\n" \
  "Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\n"                         \
  "-----END CERTIFICATE-----\n"

#endif
