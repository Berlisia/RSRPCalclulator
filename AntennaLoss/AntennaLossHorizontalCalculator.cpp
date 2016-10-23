#include "AntennaLossHorizontalCalculator.h"
#include <cmath>
#include <functional>
#include <iostream>
using namespace std;

AntennaLossHorizontalCalculator::AntennaLossHorizontalCalculator(IMapDataProvider & p_mapProvider, IAntennaLossFileProvider & p_AntennafileProvider) :
    AntenaLossCalculator(p_mapProvider,p_AntennafileProvider)
{
}

float AntennaLossHorizontalCalculator::calculateAntennaLoss()
{
    float loss = antennafileProvider.getLossFromFile(calculateAzimuth(), Charakteristic::horizontal);
    return loss;
}

int AntennaLossHorizontalCalculator::calculateAzimuth()
{
    int angle = 0;
    const float x = valueOfX();
    const float y = valueOfY();
    const float value = x/y;
    angle = arcTangens(value);
    return angle;
}

int AntennaLossHorizontalCalculator::valueOfX()
{
    int x = 0;
    x = receiver.first - antenna.first;
    if(x < 0)
    {
        x = -x;
    }
    return x;
}

int AntennaLossHorizontalCalculator::valueOfY()
{
    int y = 0;
    y = receiver.second - antenna.second;
    if(y < 0)
    {
        y = -y;
    }
    return y;
}


