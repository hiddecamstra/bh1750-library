#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include "BH1750.hpp"

LightSensor a;
float lux = 0;

const int ledPin = 13;
int lightThreshold = 30;

void setup() {
    Serial.begin(9600);
    a.begin(); // Initiate light sensor.
    pinMode(ledPin, OUTPUT);
}

void loop() {
    lux = a.getLux(); // Measure lux with default values.
    Serial.println(lux); // Print for debug.
    
    if (lux != -1){ // No error.
        if (lux < lightThreshold){ // Activate when measured result is below threshold. Else turn off.
            digitalWrite(ledPin, HIGH);
        }
        else
            digitalWrite(ledPin, LOW);
    } 

    delay(1000);
}

#endif