#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

int ledPin = 13;
LightSensor a;
int addressPin = 12;

int lightThreshold = 0;
float lux = 0;

enum State {
    DEFAULT_MENU,
    CHANGE_THRESHOLD
};

State currentState = DEFAULT_MENU;

void showMenu() {
    Serial.println();
    Serial.println("===== MENU =====");
    Serial.println("1: Check current sensitivity threshold");
    Serial.println("2: Change sensitivity threshold");
    Serial.println("> ");
}

void ikeaLamp(){
    lux = a.getLux();
    Serial.println(lux);
    
    if (lux < lightThreshold && lux > 0)
    {
        digitalWrite(ledPin, HIGH);
    }
    else{
        digitalWrite(ledPin, LOW);
    }
}

void setup() {
    Serial.begin(9600);

    while (!Serial);

    a.begin();
    a.switchModes(CONTINUOUSLY_L_RESOLUTION_MODE);
    
    pinMode(addressPin, OUTPUT);
    digitalWrite(addressPin, HIGH);
    a.switchAddress(H);

    pinMode(ledPin, OUTPUT);

    showMenu();
}

void loop() {
    ikeaLamp();
    delay(1000);

    if (!Serial.available())
        return;

    int userInput = Serial.parseInt();
    switch (currentState) {
        case DEFAULT_MENU:
            switch (userInput) {
                case 1:
                    Serial.print("Current light sensitivity threshold: ");
                    Serial.println(lightThreshold);
                    break;
                case 2:
                    currentState = CHANGE_THRESHOLD;
                    Serial.println("Enter new threshold:");
                    return;
                    break;
                default:
                    Serial.println("That option does not exist.");
                    break;
            }
            showMenu();
            break;
        case CHANGE_THRESHOLD:
            lightThreshold = userInput;
            currentState = DEFAULT_MENU;
            showMenu();
            break;
    }
}

#endif