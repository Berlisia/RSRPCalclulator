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
    SectorsControler(std::vector<Sector> & p_sector);

    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    std::shared_ptr<std::vector<Sector> > getVectorOfSectors();
    void addSector(Antenna & antenna, BaseStation & base);
    void addSector(Sector p_sector);

private:
    std::shared_ptr<std::vector<Sector>> sector;
};

#endif // SECTORSCONTROLER_H
