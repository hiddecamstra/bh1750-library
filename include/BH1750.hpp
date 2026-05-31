/** @file
 *  @brief BH1750 library
 *  @details
 *  This is a library made for the functions of a BH1750 light sensor.
 */
#include "Arduino.h"
#ifndef HIDDEBH1750_H
#define HIDDEBH1750_H

#include <Wire.h>

class MyLightSensor{
  /// @brief
  /// default constructor
  /// @details
  /// This constructor does something...
  private:
    int ledPin;
  public:
    MyLightSensor(int ledPin) : ledPin(ledPin) 
    {}
    void begin();
    void blinkLed();
};


#endif

/*
Naam: Hidde Camstra
Studentnummer: 1898363
Opdracht in dit bestand: OO - Doxygen.
*/
/** @file
 *  @brief 2D integer vector ADT
 *  @details
 *  This is a 2D vector ADT that stores its two components as (signed) integers.
 *  The x and y components are public attributes.
 *  The appropriate constructors and operators are provided.
 */
class vector {

private:
  bool flg_input; ///< indicates if the user made an input

public:

  /// @brief
  /// default constructor
  /// @details
  /// This constructor does not initialize the x and y attributes.
  vector();

  /// @brief
  /// multiply vector by integer
  /// @details
  /// This operator multiplies a vector by an integer, yielding a vector.
  /// The resulting vector points in the same direction as the original,
  /// but its length is rhs times longer than the original.
  /// In other words, the x and y attributes of the result are
  /// the x and y of the original, multiplied by the rhs.
  vector operator*( int rhs ) const;

  /// ...
};