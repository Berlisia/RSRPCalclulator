#include "PixelFinder.h"
#include <iostream>

PixelFinder::PixelFinder(AreaCalculation &p_area, SectorsControler & p_sectorsControler) :
    areaCalculation(p_area),
    sectorsControler(p_sectorsControler)
{
    pixel = std::make_unique<PixelPoint>(std::make_pair<int,int>(0,0));
}

void PixelFinder::changePixel(std::unique_ptr<PixelPoint> p_pixel)
{
    if(checkPixel(p_pixel))
    {
        pixel = std::move(p_pixel);
    }
    else
    {
        std::cout << "Upsss" << std::endl;
    }
}

std::pair<int, int> PixelFinder::getPixel()
{
    return pixel->getXy();
}

float PixelFinder::getPowerFromSector(int indexOfSector)
{
    return sectorsControler.getPowerFromSector(indexOfSector);
}

double PixelFinder::getBandwithFromSector(int indexOfSector)
{
    return sectorsControler.getBandwithFromSector(indexOfSector);
}

std::vector<Sector> &PixelFinder::getVectorOfSectors()
{
    return sectorsControler.getVectorOfSectors();
}

void PixelFinder::addSector(Sector p_sector)
{
    sectorsControler.addSector(p_sector);
}

bool PixelFinder::checkPixel(std::unique_ptr<PixelPoint> & pixel)
{
    return (areaCalculation.getPixel(0).getX() <= pixel->getX()) and
           (areaCalculation.getPixel(0).getY() <= pixel->getY()) and
           (areaCalculation.getPixel(3).getX() >= pixel->getX()) and
           (areaCalculation.getPixel(3).getY() >= pixel->getY());
}
