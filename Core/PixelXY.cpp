#include "PixelXY.h"

PixelXY::PixelXY(std::pair<int, int> p_xy) :
    m_xy(p_xy)
{

}

PixelXY::PixelXY(unsigned int i, unsigned int j)
{
    m_xy = std::make_pair<int,int>(i,j);
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
