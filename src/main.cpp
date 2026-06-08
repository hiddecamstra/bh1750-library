#ifndef PIO_UNIT_TESTING

#include <Arduino.h>
#include <Wire.h>
#include "BH1750.hpp"

int aLedPin = 13;
int bLedPin = 10;

LightSensor a;
LightSensor b;

int aAddressPin = 12;
int bAddressPin = 11;

int lightThreshold = 50;

float luxA = 0;
float luxB = 0;

int index = 0;
bool stopSensors = false;

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
    Serial.println("3: Start or stop the sensors");
    Serial.println("> ");
}

void ikeaLamp(){
    luxA = a.getLux();
    luxB = b.getLux();

    //Serial.print("Lux a: ");
   // Serial.println(luxA);

    //Serial.print("Lux b: ");
    //Serial.println(luxB);

    if (luxA != -1){// If received not an error code.
        if (luxA < lightThreshold) // Turn on LED if measured lux is lower than threshold.
            digitalWrite(aLedPin, HIGH);
        else
            digitalWrite(aLedPin, LOW);
    } 

    if (luxB != -1){
        if (luxB < lightThreshold)
            digitalWrite(bLedPin, HIGH);
        else
            digitalWrite(bLedPin, LOW);
    }
}

void exampleForSendingCommands(){
    index++;

    if (index >= 5){
        a.setCommand(POWER_DOWN);
        Serial.println("Little break!");
    }
    else{
        ikeaLamp();
    }
    if(index >= 10){
        a.setCommand(POWER_ON);
        //a.switchModes(ONE_TIME_H_RESOLUTION_MODE);
        a.setMode(CONTINUOUSLY_L_RESOLUTION_MODE);
        index = 0;
        Serial.println("We roll again! ");
    }
}

void setup() {
    Serial.begin(9600);

    while (!Serial);

    a.begin();
    b.begin();

    pinMode(aAddressPin, OUTPUT);
    digitalWrite(aAddressPin, HIGH);
    a.setAddress(H);
    a.setMode(CONTINUOUSLY_L_RESOLUTION_MODE);

    pinMode(aLedPin, OUTPUT);

    showMenu();
}

void loop() {
    if (stopSensors) // Only run when sensors enabled in menu.
        exampleForSendingCommands();
    
    delay(1000);


    if (!Serial.available()) // If Serial doesn't work try again.
        return;

    int userInput = Serial.parseInt(); // Get input, only in ints.
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
                    return; // Return instead of break, so it doens't run through rest of code, and it flows into new state.
                case 3:
                    if (stopSensors)
                        stopSensors = false;
                    else
                        stopSensors = true;
                    break;
                default:
                    Serial.println("That option does not exist.");
                    break;
            }
            showMenu();
            break;
        case CHANGE_THRESHOLD:
            lightThreshold = userInput; // Change threshold to the newly put in input.
            currentState = DEFAULT_MENU; // Go back to normal menu.
            showMenu();
            break;
    }
}

#endif