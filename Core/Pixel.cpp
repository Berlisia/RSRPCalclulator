#include "Pixel.h"

Pixel::Pixel(std::vector<Sector *> & sectors) :
             sector(sectors)
{
}

float Pixel::getPowerFromSector(int indexOfSector)
{
    return sector[indexOfSector]->getPower();
}

double Pixel::getBandwithFromSector(int indexOfSector)
{
    return sector[indexOfSector]->getBandwith();
}

std::vector<Sector *> & Pixel::getVectorOfSectors()
{
    return sector;
}
