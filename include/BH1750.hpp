#include <Arduino.h>

#ifndef BH1750_HPP
#define BH1750_HPP

enum Modes{
  //POWER_DOWN = 0b00000000,
  //POWER_ON = 0b00000001,
  //RESET = 0b00000111,
  CONTINUOUSLY_H_RESOLUTION_MODE = 0b00010000,
  CONTINUOUSLY_H_RESOLUTION_MODE2 = 0b00010001,
  CONTINUOUSLY_L_RESOLUTION_MODE = 0b00010011,
  ONE_TIME_H_RESOLUTION_MODE = 0b00100000,
  ONE_TIME_H_RESOLUTION_MODE2 = 0b00100001,
  ONE_TIME_L_RESOLUTION_MODE = 0b00100011
};

class LightSensor{
  private:
    uint8_t slaveAddress = 0b0100011;
    Modes currentMode;
    void writeToI2C(uint8_t opecode);
    uint16_t readFromI2C();
  public:
    LightSensor() : currentMode(CONTINUOUSLY_H_RESOLUTION_MODE)
    {}
    void begin();
    float getLux();
    void switchMode(Modes newMode);
};

#endif