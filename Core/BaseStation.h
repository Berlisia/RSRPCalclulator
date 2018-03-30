#ifndef BASESTATION_H
#define BASESTATION_H
#include "PixelXY.h"
#include <string>

class BaseStation
{
public:
    BaseStation(std::pair<int,int> p_positon, double p_height, std::string p_name);

    double getAntennaHeight();
    std::pair<int,int> getPossition();
    std::string getName();

private:
    PixelXY positon;
    double antennaHeight;
    std::string name;
};

#endif // BASESTATION_H
