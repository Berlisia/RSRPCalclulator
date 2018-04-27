#include "AreaCalculation.h"

AreaCalculation::AreaCalculation(std::vector<std::pair<int, int>> vectorOfPixels)
{
    for (auto pair : vectorOfPixels)
    {
        area.emplace_back(PixelXY(pair));
    }
}

PixelXY AreaCalculation::getPixel(int index)
{
    return area[index];
}

int AreaCalculation::beginX()
{
    return area[0].getX();
}

int AreaCalculation::beginY()
{
    return area[0].getY();
}

int AreaCalculation::endX()
{
    return area[1].getX();
}

int AreaCalculation::endY()
{
    return area[3].getY();
}
