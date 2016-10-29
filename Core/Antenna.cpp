#include "Antenna.h"

Antenna::Antenna(float power, int tilt, int frequency) :
    power(power),
    tilt(tilt),
    frequency(frequency)
{
    position = std::pair<int,int>(position);
}

void Antenna::setPower(float newPower)
{
    power = newPower;
}

void Antenna::setTilt(int newTilt)
{
    tilt = newTilt;
}

void Antenna::setFrequency(int newFrequency)
{
    frequency = newFrequency;
}

float Antenna::getPower()
{
    return power;
}

int Antenna::getTilt()
{
    return tilt;
}

std::pair<int, int> Antenna::getPosition()
{
    return position;
}
