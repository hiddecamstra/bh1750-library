/*
In this example we do a serial print of the lux values. And we also use 2 LED that we power on or off based on the lux measured.
The two BH1750 sensor (a & b) are on the same SDA and SCL rows, that are connected to the Arduino. But they are differentiated from-
eachother by setting the address, by putting the ADDR pin of one of the BH1750 sensor to GPIO pin 12. And putting this on HIGH.
The address also changes, and different measurements are collected on the same clock, by 2 different sensors.

Connect LED A to pin 13.
Connect LED B to pin 10.
Connect 1 BH1750 sensor ADDR to pin 12.
Connect both BH1750 SDA & SCL pins to the arduino.
Also connect both sensors to VCC and GND.
*/

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

const int aLedPin = 13;
const int bLedPin = 10;

LightSensor a; // Initiate sensor.
const int aAddressPin = 12; // Set ADDR pin.
LightSensor b; // Initiate sensor.

float aLux = 0;
float bLux = 0;

int aLedThreshold = 50; // Choose a threshold of your liking.
int bLedThreshold = 50;

void ledLogic(float luxToUse, float thresholdToUse, int ledToUse){
    if (luxToUse != -1){ // First check if not an error code received.
        if (luxToUse < thresholdToUse) // Turn LED on and off depending on measured value.
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
    pinMode(aAddressPin, OUTPUT); // Set all pins up for use.

    a.begin();
    b.begin(); // Initialize sensors.

    digitalWrite(aAddressPin, HIGH); // Change one of the sensors address.
    a.setAddress(H); // Same goes for the code.

    Serial.begin(9600);
}

void loop() {
    aLux = a.getLux();
    bLux = b.getLux(); // Get the measurements.

    Serial.print("lux a:");
    Serial.println(aLux);
    Serial.print("lux b:");
    Serial.println(bLux); // Print them out for visual.

    ledLogic(aLux, aLedThreshold, aLedPin);
    ledLogic(bLux, bLedThreshold, bLedPin); // Turn LEDS on and off.
    
    delay(1000);
}