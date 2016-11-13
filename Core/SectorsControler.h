#ifndef SECTORSCONTROLER_H
#define SECTORSCONTROLER_H
#include "Sector.h"
#include "Antenna.h"
#include "BaseStation.h"
#include <vector>
#include <memory>

class SectorsControler
{
public:
    SectorsControler(){}
    SectorsControler(std::vector<Sector> & p_sector);

    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    const std::vector<Sector>& getVectorOfSectors();

    void addSector(Sector p_sector);

private:
    std::vector<Sector> sector;
};

#endif // SECTORSCONTROLER_H
