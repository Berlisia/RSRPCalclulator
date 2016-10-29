#ifndef PIXELCONTROLER_H
#define PIXELCONTROLER_H
#include "PixelXY.h"
#include "SectorsControler.h"
#include "AreaCalculation.h"
#include <memory>

class PixelControler
{
public:
    PixelControler(AreaCalculation & p_area, SectorsControler & p_sectorsControler);

    void changePixel(std::shared_ptr<PixelXY> p_pixel);

    std::pair<int,int> getPixel();
    float getPowerFromSector(int indexOfSector);
    double getBandwithFromSector(int indexOfSector);
    std::vector<Sector> &getVectorOfSectors();

    void addSector(Sector p_sector);

private:
    bool checkPixel(std::shared_ptr<PixelXY> & pixel);

    std::shared_ptr<PixelXY> pixel;
    AreaCalculation & areaCalculation;
    SectorsControler & sectorsControler; //te sektory które na niego patrzą
};

#endif // PIXELCONTROLER_H
