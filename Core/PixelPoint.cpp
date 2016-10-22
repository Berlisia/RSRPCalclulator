#include "PixelPoint.h"

//PixelPoint::PixelPoint(std::vector<Sector *> & sectors) :
//             sector(sectors)
//{
//}

PixelPoint::PixelPoint(std::pair<int, int> p_xy) :
    m_xy(p_xy)
{

}

float PixelPoint::getPowerFromSector(int indexOfSector)
{
    return sector[indexOfSector]->getPower();
}

double PixelPoint::getBandwithFromSector(int indexOfSector)
{
    return sector[indexOfSector]->getBandwith();
}

std::vector<Sector *> & PixelPoint::getVectorOfSectors()
{
    return sector;
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
