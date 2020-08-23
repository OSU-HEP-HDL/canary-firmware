#ifndef MAX31865SENSOR
#define MAX31865SENSOR

#include "TRHSensor.h"
#include "Adafruit_MAX31865.h"

class MAX31865Sensor: public virtual TRHSensor {
  
  public:
    MAX31865Sensor(float rnom, float rref, uint8_t cs);
    int init(void) override;
    void readData() override;
    String getSensorString(void) override {return "t[C]   ";}
    String getMeasurementsString(void) override;
    void getJSONDoc(JsonDocument &doc) override;
    //void setRHSource(TRHSensor* rhsource);
  
  private:
    Adafruit_MAX31865 _max31865;
    float _rnom;
    float _rref;
    uint8_t _cs;
    //TRHSensor* _rhsource = NULL;
};
#endif //MAX31865SENSOR
