#ifndef PIXEL_H
#define PIXEL_H
#include "Sector.h"
#include <vector>


class Pixel
{
public:
    Pixel(std::vector<Sector *> & sectors); //tylko sektory w odległosci 20 km

    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    std::vector<Sector *> & getVectorOfSectors();

private:
    std::vector<Sector *> & sector;
};

#endif // PIXEL_H
