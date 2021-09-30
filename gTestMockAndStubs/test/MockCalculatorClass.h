#pragma once

#include "CalculatorClass.h"
#include "/home/bojan/Desktop/unitTests/practiceWithMocks/gtest-demo/googletest-master/googlemock/include/gmock/gmock.h" // Brings in Google Mock


class MockCalculatorClass : public CalculatorClass
{
public:
    MOCK_METHOD2(add, int(int x, int y));
    MOCK_METHOD2(substract, int(int x, int y));
    MOCK_METHOD2(multiply, int(int x, int y));
    MOCK_METHOD2(divide, double(double x, double y));
};
