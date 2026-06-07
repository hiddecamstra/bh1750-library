#include "BH1750.hpp"
#include <Wire.h>

void LightSensor::begin(){
    Wire.begin();
    Wire.setClock(400000);
}

void LightSensor::changeMeasurementTime(){
    switch (currentMode)
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

bool LightSensor::writeToI2C(){
    Wire.beginTransmission(currentAddress);
    Wire.write(currentMode);
    uint8_t statusOfTransmission = Wire.endTransmission();
    
    if (statusOfTransmission == 0){
        return true;
    }
    else{
        return false;
    }
}

float LightSensor::readFromI2C(){
    uint8_t highByte = 0;
    uint8_t lowByte = 0;
    uint16_t combined = 0;

    Wire.requestFrom(currentAddress, 2);
    if (Wire.available() == 2){
        highByte = Wire.read();
        lowByte = Wire.read();

        combined = highByte;
        combined = combined << 8;
        combined += lowByte;

        return combined;
    }
    else{
        return -1;
    }
}

float LightSensor::getLux(){
    if (!writeToI2C()){
        return -1;
    }
    
    delay(measurementTime);

    float rawdata = readFromI2C();
    
    if (rawdata != -1){
        return rawdata / 1.2;
    }
    else{
        return -1;
    }
}

void LightSensor::switchModes(MODES newMode){
    currentMode = newMode;
    changeMeasurementTime();
}

void LightSensor::switchAddress(ADDRESSES newAddress){
    currentAddress = newAddress;
}