#ifndef SECTORSCONTROLER_H
#define SECTORSCONTROLER_H
#include "Sector.h"
#include "Antenna.h"
#include "BaseStation.h"
#include "AntennaLoss/AntennaLossFileProvider.h"
#include <vector>
#include <memory>
#include <map>
#include <QString>

class SectorsControler
{
public:
    SectorsControler(){}
    SectorsControler(std::vector<Sector> & p_sector);

    double getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    const std::vector<Sector>& getVectorOfSectors();
    int getSectorECGI(int indexOfSector) const;
    int getBandIndexFromSector(int sectorIdx) const;

    void addSector(Sector p_sector);
    void modify(const int ecgi, const QString p_filed, const QString p_value);

private:
    std::vector<Sector> sector;
    std::map<std::shared_ptr<AntennaLossFileParser>, int> characteristicMap;
};

#endif // SECTORSCONTROLER_H
