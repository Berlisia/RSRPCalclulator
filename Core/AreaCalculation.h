#ifndef AREACALCULATION_H
#define AREACALCULATION_H
#include <vector>
#include "PixelPoint.h"

class AreaCalculation
{
public:
    AreaCalculation(std::vector<std::pair<int,int>> vectorOfPixels);

    PixelPoint getPixel(int index);

private:
    std::vector<PixelPoint> area;
};

#endif // AREACALCULATION_H
