#ifndef MAPPARSER_H
#define MAPPARSER_H
#pragma once
#include "Pixel.h"
#include <vector>
#include <QTextStream>

using pixel_Map = std::vector<std::vector<Pixel>>;

class MapParser
{
public:
    MapParser();
    MapParser(const QString &p_fileName);
    int getPixelHight(const std::pair<int, int> &l_xy) const;

private:
    QString m_fileName;
    std::pair<int, int> m_mapSize;
    pixel_Map m_pixelMap;
    void loadMapFromFile();
    void getMapSizeFromFile(QTextStream &fileStream);
    void getMapContentFromFile(QTextStream &fileStream);

};

#endif // MAPPARSER_H
