#include "AntennaLossVerticalCalculator.h"
#include <cmath>
#include <functional>

AntennaLossVerticalCalculator::AntennaLossVerticalCalculator(std::shared_ptr<IMapDataProvider> p_mapProvider,
                                                             std::shared_ptr<IAntennaLossFileProvider> p_AntennafileProvider) :
    AntenaLossCalculator(p_mapProvider,p_AntennafileProvider),
    antennaHeight(0),
    tilt(0)
{
}

float AntennaLossVerticalCalculator::calculateAntennaLoss()
{
   int angle = calculateAngle();
   calculateAngleWithTilt(angle);
   float loss = antennafileProvider->getLossFromFile(angle, Charakteristic::vertical);
   return loss;
}

void AntennaLossVerticalCalculator::setAntennaHeight(float p_antennaHeight)
{
    antennaHeight = p_antennaHeight;
    calculateAntennaHeight();
}

void AntennaLossVerticalCalculator::setTilt(int p_tilt)
{
    tilt = p_tilt;
}

float AntennaLossVerticalCalculator::getAntennaHeight()
{
    return antennaHeight;
}

int AntennaLossVerticalCalculator::getTilt()
{
    return tilt;
}

int AntennaLossVerticalCalculator::calculateAngle()
{
    float angle = 0;
    const float distance = mapProvider->coutDistance(receiver,antenna);
    angle = atangens(distance);
    return angle;
}

void AntennaLossVerticalCalculator::calculateAntennaHeight()
{
    antennaHeight = (mapProvider->pixelHeight(antenna) + antennaHeight)
                    - mapProvider->pixelHeight(receiver);
}

void AntennaLossVerticalCalculator::calculateAngleWithTilt(int & angle)
{
    angle = angle - tilt;
    if(angle < 0)
    {
        angle = 360 + angle;
    }
}

int AntennaLossVerticalCalculator::atangens(const float distance)
{
    const float value = antennaHeight/distance;
    int angle = arcTangens(value);
    return angle;
}
