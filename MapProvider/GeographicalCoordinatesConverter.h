#ifndef GEOGRAPHICALCOORDINATESCONVERTER_H
#define GEOGRAPHICALCOORDINATESCONVERTER_H
#include <utility>

class GeographicalCoordinatesConverter
{
public:
    GeographicalCoordinatesConverter();

    std::pair<double, double> pixelToGeographicalCoordinates(std::pair<int,int> p_pixel) const;
    std::pair<int,int> geographicalCoordinatesToPixel(std::pair<double, double> p_coordinates) const;

private:
    static const float m_ulxmap;
    static const float m_ulymap;
    static const int m_maxX;
    static const int m_maxY;
};

#endif // GEOGRAPHICALCOORDINATESCONVERTER_H
