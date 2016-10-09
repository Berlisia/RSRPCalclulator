#ifndef PARAMETER_H
#define PARAMETER_H

class Parameter
{
public:
    Parameter(int maxValue, int minValue);
    float getValue();
    bool setValue(float newValue);
protected:
    float value;
    int maxValue;
    int minValue;
};

#endif // PARAMETER_H
