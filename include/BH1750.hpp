/**
 * @file BH1750.hpp
 * @brief BH1750 ambient light sensor library.
 *
 * C++ library for the BH1750 light sensor.
 * Provides functionality to configure commands, measurement modes,
 * switching I2C addresses, and to retrieve measured lux.
 *
 * Uses the Arduino Wire library for I2C communication.
 *
 * @author Hidde Camstra
 */

#ifndef BH1750_HPP
#define BH1750_HPP

#include <Arduino.h>

/**
 * @brief Available commands.
*/
enum COMMANDS{
  POWER_DOWN = 0b00000000,
  POWER_ON = 0b00000001,
  RESET = 0b00000111
};
/**
 * @brief Available modes.
*/
enum MODES{
  CONTINUOUSLY_H_RESOLUTION_MODE = 0b00010000,
  CONTINUOUSLY_H_RESOLUTION_MODE2 = 0b00010001,
  CONTINUOUSLY_L_RESOLUTION_MODE = 0b00010011,
  ONE_TIME_H_RESOLUTION_MODE = 0b00100000,
  ONE_TIME_H_RESOLUTION_MODE2 = 0b00100001,
  ONE_TIME_L_RESOLUTION_MODE = 0b00100011
};
/**
 * @brief Available addresses.
*/
enum ADDRESSES{
  H = 0b1011100,
  L = 0b0100011
};

/**
 * @brief Sensor specific settings and values.
*/
class LightSensor{
  private:
    MODES currentMode;
    ADDRESSES currentAddress;
    int measurementTime; // Changes depending on mode.
    bool poweredDown; // To not send back most recent measured value but errorcode instead.
    /**
     * @brief Changes measurement duration based on selected mode.
    */
    void changeMeasurementTime();
    /**
     * @brief Method to send a byte using Wire.h to the BH1750 sensor.
    */
    bool writeToI2C(uint8_t byteToWrite);
    /**
     * @brief Method to read 2 bytes using Wire.h from the BH1750 sensor.
    */
    float readFromI2C();
  public:
    /**
     * @brief Constructor initiates sensor.
    */
    LightSensor() : currentMode(CONTINUOUSLY_H_RESOLUTION_MODE), currentAddress(L), measurementTime(120), poweredDown(false)
    {} // Set default values that can be used by simply initation.
    /**
     * @brief Method to begin the proces. Begin the Wire.h library, sets the clockspeed to 400000 (Highspeed I2C). Turns the sensor on and sets the initial mode.
    */
    void begin(); // *
    /**
     * @brief Method to get the measured lux value.
    */
    float getLux(); // *
    /**
     * @brief Method to set a different mode.
    */
    bool setMode(MODES newMode);
    /**
     * @brief Method to set a different address.
    */
    void setAddress(ADDRESSES newAddress);
    /**
     * @brief Method to set a command.
    */
    bool setCommand(COMMANDS commandToSend);
};

#endif