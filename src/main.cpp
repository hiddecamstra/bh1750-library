#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

int ledPin = 13;
LightSensor a;

int lightThreshold = 0;
float lux = 0;

int i = 0;

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
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);

    while (!Serial);

    showMenu();
}

void loop() {
    lux = a.getLux();
    Serial.println(lux);
    if (i == 6){
        i = 0;
    }
    switch (i)
    {
    case 0:
        a.switchMode(CONTINUOUSLY_L_RESOLUTION_MODE);
        break;
    case 1:
        a.switchMode(CONTINUOUSLY_H_RESOLUTION_MODE);
        break;
    case 2:
        a.switchMode(CONTINUOUSLY_H_RESOLUTION_MODE2);
        break;
    case 3:
        a.switchMode(ONE_TIME_L_RESOLUTION_MODE);
        break;
    case 4:
        a.switchMode(ONE_TIME_H_RESOLUTION_MODE);
        break;
    case 5:
        a.switchMode(ONE_TIME_H_RESOLUTION_MODE2);
        break;
    default:
        break;
    }
    i++; 
    if (lux < lightThreshold)
    {
        digitalWrite(ledPin, HIGH);
    }
    else{
        digitalWrite(ledPin, LOW);
    }

    delay(1000);

    if (!Serial.available())
        return;

    int userInput = Serial.parseInt();
    
    switch (currentState) {
        case DEFAULT_MENU:
            switch (userInput) {
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
            ChangeValue(userInput);
            break;
    }
}

#endif