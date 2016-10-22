#include "AnetnnaLossCalculator.h"
#include <cmath>
#include <functional>
#include <iostream>
using namespace std;

const int AntenaLossCalculator::stopnie = 180;
const float AntenaLossCalculator::PI = 3.14;

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
    cout << angle << endl;
    angle = angle * stopnie/PI;
        cout << angle << endl;
    angle = std::round(angle);
    return angle;
}
