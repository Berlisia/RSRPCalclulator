#ifndef PIXELXY_H
#define PIXELXY_H
#include <vector>

class PixelXY
{
public:
    PixelXY(std::pair<int, int> p_xy);

    int getX() const;
    int getY() const;
    std::pair<int, int> getXy() const;

private:
    std::pair<int, int> m_xy;
};

#endif // PIXELXY_H
