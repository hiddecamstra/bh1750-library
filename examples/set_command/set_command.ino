/*
This example shows you that you can send a command. Like POWER_DOWN sets the sensor in sleep mode. Also you will not be able to-
read the most recent value. This is however possible if you send the command POWER_ON. This will get the device out of sleep-
mode. But it will not measure any new values. Yet the most recent measured value is available for reading.

Extend this if you like by setting a mode instead, or after, turning the sensor back on.

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

bool currentlyTurnedOff = false;

void setup() {
    pinMode(ledPin, OUTPUT);
    a.begin();
    Serial.begin(9600);
}

void loop() {
    lux = a.getLux();
    Serial.println(lux);
    if (lux != -1){ // No error code.
        if (lux < ledThreshold)
            digitalWrite(ledPin, HIGH); // Put LED on according to measured value and set threshold.
        else
            digitalWrite(ledPin, LOW);
    }
    else
        digitalWrite(ledPin, LOW); // If error turn LED off.

    delay(5000);
    if (currentlyTurnedOff){
        a.setCommand(POWER_DOWN); // Turn devuce down.
        currentlyTurnedOff = false;
    }
    else{
        a.setCommand(POWER_ON); // Turned back on but mode is not set.
        currentlyTurnedOff = true;
    }
    delay(5000);
}