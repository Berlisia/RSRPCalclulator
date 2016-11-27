#include "GeographicalCoordinatesConverter.h"
#include "wgs84_do_puwg92.h"
#include <cmath>

const float GeographicalCoordinatesConverter::m_ulxmap = 273650.500000;
const float GeographicalCoordinatesConverter::m_ulymap = 383600.500000;
const int GeographicalCoordinatesConverter::m_maxX = 3942;
const int GeographicalCoordinatesConverter::m_maxY = 3802;

GeographicalCoordinatesConverter::GeographicalCoordinatesConverter()
{

}

std::pair<double,double> GeographicalCoordinatesConverter::pixelToGeographicalCoordinates(std::pair<int, int> p_pixel) const
{
    double l_geographicalCoordinatesX = 0;
    double l_geographicalCoordinatesY = 0;
    double l_xInMeters = m_ulxmap + ((m_maxX - p_pixel.first) * 25);
    double l_yInMeters = m_ulymap - ((m_maxY - p_pixel.second) * 25);
    puwg92_do_wgs84(l_xInMeters, l_yInMeters, &l_geographicalCoordinatesX, &l_geographicalCoordinatesY);

    std::pair<double,double> l_geographicalCoordinates(l_geographicalCoordinatesX, l_geographicalCoordinatesY);
    return l_geographicalCoordinates;
}

std::pair<int, int> GeographicalCoordinatesConverter::geographicalCoordinatesToPixel(std::pair<double, double> p_coordinates) const
{
    double l_pxX = 0;
    double l_pxY = 0;
    wgs84_do_puwg92(p_coordinates.first, p_coordinates.second, &l_pxX, &l_pxY);

    l_pxX = std::round(m_maxX - ((l_pxX - m_ulxmap) / 25));
    l_pxY = std::round(m_maxY - ((m_ulymap - l_pxY) / 25));
    std::pair<double,double> pixel(l_pxY, l_pxX);
    return pixel;
}

