#include "MapParser.h"
#include <iostream>
#include <fstream>
#include <limits>

void goToLine(std::fstream& file, int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

MapParser::MapParser(): m_fileName("asd.pgm"){loadMapFromFile();}

MapParser::MapParser(std::string p_fileName): m_fileName(p_fileName){}

int MapParser::getPixelHight(const std::pair<int, int> &l_xy) const
{
    return m_pixelMap[l_xy.first][l_xy.second].getHight();
}

void MapParser::loadMapFromFile()
{
    std::fstream file(m_fileName, std::ios::in);
    if (file.is_open())
    {
        getMapSizeFromFile(file);
        getMapContentFromFile(file);
    }
}

void MapParser::getMapSizeFromFile(std::fstream &file)
{
    goToLine(file, 3);
    file >> m_mapSize.first;
    file >> m_mapSize.second;
    m_pixelMap.resize(m_mapSize.second, std::vector<Pixel>(m_mapSize.first));
    std::cout << "Wczytuje mape x:" << m_mapSize.second<< " y:" << m_mapSize.first << std::endl;
}

void MapParser::getMapContentFromFile(std::fstream &file)
{
    goToLine(file, 5);
    unsigned int l_height;
    int l_x;
    int l_y;
    std::cout << "Wczytywanie mapy"<<std::endl;
    for (int i=0;i<m_mapSize.first*m_mapSize.second;i++)
    {
        l_y = i/m_mapSize.second;
        l_x = i-l_y*m_mapSize.second;
        file >> l_height;
        std::pair<int, int> l_xy(l_x, l_y);
        m_pixelMap[l_x][l_y] = Pixel(l_xy, l_height, Enviroment_NotDefined);
    }
}
