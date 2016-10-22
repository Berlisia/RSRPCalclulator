#ifndef PIXELPOINT_H
#define PIXELPOINT_H
#include "Sector.h"
#include <vector>

class PixelPoint
{
public:
    PixelPoint(std::vector<Sector *> & sectors); //tylko sektory w odległosci 20 km
    PixelPoint(std::pair<int, int> p_xy);

    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    std::vector<Sector *> & getVectorOfSectors();

    int getX() const;
    int getY() const;
    std::pair<int, int> getXy() const;

private:
    std::vector<Sector *> & sector;
    std::pair<int, int> m_xy;
};

#endif // PIXEL_H
