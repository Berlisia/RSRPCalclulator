#include "Receiver.h"

PixelXY Receiver::getPossition() const
{
    return possition;
}

double Receiver::getHeight() const
{
    return height;
}

void Receiver::setPossition(std::pair<int, int> p_possition)
{
    possition = PixelXY(p_possition);
}

void Receiver::setHeight(double value)
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
