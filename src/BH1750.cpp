#include "BH1750.hpp"
#include <Wire.h>

void LightSensor::begin(){
    Wire.begin();
    Wire.setClock(4000000);
}

void LightSensor::writeToI2C(){
    Wire.beginTransmission(currentAddress);
    Wire.write(currentMode);
    Wire.endTransmission();
}

uint16_t LightSensor::readFromI2C(){
    uint8_t highByte = 0;
    uint8_t lowByte = 0;
    uint16_t combined = 0;

    Wire.requestFrom(currentAddress, 2);
    highByte = Wire.read();
    lowByte = Wire.read();

    combined = highByte;
    combined = combined << 8;
    combined += lowByte;

    return combined;
}

float LightSensor::getLux(){
    writeToI2C();
    float rawdata = readFromI2C();
    return rawdata / 1.2;
}

void LightSensor::switchMode(Modes newMode){
    currentMode = newMode;
}

void LightSensor::switchAddress(ADDRESSES newAddress){
    currentAddress = newAddress;
}