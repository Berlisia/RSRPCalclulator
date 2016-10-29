#include "Receiver.h"

Receiver::Receiver(std::pair<int, int> p_possition) :
    possition(PixelXY(p_possition))
{

}

PixelXY Receiver::getPossition()
{
    return possition;
}

void Receiver::setPossition(std::pair<int, int> p_possition)
{
    possition = PixelXY(p_possition);
}
