#include <Arduino.h>
#include <unity.h>
#include "BH1750.hpp"

/*void test_add_positive_numbers()
{
    TEST_ASSERT_EQUAL(5, MyLightSensor::add(2, 3));
}

void test_add_negative_numbers()
{
    TEST_ASSERT_EQUAL(-5, MyLightSensor::add(-2, -3));
}

void test_add_opposite_numbers()
{
    TEST_ASSERT_EQUAL(0, MyLightSensor::add(-2, 2));
}*/

void setup()
{
    UNITY_BEGIN();

    RUN_TEST(test_add_positive_numbers);
    RUN_TEST(test_add_negative_numbers);
    RUN_TEST(test_add_opposite_numbers);

    UNITY_END();
}

void loop()
{
}