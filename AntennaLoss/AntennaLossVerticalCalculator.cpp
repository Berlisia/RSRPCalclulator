#include "AntennaLossVerticalCalculator.h"
#include <cmath>
#include <functional>

AntennaLossVerticalCalculator::AntennaLossVerticalCalculator(
    std::shared_ptr<IMapDataProvider> p_mapProvider,
    std::shared_ptr<IAntennaLossFileProvider> p_AntennafileProvider)
    : AntenaLossCalculator(std::move(p_mapProvider), std::move(p_AntennafileProvider)), antennaHeight(0), tilt(0)
{
}

double AntennaLossVerticalCalculator::calculateAntennaLoss()
{
    int angle = calculateAngle();
    calculateAngleWithTilt(angle);
    double loss = antennafileProvider->getLossFromFile(angle, Charakteristic::vertical);
    return loss;
}

void AntennaLossVerticalCalculator::setAntennaHeight(double p_antennaHeight)
{
    antennaHeight = p_antennaHeight;
    calculateAntennaHeight();
}

void AntennaLossVerticalCalculator::setTilt(int p_tilt)
{
    tilt = p_tilt;
}

double AntennaLossVerticalCalculator::getAntennaHeight()
{
    return antennaHeight;
}

int AntennaLossVerticalCalculator::getTilt()
{
    return tilt;
}

int AntennaLossVerticalCalculator::calculateAngle()
{
    double angle = 0;
    const double distance = mapProvider->coutDistance(receiver, antenna);
    angle = atangens(distance);
    return angle;
}

void AntennaLossVerticalCalculator::calculateAntennaHeight()
{
    antennaHeight = (mapProvider->pixelHeight(antenna) + antennaHeight) - mapProvider->pixelHeight(receiver);
}

void AntennaLossVerticalCalculator::calculateAngleWithTilt(int& angle)
{
    angle = angle - tilt;
    if (angle < 0)
    {
        angle = 360 + angle;
    }
}

int AntennaLossVerticalCalculator::atangens(const double distance)
{
    const double value = antennaHeight / distance;
    int angle = arcTangens(value);
    return angle;
}
