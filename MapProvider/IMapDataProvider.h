#ifndef IMAPDATAPROVIDER_H
#define IMAPDATAPROVIDER_H
#pragma once
#include <utility>

class IMapDataProvider
{
public:
    virtual unsigned int pixelHeight(std::pair<int,int> p_pixel) = 0;
    virtual float coutDistance(std::pair<int,int> p_pixel1, std::pair<int,int> p_pixel2) = 0;
    virtual ~IMapDataProvider(){}
};

#endif // IMAPDATAPROVIDER_H
