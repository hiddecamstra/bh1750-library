#include <Arduino.h>
#include <unity.h>
#include "BH1750.hpp"

LightSensor a;

int addressPin = 12;

void testPoweringDown(){
    a.setCommand(POWER_DOWN);
    TEST_ASSERT_EQUAL(-1, a.getLux()); // Check if received error code instead of lux measurement.
}

void testRegularRoomLight()
{
    a.setCommand(POWER_ON); // Previous test made the sensor turn off so put back on. Also testing that.
    delay(200);
    a.setMode(CONTINUOUSLY_H_RESOLUTION_MODE); // Set mode back so it will give value.
    
    float lux = a.getLux();
    TEST_ASSERT_GREATER_THAN(10, lux); // Standard values. Only checking for extreme numbers like 1 or 50000.
    TEST_ASSERT_LESS_THAN(500, lux);
}

void testSwitchingBetweenAddresses(){
    a.setAddress(H);
    delay(200);
    TEST_ASSERT_EQUAL(-1, a.getLux()); // Set address to high, but it should be low. So should be error code.

    a.setAddress(L);
    delay(200);
    TEST_ASSERT_NOT_EQUAL(-1, a.getLux()); // Set address to low, which is correct. Should give proper lux and not error code.

    digitalWrite(addressPin, HIGH);
    a.setAddress(H);
    delay(200);
    TEST_ASSERT_NOT_EQUAL(-1, a.getLux()); // Set address to high, which is correct cause addressPin also set to high.
}

void testIfCanChangeToAnyMode(){
    TEST_ASSERT_TRUE(a.setMode(CONTINUOUSLY_H_RESOLUTION_MODE));
    TEST_ASSERT_TRUE(a.setMode(CONTINUOUSLY_H_RESOLUTION_MODE2));
    TEST_ASSERT_TRUE(a.setMode(CONTINUOUSLY_L_RESOLUTION_MODE));
    TEST_ASSERT_TRUE(a.setMode(ONE_TIME_H_RESOLUTION_MODE));
    TEST_ASSERT_TRUE(a.setMode(ONE_TIME_H_RESOLUTION_MODE2));
    TEST_ASSERT_TRUE(a.setMode(ONE_TIME_L_RESOLUTION_MODE));
}

void testSpamOfGetLux(){
    for (size_t i = 0; i < 30; i++)
    {
        TEST_ASSERT_NOT_EQUAL(-1, a.getLux());
    }
}

void setup()
{
    a.begin();
    pinMode(addressPin, OUTPUT);
    delay(2000);

    UNITY_BEGIN();

    RUN_TEST(testPoweringDown);
    RUN_TEST(testRegularRoomLight);
    RUN_TEST(testSwitchingBetweenAddresses);
    RUN_TEST(testIfCanChangeToAnyMode);
    RUN_TEST(testSpamOfGetLux);

    UNITY_END();
}

void loop()
{
}