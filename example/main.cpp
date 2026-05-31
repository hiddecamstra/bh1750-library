#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

int ledPin = 13;
MyLightSensor a = MyLightSensor(ledPin);


void setup() {
  //pinMode(ledPin, OUTPUT);
  a.begin();
}

void loop() {
  //digitalWrite(ledPin, HIGH);
  //delay(250);
  //digitalWrite(ledPin, LOW);
  //delay(250);
  a.blinkLed();
}