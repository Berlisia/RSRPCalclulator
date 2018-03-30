#ifndef IANTENNALOSSFILEPROVIDER_H
#define IANTENNALOSSFILEPROVIDER_H
#include <iostream>
#include <QString>

enum class Charakteristic
{
    horizontal,
    vertical
};

class IAntennaLossFileProvider
{
public:
    virtual double getLossFromFile(int angle, Charakteristic type) = 0;
    virtual void changeFileHorizontal(QString path) = 0;
    virtual void changeFileVertical(QString path) = 0;
    virtual ~IAntennaLossFileProvider(){}
};

#endif // IANTENNALOSSFILEPROVIDER_H
