#ifndef PIXELPOINT_H
#define PIXELPOINT_H
#include "Sector.h"
#include <vector>

class PixelPoint
{
public:
    PixelPoint(std::vector<Sector *> & sectors); //tylko sektory w odległosci 20 km

    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    std::vector<Sector *> & getVectorOfSectors();

private:
    std::vector<Sector *> & sector;
};

#endif // PIXEL_H
