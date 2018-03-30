#include "MapDataProvider.h"
#include <cmath>

namespace
{
    template< typename T1, typename T2>
    auto operator-(std::pair<T1, T2> p_pixel1,
                   std::pair<T1, T2> p_pixel2)
    {
        return std::pair<T1, T2>(
                    p_pixel1.first - p_pixel2.first,
                    p_pixel1.second - p_pixel2.second);
    }
    template< typename T1, typename T2>
    auto operator+(std::pair<T1, T2> p_pixel1,
                   std::pair<T1, T2> p_pixel2)
    {
        return std::pair<T1, T2>(
                    p_pixel1.first + p_pixel2.first,
                    p_pixel1.second + p_pixel2.second);
    }
    auto operator/(std::pair<int, int> p_pixel1,
                   double p_divider)
    {
        return std::pair<double, double>(
                    p_pixel1.first / p_divider,
                    p_pixel1.second / p_divider);
    }
}

MapDataProvider::MapDataProvider():
    m_mapParser(std::make_unique<MapParser>())
{
}

unsigned int MapDataProvider::pixelHeight(std::pair<int, int> p_pixel)
{
    return m_mapParser->getPixelHight(p_pixel);
}

double MapDataProvider::coutDistance(std::pair<int, int> p_pixel1,
                                    std::pair<int, int> p_pixel2)
{
    return pow((pow(p_pixel1.first-p_pixel2.first, 2)+pow(p_pixel1.second-p_pixel2.second,2)),0.5)*25;
}

double MapDataProvider::coutMediumHeightBetwenTwoPixels(std::pair<int, int> p_pixel1,
                                                       std::pair<int, int> p_pixel2,
                                                       int p_interwal)
{
    int l_jumps = coutDistance(p_pixel1, p_pixel2) / p_interwal;

    if(l_jumps<1)
    {
        return (pixelHeight(p_pixel1)+pixelHeight(p_pixel2)) / 2;
    }

    auto l_jumper = (p_pixel2 - p_pixel1) / l_jumps;

    std::pair<double, double> l_last = p_pixel1;
    double l_sumaryHeight = 0;
    for(int i = 0; i < l_jumps; i++)
    {
        l_sumaryHeight += pixelHeight(l_last);
        l_last = l_last + l_jumper;
    }

    return (l_sumaryHeight + pixelHeight(p_pixel2)) / (l_jumps + 1);
}

std::vector<std::pair<int, int> > MapDataProvider::getVectorOfPixels(std::pair<int, int> p_pixel1,
                                                                     std::pair<int, int> p_pixel2,
                                                                     int p_interwal)
{
    int l_jumps = coutDistance(p_pixel1, p_pixel2) / p_interwal;

    if(l_jumps<1)
    {
        std::vector<std::pair<int, int>> vector;
        vector.push_back(p_pixel1);
        vector.push_back(p_pixel2);
        return std::move(vector);
    }

    auto l_jumper = (p_pixel2 - p_pixel1) / l_jumps;

    std::pair<double,double> l_last = p_pixel1;
    std::vector<std::pair<int, int>> vector;
    for(int i = 0; i < l_jumps; i++)
    {
        vector.push_back(l_last);
        l_last = l_last + l_jumper;
    }

    return std::move(vector);
}
