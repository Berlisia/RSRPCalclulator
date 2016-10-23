#ifndef PIXELPOINT_H
#define PIXELPOINT_H
#include "Sector.h"
#include <vector>

class PixelPoint
{
public:
    PixelPoint(std::pair<int, int> p_xy);

    int getX() const;
    int getY() const;
    std::pair<int, int> getXy() const;

private:
    std::pair<int, int> m_xy;
};

#endif // PIXEL_H
