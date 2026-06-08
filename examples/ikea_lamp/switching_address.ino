/*
This example show do you can control the address of the sensor. By setting the addres to H (HIGH) the returning lux becomes-
the error code -1. And this code allows the sensor to only work by holding the button. Which sets the ADDR pin to HIGH.
Therefore changing the address to HIGH, and allowing the getLux() function to work, hence it contains the correct address which-
was set in the setup.

Set a LED on pin 13.
Connect the BH1750 sensor to VCC, GND, SCL and SDA.
Connect one side of the button to VCC (POWER) and the oposite side, diagonally set the ADDR pin of the BH1750 sensor + 
a PULL_DOWN resistor of 10kohm to the GROUND.
*/

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

const int ledPin = 13;

LightSensor a;

float lux = 0;
int ledThreshold = 50;

void setup() {
    pinMode(ledPin, OUTPUT);
    a.begin();
    a.setAddress(H);
}

void loop() {
    lux = a.getLux();

    if (lux != -1){
        if (lux < ledThreshold)
            digitalWrite(ledPin, HIGH);
        else
            digitalWrite(ledPin, LOW);
    }
    else
        digitalWrite(ledPin, LOW);
    
    delay(1000);
}