#ifndef BASESTATION_H
#define BASESTATION_H
#include "PixelXY.h"


class BaseStation
{
public:
    BaseStation(std::pair<int,int> p_positon, float p_height);

    float getAntennaHeight();
    std::pair<int,int> getPossition();

private:
    PixelXY positon;
    float antennaHeight;
//    int numberOfSectors;
};

#endif // BASESTATION_H
