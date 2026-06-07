#include "BH1750.hpp"
#include <Wire.h>

void LightSensor::begin(){
    Wire.begin();
    Wire.setClock(4000000);
}

void LightSensor::changeMeasurementTime(){
    switch (currentMessage)
    {
    case CONTINUOUSLY_H_RESOLUTION_MODE:
    case CONTINUOUSLY_H_RESOLUTION_MODE2:
    case ONE_TIME_H_RESOLUTION_MODE:
    case ONE_TIME_H_RESOLUTION_MODE2:
        measurementTime = 120;
        break;
    case CONTINUOUSLY_L_RESOLUTION_MODE:
    case ONE_TIME_L_RESOLUTION_MODE:
        measurementTime = 16;
        break;
    default:
        break;
    }
}

void LightSensor::writeToI2C(){
    Wire.beginTransmission(currentAddress);
    Wire.write(currentMessage);
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
    changeMeasurementTime();
    writeToI2C();
    delay(measurementTime);
    float rawdata = readFromI2C();
    return rawdata / 1.2;
}

void LightSensor::switchMessage(Messages newMessage){
    currentMessage = newMessage;
}

void LightSensor::switchAddress(ADDRESSES newAddress){
    currentAddress = newAddress;
}