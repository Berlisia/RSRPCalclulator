#include "PixelControler.h"
#include <iostream>

PixelControler::PixelControler(AreaCalculation &p_area, SectorsControler & p_sectorsControler) :
    areaCalculation(p_area),
    sectorsControler(p_sectorsControler)
{
    pixel = std::make_shared<PixelXY>(std::make_pair<int,int>(0,0));
}

void PixelControler::changePixel(std::shared_ptr<PixelXY> p_pixel)
{
    if(checkPixel(p_pixel))
    {
        pixel = p_pixel;
    }
    else
    {
        std::cout << "Upsss" << std::endl;
    }
}

std::pair<int, int> PixelControler::getPixel()
{
    return pixel->getXy();
}

float PixelControler::getPowerFromSector(int indexOfSector)
{
    return sectorsControler.getPowerFromSector(indexOfSector);
}

double PixelControler::getBandwithFromSector(int indexOfSector)
{
    return sectorsControler.getBandwithFromSector(indexOfSector);
}

std::vector<Sector> &PixelControler::getVectorOfSectors()
{
    return sectorsControler.getVectorOfSectors();
}

void PixelControler::addSector(Sector p_sector)
{
    sectorsControler.addSector(p_sector);
}

bool PixelControler::checkPixel(std::shared_ptr<PixelXY> &pixel)
{
    return (areaCalculation.getPixel(0).getX() <= pixel->getX()) and
           (areaCalculation.getPixel(0).getY() <= pixel->getY()) and
           (areaCalculation.getPixel(3).getX() >= pixel->getX()) and
           (areaCalculation.getPixel(3).getY() >= pixel->getY());
}
