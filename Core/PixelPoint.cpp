#include "PixelPoint.h"

PixelPoint::PixelPoint(std::vector<Sector *> & sectors) :
             sector(sectors)
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
