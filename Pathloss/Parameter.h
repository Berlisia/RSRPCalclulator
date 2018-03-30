#ifndef PARAMETER_H
#define PARAMETER_H

class Parameter
{
public:
    Parameter(double maxValue, double minValue);
    double getValue();
    bool setValue(double newValue);
protected:
    double value;
    double maxValue;
    double minValue;
};

#endif // PARAMETER_H
