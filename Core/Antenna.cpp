#include "Antenna.h"

Antenna::Antenna(float power, int tilt, int frequency, std::string fileH, std::string fileV) :
    power(power),
    tilt(tilt),
    frequency(frequency),
    fileNameH(fileH),
    fileNameV(fileV)
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

std::string Antenna::getFileNameH()
{
    return fileNameH;
}

std::string Antenna::getFileNameV()
{
    return fileNameV;
}

