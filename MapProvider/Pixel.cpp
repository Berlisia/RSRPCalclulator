#include "Pixel.h"


Enviroment Pixel::getEnv() const
{
    return m_env;
}

int Pixel::getX() const
{
    return m_xy.first;
}

int Pixel::getY() const
{
    return m_xy.second;
}

std::pair<int, int> Pixel::getXy() const
{
    return m_xy;
}

unsigned int Pixel::getHight() const
{
    return m_hight;
}
