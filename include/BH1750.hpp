#include <Arduino.h>

#ifndef BH1750_HPP
#define BH1750_HPP

enum Modes{
  CONTINUOUSLY_H_RESOLUTION_MODE = 0b00010000,
  CONTINUOUSLY_H_RESOLUTION_MODE2 = 0b00010001,
  CONTINUOUSLY_L_RESOLUTION_MODE = 0b00010011,
  ONE_TIME_H_RESOLUTION_MODE = 0b00100000,
  ONE_TIME_H_RESOLUTION_MODE2 = 0b00100001,
  ONE_TIME_L_RESOLUTION_MODE = 0b00100011
};

enum ADDRESSES{
  H = 0b1011100,
  L = 0b0100011
};

class LightSensor{
  private:
    Modes currentMode;
    ADDRESSES currentAddress;
    void writeToI2C();
    uint16_t readFromI2C();
  public:
    LightSensor() : currentMode(CONTINUOUSLY_H_RESOLUTION_MODE), currentAddress(L)
    {}
    void begin();
    float getLux();
    void switchMode(Modes newMode);
    void switchAddress(ADDRESSES newAddress);
};

#endif