#ifndef SECTORSCONTROLER_H
#define SECTORSCONTROLER_H
#include "Sector.h"
#include "Antenna.h"
#include "BaseStation.h"
#include <vector>

class SectorsControler
{
public:
    SectorsControler(std::vector<Sector> & p_sector);

    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    std::vector<Sector> &getVectorOfSectors();
    void addSector(Antenna & antenna, BaseStation & base);
    void addSector(Sector p_sector);

private:
    std::vector<Sector> & sector;
};

#endif // SECTORSCONTROLER_H
