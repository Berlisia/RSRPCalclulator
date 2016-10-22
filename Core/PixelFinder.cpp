#include "PixelFinder.h"

PixelFinder::PixelFinder(vectorOfPixels & p_area) :
    areaCalculation(p_area)
{

}

void PixelFinder::changePixel(PixelPoint *p_pixel)
{
    if(checkPixel(p_pixel))
    {
        pixel.reset(p_pixel);
    }
}

vectorOfPixels & PixelFinder::getArea()
{
    return areaCalculation;
}

std::unique_ptr<PixelPoint> PixelFinder::getPixel()
{
    return pixel;
}

bool PixelFinder::checkPixel(PixelPoint *p_pixel)
{
    return areaCalculation[0].getX() < p_pixel->getX() and
           areaCalculation[0].getY() < p_pixel->getY() and
           areaCalculation[4].getX() > p_pixel->getX() and
           areaCalculation[4].getY() > p_pixel->getY();
}
