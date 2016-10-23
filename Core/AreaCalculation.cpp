#include "AreaCalculation.h"

AreaCalculation::AreaCalculation(std::vector<std::pair<int, int>> vectorOfPixels)
{
    for (auto pair : vectorOfPixels)
    {
        area.push_back(PixelPoint(pair));
    }
}

PixelPoint AreaCalculation::getPixel(int index)
{
    return area[index];
}
