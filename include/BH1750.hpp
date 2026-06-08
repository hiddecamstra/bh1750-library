#ifndef BH1750_HPP
#define BH1750_HPP

#include <Arduino.h>

enum COMMANDS{
  POWER_DOWN = 0b00000000,
  POWER_ON = 0b00000001,
  RESET = 0b00000111
};

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
    bool poweredDown;
    void changeMeasurementTime();
    bool writeToI2C(uint8_t byteToWrite);
    float readFromI2C();
  public:
    LightSensor() : currentMode(CONTINUOUSLY_H_RESOLUTION_MODE), currentAddress(L), measurementTime(120), poweredDown(false)
    {}
    void begin();
    float getLux();
    bool setMode(MODES newMode);
    void setAddress(ADDRESSES newAddress);
    bool setCommand(COMMANDS commandToSend);
};

#endif