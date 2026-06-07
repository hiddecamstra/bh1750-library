#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

int ledPin = 13;
LightSensor a;
int addressPin = 12;

int lightThreshold = 0;
float lux = 0;

int index = 0;

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

void exampleForSendingCommands(){
    index++;

    if (index >= 5){
        a.sendCommand(POWER_DOWN);
        Serial.println("Little break!");
    }
    else{
        ikeaLamp();
    }
    if(index >= 10){
        a.sendCommand(POWER_ON);
        //a.switchModes(ONE_TIME_H_RESOLUTION_MODE);
        a.switchModes(CONTINUOUSLY_L_RESOLUTION_MODE);
        index = 0;
        Serial.println("We roll again! ");
    }
}

void setup() {
    Serial.begin(9600);

    while (!Serial);

    a.begin();

    pinMode(addressPin, OUTPUT);
    digitalWrite(addressPin, HIGH);
    a.switchAddress(H);
    a.switchModes(CONTINUOUSLY_L_RESOLUTION_MODE);

    pinMode(ledPin, OUTPUT);

    showMenu();
}

void loop() {
    //ikeaLamp();
    exampleForSendingCommands();
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