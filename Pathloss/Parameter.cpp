#include "Parameter.h"

Parameter::Parameter(float maxValue, float minValue) : maxValue(maxValue), minValue(minValue)
{
}

bool Parameter::setValue(float newValue)
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

float Parameter::getValue()
{
    return value;
}
