#ifndef PIXELFINDER_H
#define PIXELFINDER_H
#include "PixelPoint.h"
#include "SectorsControler.h"
#include "AreaCalculation.h"
#include <memory>

class PixelFinder //Powinno byc PixelControler
{
public:
    PixelFinder(AreaCalculation & p_area, SectorsControler & p_sectorsControler);

    void changePixel(std::unique_ptr<PixelPoint> p_pixel);

    std::pair<int,int> getPixel();
    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    std::vector<Sector> &getVectorOfSectors();

    void addSector(Sector p_sector);

private:
    bool checkPixel(std::unique_ptr<PixelPoint> & pixel);

    std::unique_ptr<PixelPoint> pixel;
    AreaCalculation & areaCalculation;
    SectorsControler & sectorsControler; //te sektory które na niego patrzą
};

#endif // PIXELFINDER_H
