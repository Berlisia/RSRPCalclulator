#ifndef PARAMETER_H
#define PARAMETER_H

class Parameter
{
public:
    Parameter(float maxValue, float minValue);
    float getValue();
    bool setValue(float newValue);
protected:
    float value;
    float maxValue;
    float minValue;
};

#endif // PARAMETER_H
