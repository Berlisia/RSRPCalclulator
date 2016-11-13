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
