#ifndef IANTENNALOSSFILEPROVIDER_H
#define IANTENNALOSSFILEPROVIDER_H

enum class Charakteristic
{
    horizontal,
    vertical
};

class IAntennaLossFileProvider
{
public:
    virtual float getLossFromFile(int angle, Charakteristic type) = 0;

};

#endif // IANTENNALOSSFILEPROVIDER_H
