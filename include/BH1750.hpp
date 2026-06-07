#include <Arduino.h>

#ifndef BH1750_HPP
#define BH1750_HPP

enum MODES{
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
    MODES currentMode;
    ADDRESSES currentAddress;
    int measurementTime;
    void changeMeasurementTime();
    bool writeToI2C();
    float readFromI2C();
  public:
    LightSensor() : currentMode(CONTINUOUSLY_H_RESOLUTION_MODE), currentAddress(L), measurementTime(120)
    {}
    void begin();
    float getLux();
    void switchModes(MODES newMode);
    void switchAddress(ADDRESSES newAddress);
};

#endif