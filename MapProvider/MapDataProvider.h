#ifndef MAPDATAPROVIDER_H
#define MAPDATAPROVIDER_H
#pragma once
#include "IMapDataProvider.h"
#include "MapParser.h"
#include <memory>
#include <iostream>

class MapDataProvider: public IMapDataProvider
{
public:
    MapDataProvider();
    unsigned int pixelHeight(std::pair<int,int> p_pixel) override;
    float coutDistance(std::pair<int,int> p_pixel1, std::pair<int,int> p_pixel2) override;
    ~MapDataProvider(){}
private:
    std::unique_ptr<MapParser> m_mapParser;
};

#endif // MAPDATAPROVIDER_H
