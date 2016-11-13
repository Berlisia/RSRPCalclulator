#ifndef PIXELXY_H
#define PIXELXY_H
#include <vector>

class PixelXY
{
public:
    PixelXY(){}
    PixelXY(std::pair<int, int> p_xy);
    PixelXY(unsigned int i, unsigned int j);

    int getX() const;
    int getY() const;
    std::pair<int, int> getXy() const;

private:
    std::pair<int, int> m_xy;
};

#endif // PIXELXY_H
