/*
 * This sketch measures values from the connected sensors, prints them to serial output and sends them to a server.
 * Both ESP8266 and ESP32 microcontrollers are supported. Other microcontrollers may be compatible too.
 * Printing and posting can be enabled/disabled by uncommenting/commenting the relative options in config.h.
 * To enable/disable a sensor, uncomment/comment its name in config.h.
 * All the available options can be set in config.h.
 * Do not edit this file. Edit config.h instead.
 * Repository: https://gitlab.cern.ch/guescini/canary-software
 * Wiki: https://gitlab.cern.ch/guescini/canary/wikis/home
 * Author: Francesco Guescini.
*/

//******************************************
//definitions
#define VERSION "v. 1.0.0"

//******************************************
//libraries
#include "config.h"
#include "sensor.h"
#include "vector"
#include "memory"
#include "AsyncDelay.h"
#include "ArduinoJson.h"

//wifi and MQTT
#if POST or VERBOSE
#include "WiFiHandler.h"
#include "MQTTHandler.h"
#endif //POST or VERBOSE

//SHTxx
#if defined(SHT35A) or defined(SHT35B) or defined(SHT85)
#include "SHTxxSensor.h"
#endif //SHTxx

//MAX31865
#ifdef MAX31865
#include "MAX31865Sensor.h"
#endif //MAX31865

//SPS30
#ifdef SPS30
#include "SPS30Sensor.h"
#endif //SPS30

//ADS1x15
#if defined(ADS1115) or defined(ADS1015)
#include "ADS1x15Sensor.h"
#endif //ADS1015 or ADS1115

//******************************************
//wifi and MQTT setup
#if POST or VERBOSE
WiFiHandler wifihandler(WIFISSID,
			WIFIPASSWORD);
PubSubClient mqttclient;
MQTTHandler mqtthandler(&mqttclient,
			MQTTSERVER,
			TLS? MQTTTLSPORT:MQTTPORT,
			TLS,
			MQTTUSERNAME,
			MQTTPASSWORD,
			MQTTTOPIC,
			MQTTMESSAGESIZE,
			TLS? CACERT:"");
#endif //POST or VERBOSE

//******************************************
//vector of sensors
std::vector<std::unique_ptr<Sensor>> sensors;

//******************************************
//JSON documents
StaticJsonDocument<MQTTMESSAGESIZE> masterdoc;
StaticJsonDocument<160> sensordoc;

//******************************************
//loop time intervals
AsyncDelay sleepTime; //data measurement and posting
AsyncDelay integrationTime; //measurement average
AsyncDelay MQTTTime; //MQTT broker check-in

//******************************************
//setup
void setup() {

  //------------------------------------------
  //serial begin
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("\nsleep, measure, post, repeat");
  Serial.println(VERSION);
  Serial.println();

  //------------------------------------------
  //wifi connection
#if POST
  wifihandler.connect(VERBOSE);
#endif //POST

  //------------------------------------------
  //add sensors to the vector

  //SHT35A
#ifdef SHT35A
  SHTxxSensor* sht35a = new SHTxxSensor(SHTxxSensor::sht35a);
  sensors.emplace_back(sht35a);
#endif //SHT35A

  //SHT35B
#ifdef SHT35B
  SHTxxSensor* sht35b = new SHTxxSensor(SHTxxSensor::sht35b);
  sensors.emplace_back(sht35b);
#endif //SHT35B

  //SHT85
#ifdef SHT85
  SHTxxSensor* sht85 = new SHTxxSensor(SHTxxSensor::sht85);
  sensors.emplace_back(sht85);
#endif //SHT85

  //MAX31865
#ifdef MAX31865
#ifdef MAX31865RHSOURCE
  MAX31865Sensor* max31865 = new MAX31865Sensor(MAX31865RNOM, MAX31865RREF, MAX31865CS, MAX31865RHSOURCE);
#else
  MAX31865Sensor* max31865 = new MAX31865Sensor(MAX31865RNOM, MAX31865RREF, MAX31865CS);
#endif //MAX31865RHSOURCE
  sensors.emplace_back(max31865);
#endif //MAX31865

  //SPS30
#ifdef SPS30
  SPS30Sensor* sps30 = new SPS30Sensor(SPS30AVERAGE);
  sensors.emplace_back(sps30);
#endif //SPS30

  //ADS1015 or ADS1115
#if defined(ADS1115) or defined(ADS1015)
  ADS1x15Sensor* ads1x15 = new ADS1x15Sensor(ADS1x15VDD, ADS1x15VREF);
  sensors.emplace_back(ads1x15);
#endif //ADS1015 or ADS1115
    
  //------------------------------------------
  //initialize sensors
  for (auto&& sensor : sensors) {
      sensor->init();
  }

  //------------------------------------------
  //print list of sensors
#if PRINTSERIAL or VERBOSE
  Serial.println("available sensors:");
  for (auto&& sensor : sensors) {
      Serial.print("\t");
      Serial.println(sensor->getName());
  }
  Serial.println();
#endif //PRINTSERIAL or VERBOSE

  //------------------------------------------
  //print measurement names and units
#if PRINTSERIAL
  for (auto&& sensor : sensors) {
      Serial.print(sensor->getSensorString());
  }
  Serial.println();
#endif //PRINTSERIAL

  //------------------------------------------
  //read, print and post values before going to sleep
  //NOTE this is meant for battery operation (no caffeine)
#if not CAFFEINE
  for (auto&& sensor : sensors) {
    sensor->integrate();
  }
  readPrintPost();
  Serial.println("now going to sleep zzz...");
  ESP.deepSleep(SLEEPTIME * 1e6); //µs
#endif //not CAFFEINE
  
  //------------------------------------------
  //start asynchronous timing
#if CAFFEINE
  MQTTTime.start(MQTTTIME*1e3, AsyncDelay::MILLIS);
  integrationTime.start(INTEGRATIONTIME*1e3, AsyncDelay::MILLIS);
  sleepTime.start(SLEEPTIME*1e3, AsyncDelay::MILLIS);
#endif //CAFFEINE
  
} //setup()

//******************************************
//loop
void loop() {

  //------------------------------------------
  //integrate sensor measurements (if averaging is enabled)
  if (integrationTime.isExpired()) {
    for (auto&& sensor : sensors) {
      sensor->integrate();
    }
    integrationTime.repeat();
  }

  //------------------------------------------
  //read, print and post measurements
  if (sleepTime.isExpired()) {
    readPrintPost();
    sleepTime.repeat();
  }

  //------------------------------------------
  //MQTT check-in loop
#if POST
  if (MQTTTime.isExpired()) {
    mqtthandler.loop();
    MQTTTime.repeat();
  }
#endif //POST

} //loop()

//******************************************
//read, print and post measurements
//NOTE integration and averaging is done separately
void readPrintPost() {

    //------------------------------------------
    //read measurements
    for (auto&& sensor : sensors) {
      sensor->readData();
    }
    
    //------------------------------------------
    //print measurements
#if PRINTSERIAL
    for (auto&& sensor : sensors) {
      Serial.print(sensor->getMeasurementsString());
    }
    Serial.println();
#endif //PRINTSERIAL

#if POST or VERBOSE
    //------------------------------------------
    //post measurements
    masterdoc.clear();
    for (auto&& sensor : sensors) {
      sensordoc.clear();
      sensor->getJSONDoc(sensordoc);
      addMetaData(sensordoc);
      masterdoc.add(sensordoc);
    }
#if POST
    wifihandler.connect(VERBOSE);
#endif //POST
    mqtthandler.post(masterdoc, POST, VERBOSE);

    //------------------------------------------
    //disconnect before leaving
#if not CAFFEINE
    wifihandler.disconnect();
#endif //not CAFFEINE
#endif //POST or VERBOSE


} //readPrintPost()

//******************************************
//add metadata to JSON document
void addMetaData(JsonDocument &doc) {
#ifdef INSTITUTE
  doc["institute"] = INSTITUTE;
#endif //INSTITUTE
#ifdef ROOM
  doc["room"] = ROOM;
#endif //ROOM
#ifdef LOCATION
  doc["location"] = LOCATION;
#endif //LOCATION
#ifdef NAME
  doc["name"] = NAME;
#elif defined(MACASNAME)
  doc["name"] = wifihandler.getMACAddress();
#endif //NAME or MACASNAME
  return;
}
