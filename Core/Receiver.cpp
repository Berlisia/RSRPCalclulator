#include "Receiver.h"

Receiver::Receiver()
{
}

PixelXY Receiver::getPossition()
{
    return possition;
}

float Receiver::getHeight()
{
    return height;
}

void Receiver::setPossition(std::pair<int, int> p_possition)
{
    possition = PixelXY(p_possition);
}

void Receiver::setHeight(float value)
{
    height = value;
}

double Receiver::getGain() const
{
    return gain;
}

void Receiver::setGain(double value)
{
    gain = value;
}

double Receiver::getOtherLosses() const
{
    return otherLosses;
}

void Receiver::setOtherLosses(double value)
{
    otherLosses = value;
}
