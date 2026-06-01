#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

int ledPin = 13;
MyLightSensor a(ledPin);

int lightThreshold = 0;

enum State {
    DEFAULT_MENU,
    CHANGE_VALUE
};

State currentState = DEFAULT_MENU;

void showMenu() {
    Serial.println();
    Serial.println("===== MENU =====");
    Serial.println("1: Turn on LED with default values");
    Serial.println("2: Change measuring mode");
    Serial.println("3: Check current sensitivity threshold");
    Serial.println("4: Change sensitivity threshold");
    Serial.print("> ");
}

void ChangeValue(int valueToChangeTo){
  lightThreshold = valueToChangeTo;
  Serial.print("Threshold changed to: ");
  Serial.println(lightThreshold);
  currentState = DEFAULT_MENU;
  showMenu();
}

void setup() {
    a.begin();
    Serial.begin(9600);

    while (!Serial);

    showMenu();
}

void loop() {
    if (!Serial.available())
        return;

    int incomingByte = Serial.parseInt();
    
    switch (currentState) {
        case DEFAULT_MENU:
            switch (incomingByte) {
                case 1:
                    Serial.println("OLAAA");
                    break;
                case 2:
                    Serial.println("DIOS MIO");
                    break;
                case 3:
                    Serial.print("Current light sensitivity threshold: ");
                    Serial.println(lightThreshold);
                    break;
                case 4:
                    currentState = CHANGE_VALUE;
                    Serial.println("Enter new threshold:");
                    return;
                default:
                    Serial.println("That option does not exist.");
                    break;
            }
            showMenu();
            break;
        case CHANGE_VALUE:
            ChangeValue(incomingByte);
            break;
    }
}

#endif