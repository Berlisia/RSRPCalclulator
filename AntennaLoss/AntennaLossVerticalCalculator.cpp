#include "AntennaLossVerticalCalculator.h"
#include <cmath>
#include <functional>

AntennaLossVerticalCalculator::AntennaLossVerticalCalculator(IMapDataProvider & p_mapProvider, IAntennaLossFileProvider & p_AntennafileProvider) :
    mapProvider(p_mapProvider),
    antennafileProvider(p_AntennafileProvider)
{
}

float AntennaLossVerticalCalculator::calculateAntennaLoss()
{
   int angle = calculateAngle();
   angle = angle - tilt;
   float loss = antennafileProvider.getLossFromFile(angle, Charakteristic::vertical);
   return loss;
}

void AntennaLossVerticalCalculator::setReceiver(std::pair<int, int> p_receiver)
{
    receiver = p_receiver;
}

void AntennaLossVerticalCalculator::setAntenna(std::pair<int, int> p_antenna)
{
    antenna = p_antenna;
}

void AntennaLossVerticalCalculator::setAntennaHeight(float p_antennaHeight)
{
    antennaHeight = p_antennaHeight;
}

void AntennaLossVerticalCalculator::setTilt(int p_tilt)
{
    tilt = p_tilt;
}

int AntennaLossVerticalCalculator::calculateAngle()
{
    int angle = -1;
    float distance = mapProvider.coutDistance(receiver,antenna);
    angle = std::atan(antennaHeight/distance);
    return angle;
}
