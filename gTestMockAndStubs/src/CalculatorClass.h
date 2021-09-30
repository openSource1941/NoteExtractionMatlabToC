#pragma once


class CalculatorClass
{

public:

    virtual ~CalculatorClass() {}
    virtual int add(int a,int b) = 0;
    virtual int substract(int a,int b) = 0;
    virtual int multiply(int a,int b) = 0;
    virtual double divide(double a,double b) = 0;
    double factoriel(int number);
};

