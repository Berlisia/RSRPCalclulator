#ifndef BASESTATION_H
#define BASESTATION_H
#include "PixelXY.h"
#include <string>

class BaseStation
{
public:
    BaseStation(std::pair<int,int> p_positon, float p_height, std::string p_name);

    float getAntennaHeight();
    std::pair<int,int> getPossition();
    std::string getName();

private:
    PixelXY positon;
    float antennaHeight;
    std::string name;
};

#endif // BASESTATION_H
