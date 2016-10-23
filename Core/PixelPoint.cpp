#include "PixelPoint.h"

PixelPoint::PixelPoint(std::pair<int, int> p_xy) :
    m_xy(p_xy)
{

}

int PixelPoint::getX() const
{
    return m_xy.first;
}

int PixelPoint::getY() const
{
    return m_xy.second;
}

std::pair<int, int> PixelPoint::getXy() const
{
    return m_xy;
}
