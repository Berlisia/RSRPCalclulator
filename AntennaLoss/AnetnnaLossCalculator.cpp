#include "AnetnnaLossCalculator.h"
#include <cmath>
#include <functional>

const int AntenaLossCalculator::stopnie = 180;
const float AntenaLossCalculator::PI = 3.14;
const int AntenaLossCalculator::circle = 360;

AntenaLossCalculator::AntenaLossCalculator(IMapDataProvider & p_mapProvider,
                                            IAntennaLossFileProvider & p_AntennafileProvider) :
    mapProvider(p_mapProvider),
    antennafileProvider(p_AntennafileProvider),
    receiver(0,0),
    antenna(0,0)
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

int AntenaLossCalculator::arcTangens(const float value)
{
    float angle = 0;
    angle = std::atan(value);
    angle = angle * stopnie/PI;
    angle = std::round(angle);
    return angle;
}
