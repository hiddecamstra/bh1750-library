/** @file
 *  @brief BH1750 library
 *  @details
 *  This is a library made for the functions of a BH1750 light sensor.
 */
#include "Arduino.h"
#ifndef BH1750_HPP
#define BH1750_HPP

#include <Wire.h>

class MyLightSensor{
  /// @brief
  /// default constructor
  /// @details
  /// This constructor does something...
  private:
    int ledPin;
  public:
    MyLightSensor(int ledPin) : ledPin(ledPin) 
    {}
    void begin();
    void blinkLed();
};

#endif