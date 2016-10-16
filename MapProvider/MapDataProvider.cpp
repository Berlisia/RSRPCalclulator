#include "MapDataProvider.h"
#include <math.h>
MapDataProvider::MapDataProvider(): m_mapParser(std::make_unique<MapParser>()){}

unsigned int MapDataProvider::pixelHeight(std::pair<int, int> p_pixel)
{
    return m_mapParser->getPixelHight(p_pixel);
}

float MapDataProvider::coutDistance(std::pair<int, int> p_pixel1, std::pair<int, int> p_pixel2)
{
    return pow((pow(p_pixel1.first-p_pixel2.first, 2)+pow(p_pixel1.second-p_pixel2.second,2)),0.5)*25;
}
