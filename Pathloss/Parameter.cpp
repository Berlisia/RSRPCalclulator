#include "Parameter.h"

Parameter::Parameter(double maxValue, double minValue) : maxValue(maxValue), minValue(minValue)
{
}

bool Parameter::setValue(double newValue)
{
    //if(newValue <= maxValue || newValue >= minValue)
    //{
        value = newValue;
        return true;
    //}
    //else
    ///{
       // return false;
    //
}

double Parameter::getValue()
{
    return value;
}
