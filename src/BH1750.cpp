//#include <BH1750.hpp>
#include "BH1750.hpp"
//#include <BH1750.hpp>

void MyLightSensor::begin(){
    pinMode(ledPin, OUTPUT);
}

void MyLightSensor::blinkLed(){
    digitalWrite(ledPin, HIGH);
    delay(250);
    digitalWrite(ledPin, LOW);
    delay(250);
}