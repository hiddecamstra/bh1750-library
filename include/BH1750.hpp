#include "Arduino.h"
#ifndef BH1750_HPP
#define BH1750_HPP

#include <Wire.h>

class MyLightSensor{
  private:
    int ledPin;
  public:
    MyLightSensor(int ledPin) : ledPin(ledPin) 
    {}
    void begin();
    void blinkLed();
    
};

#endif