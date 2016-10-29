#ifndef AREACALCULATION_H
#define AREACALCULATION_H
#include <vector>
#include "PixelXY.h"

class AreaCalculation
{
public:
    AreaCalculation(std::vector<std::pair<int,int>> vectorOfPixels);

    PixelXY getPixel(int index);

private:
    std::vector<PixelXY> area;
};

#endif // AREACALCULATION_H
