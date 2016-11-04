#ifndef IANTENNALOSSFILEPROVIDER_H
#define IANTENNALOSSFILEPROVIDER_H
#include <iostream>

enum class Charakteristic
{
    horizontal,
    vertical
};

class IAntennaLossFileProvider
{
public:
    virtual float getLossFromFile(int angle, Charakteristic type) = 0;
    virtual ~IAntennaLossFileProvider(){}
};

#endif // IANTENNALOSSFILEPROVIDER_H
