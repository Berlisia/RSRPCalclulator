#include "AnetnnaLossCalculator.h"
#include <cmath>
#include <functional>

const int AntenaLossCalculator::stopnie = 180;
const double AntenaLossCalculator::PI = 3.14;
const int AntenaLossCalculator::circle = 360;

AntenaLossCalculator::AntenaLossCalculator(std::shared_ptr<IMapDataProvider> p_mapProvider,
                                           std::shared_ptr<IAntennaLossFileProvider> p_AntennafileProvider)
    : mapProvider(std::move(p_mapProvider)),
      antennafileProvider(std::move(p_AntennafileProvider)),
      receiver(0, 0),
      antenna(0, 0)
{
}

void AntenaLossCalculator::setReceiver(std::pair<int, int> p_receiver)
{
    receiver = p_receiver;
}

void AntenaLossCalculator::setAntenna(std::pair<int, int> p_antenna)
{
    antenna = p_antenna;
}

std::pair<int, int> AntenaLossCalculator::getAntennaPossiton()
{
    return antenna;
}

int AntenaLossCalculator::arcTangens(const double value)
{
    double angle = 0;
    angle = std::atan(value);
    angle = angle * stopnie / PI;
    angle = std::round(angle);
    return angle;
}
