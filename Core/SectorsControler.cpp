#include "SectorsControler.h"

SectorsControler::SectorsControler(std::vector<Sector> &p_sector) :
    sector(p_sector)
{
}

float SectorsControler::getPowerFromSector(int indexOfSector)
{
    return sector[indexOfSector].getPower();
}

double SectorsControler::getBandwithFromSector(int indexOfSector)
{
    return sector[indexOfSector].getBandwith();
}

std::vector<Sector> &SectorsControler::getVectorOfSectors()
{
    return sector;
}

void SectorsControler::addSector(Antenna &antenna, BaseStation &base)
{
    sector.push_back(Sector(antenna,base));
}

void SectorsControler::addSector(Sector p_sector)
{
    sector.push_back(p_sector);
}
