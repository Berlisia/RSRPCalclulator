#ifndef PIXELFINDER_H
#define PIXELFINDER_H
#include "PixelPoint.h"
#include <memory>
#include <vector>

typedef std::vector<PixelPoint> vectorOfPixels;

class PixelFinder
{
public:
    PixelFinder(vectorOfPixels & p_area);

    void changePixel(PixelPoint * p_pixel);
    vectorOfPixels & getArea();
    std::unique_ptr<PixelPoint> getPixel();

private:
    bool checkPixel(PixelPoint * p_pixel);

    std::unique_ptr<PixelPoint> pixel;
    vectorOfPixels & areaCalculation;
};

#endif // PIXELFINDER_H
