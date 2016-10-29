#include "AreaCalculation.h"

AreaCalculation::AreaCalculation(std::vector<std::pair<int, int>> vectorOfPixels)
{
    for (auto pair : vectorOfPixels)
    {
        area.push_back(PixelXY(pair));
    }
}

PixelXY AreaCalculation::getPixel(int index)
{
    return area[index];
}
