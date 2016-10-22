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
    int angle = 0;
    const float x = valueOfX();
    const float y = valueOfY();
    const float value = x/y;
    angle = arcTangens(value);
    float loss = antennafileProvider.getLossFromFile(angle, Charakteristic::horizontal);
    return loss;
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
        cout << "Y: " << y << endl;
    if(y < 0)
    {
        y = -y;
    }
    return y;
}


