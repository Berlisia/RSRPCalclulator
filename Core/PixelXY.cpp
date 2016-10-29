#include "PixelXY.h"

PixelXY::PixelXY(std::pair<int, int> p_xy) :
    m_xy(p_xy)
{

}

int PixelXY::getX() const
{
    return m_xy.first;
}

int PixelXY::getY() const
{
    return m_xy.second;
}

std::pair<int, int> PixelXY::getXy() const
{
    return m_xy;
}
