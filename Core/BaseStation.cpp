#include "BaseStation.h"

BaseStation::BaseStation(std::pair<int, int> p_positon, float p_height) :
    positon(p_positon), antennaHeight(p_height)
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
