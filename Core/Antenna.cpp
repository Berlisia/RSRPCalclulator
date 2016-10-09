#include "Antenna.h"

Antenna::Antenna(float power, int tilt, int frequency) :
    power(power),
    tilt(tilt),
    frequency(frequency)
{
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
