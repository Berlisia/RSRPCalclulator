#ifndef MAPPARSER_H
#define MAPPARSER_H
#pragma once
#include <string>
#include <unordered_map>
#include "Pixel.h"
#include <memory>
#include <fstream>
#include <vector>

using pixel_Map = std::vector<std::vector<Pixel>>;

class MapParser
{
public:
    MapParser();
    MapParser(std::string p_fileName);
    int getPixelHight(const std::pair<int, int> &l_xy) const;

private:
    std::string m_fileName;
    std::pair<int, int> m_mapSize;
    pixel_Map m_pixelMap;
    void loadMapFromFile();
    void getMapSizeFromFile(std::fstream& file);
    void getMapContentFromFile(std::fstream& file);

};

#endif // MAPPARSER_H
