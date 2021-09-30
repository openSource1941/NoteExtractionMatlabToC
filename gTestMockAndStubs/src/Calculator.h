#pragma once
#include "CalculatorClass.h"
#define numberOfTimes 3
class Calculator
{

    CalculatorClass *calculations;
public:

    Calculator( CalculatorClass * calculations )
        :       calculations(calculations) {}


    bool returnSuccesufulIfDone(int, int, int)
    {
        for(int i=0; i<numberOfTimes; i++)
        {
            calculations->substract(1,2);
            calculations->multiply(1,2);
        }
        return true;
    }
    int sameNumber(int number)
    {

        calculations->add(1,2);
        calculations->substract(1,2);
        calculations->multiply(1,2);
        return number;
    }
    int forDivide(int number)
    {
        for(int i=0; i<numberOfTimes; i++)
        {
            calculations->divide(1*i,2*i);
        }

        return number;
    }

};
