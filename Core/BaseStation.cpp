#include "BaseStation.h"

BaseStation::BaseStation(std::pair<int, int> p_positon, float p_height, std::string p_name) :
    positon(p_positon), antennaHeight(p_height), name(p_name)
{

}

float BaseStation::getAntennaHeight()
{
    return antennaHeight;
}

std::pair<int, int> BaseStation::getPossition()
{
    return positon.getXy();
}

std::string BaseStation::getName()
{
    return name;
}
