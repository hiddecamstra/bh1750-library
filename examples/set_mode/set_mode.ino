/*
In this example is shown how to set a mode. YOu can set for example the mode ONE_TIME_H_RESOLUTION_MODE.
What this does is that it makes one measurement, and immediatly goes into POWER_DOWN. Which is essentially a kind off sleep state.
This obviously saves power.
Turn it back on by sending a new mode.

Connect a led to pin 13.
Connect the BH1750 sensor to VCC, GND, SCL & SDA. Leave the ADDR pin floating or put on GND.
*/

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

const int ledPin = 13;

LightSensor a; // Initiate sensor.

float lux = 0;

int ledThreshold = 50; // Set prefered threshold.

void setup() {
    pinMode(ledPin, OUTPUT);
    a.begin();
}

void loop() {
    delay(5000);
    a.setMode(ONE_TIME_H_RESOLUTION_MODE); // Set your desired mode.
    lux = a.getLux();
    if (lux != -1){ // No error code.
        if (lux < ledThreshold)
            digitalWrite(ledPin, HIGH); // Put LED on according to measured value and set threshold.
        else
            digitalWrite(ledPin, LOW);
    }
    else
        digitalWrite(ledPin, LOW); // If error turn LED off.
}