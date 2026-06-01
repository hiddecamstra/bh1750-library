#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

int ledPin = 13;
MyLightSensor a(ledPin);

void setup() {
    a.begin();
}

void loop() {
    a.blinkLed();
}

#endif