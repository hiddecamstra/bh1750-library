#include "BH1750.hpp"
#include <Wire.h>

void LightSensor::begin(){
    Wire.begin();
    Wire.setClock(400000); // Highspeed I2C (max for bh1750).
    setCommand(POWER_ON); // Turn device on.
    setMode(currentMode); // Enable default set mode.
}

void LightSensor::changeMeasurementTime(){
    switch (currentMode) // Set measurementTime based on mode.
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
    }
}

bool LightSensor::writeToI2C(uint8_t byteToWrite){
    Wire.beginTransmission(currentAddress);
    Wire.write(byteToWrite);
    uint8_t statusOfTransmission = Wire.endTransmission();
    
    if (statusOfTransmission == 0) // Code that Wire.endTransmission(); returns. 0 means no problems.
        return true;
    else
        return false;
}

float LightSensor::readFromI2C(){
    uint8_t highByte = 0;
    uint8_t lowByte = 0;
    uint16_t combined = 0;

    Wire.requestFrom(currentAddress, 2);
    if (Wire.available() == 2){ // Check for if there are any bytes available.
        highByte = Wire.read();
        lowByte = Wire.read();

        combined = highByte;
        combined = combined << 8;
        combined += lowByte;

        return combined;
    }
    else
        return -1;
}

float LightSensor::getLux(){
    if (poweredDown)
        return -1; // Return error code instead of most recent value when turned off.
    
    delay(measurementTime); // Delay depending on mode measurement duration.

    float rawdata = readFromI2C();
    
    if (rawdata != -1) // Only return proper lux if no error code received.
        return rawdata / 1.2;
    else
        return -1;
}

bool LightSensor::setMode(MODES newMode){
    if (!writeToI2C(newMode)) // Return if writing went wrong. Or variables are set incorrectly.
        return false;
    currentMode = newMode;
    changeMeasurementTime(); // Update based on the new mode.
    poweredDown = false; // Reset powered status if mode was set after power down. 
    return true;
}

void LightSensor::setAddress(ADDRESSES newAddress){
    currentAddress = newAddress;
}

bool LightSensor::setCommand(COMMANDS commandToSend){
    if (!writeToI2C(commandToSend)) // Return if writing went wrong. Or variable is set incorrectly.
        return false;
    switch (commandToSend)
    {
    case POWER_DOWN:
        poweredDown = true;
        break;
    case POWER_ON:
        poweredDown = false;
        break;
    default:
        break;
    }
    return true;
}

    