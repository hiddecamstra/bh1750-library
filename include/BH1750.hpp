#include "Arduino.h"
#ifndef BH1750_HPP
#define BH1750_HPP

#include <Wire.h>

class LightSensor{
  private:
    uint8_t slaveAddress = 0b0100011;
    void writeToI2C(uint8_t opecode);
    uint16_t readFromI2C();
  public:
    LightSensor()
    {}
    void begin();
    float getLux();
};

#endif