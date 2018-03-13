#include "MapParser.h"
//#include <boost/progress.hpp>
#include <QDebug>
#include <QFile>

namespace
{
void skipLines(QTextStream& fileStream, int num)
{
    for (int i = 0; i < num - 1; ++i)
    {
        fileStream.readLine();
    }
}
}

MapParser::MapParser(): m_fileName(":/mapy/mapa"){loadMapFromFile();}

MapParser::MapParser(QString p_fileName): m_fileName(std::move(p_fileName)){}

int MapParser::getPixelHight(const std::pair<int, int> &l_xy) const
{
    return m_pixelMap[l_xy.first][l_xy.second].getHight();
}

void MapParser::loadMapFromFile()
{
    QFile file(m_fileName);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        getMapSizeFromFile(in);
        getMapContentFromFile(in);
    }
}

void MapParser::getMapSizeFromFile(QTextStream& fileStream)
{
    skipLines(fileStream, 3);
    fileStream >> m_mapSize.first;
    fileStream >> m_mapSize.second;
    m_pixelMap.resize(m_mapSize.first, std::vector<Pixel>(m_mapSize.second));
    qDebug() << "Wczytuje mape x:" << m_mapSize.first<< " y:" << m_mapSize.second;
}

void MapParser::getMapContentFromFile(QTextStream& fileStream)
{
    skipLines(fileStream, 2);
    unsigned int l_height;
    int l_x;
    int l_y;
    qDebug() << "Wczytywanie mapy";
    //boost::progress_display show_progress(m_mapSize.first * m_mapSize.second);
    for (int i=0; i<m_mapSize.first*m_mapSize.second; i++)
    {
        l_y = i/m_mapSize.first;
        l_x = i-l_y*m_mapSize.first;
        fileStream >> l_height;
        std::pair<int, int> l_xy(l_x, l_y);
        m_pixelMap[l_x][l_y] = Pixel(l_xy, l_height, Enviroment_NotDefined);
        //++show_progress;
    }
}
