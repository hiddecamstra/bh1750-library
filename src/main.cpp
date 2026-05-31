#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"
//#define CATCH_CONFIG_MAIN
//#include "../test/catch.hpp"

int ledPin = 13;
MyLightSensor a = MyLightSensor(ledPin);


void setup() {
  a.begin();
}

void loop() {
  a.blinkLed();
}