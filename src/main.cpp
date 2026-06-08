#ifndef PIO_UNIT_TESTING

/*

*/

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

const int aLedPin = 13;
const int bLedPin = 10;

LightSensor a;
LightSensor b;

float aLux = 0;
float bLux = 0;

int aLedThreshold = 50;
int bLedThreshold = 50;

void ledLogic(float luxToUse, float thresholdToUse, int ledToUse){
    if (luxToUse != -1){
        if (luxToUse < thresholdToUse)
            digitalWrite(ledToUse, HIGH);
        else
            digitalWrite(ledToUse, LOW);
    }
    else
        digitalWrite(ledToUse, LOW);
}

void setup() {
    pinMode(aLedPin, OUTPUT);
    pinMode(bLedPin, OUTPUT);
    a.begin();
    b.begin();
}

void loop() {
    aLux = a.getLux();
    bLux = b.getLux();

    ledLogic(aLux, aLedThreshold, aLedPin);
    ledLogic(bLux, bLedThreshold, bLedPin);
    
    delay(1000);
}

#endif