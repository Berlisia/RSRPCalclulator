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
    int azimuthForZeroDeegres = calculateAzimuth();
    cout << "zero deegres: " << azimuthForZeroDeegres << endl;
    int l_azimuth = relativeAzimuth(azimuthForZeroDeegres);
    cout << "l_azimuth: " << l_azimuth << endl;

    float loss = antennafileProvider.getLossFromFile(l_azimuth, Charakteristic::horizontal);
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

int AntennaLossHorizontalCalculator::setAzimuth(int p_azimuth)
{
    azimuth = p_azimuth;
}

int AntennaLossHorizontalCalculator::relativeAzimuth(int p_azimuthForZeroDeegres)
{
    int l_azimuth = 0;

    if(azimuth <= 180 || azimuth >= 0)
    {
        l_azimuth = azimuth - p_azimuthForZeroDeegres;
    }
    else if(azimuth > 180 || azimuth < PI)
    {
        l_azimuth = PI - azimuth + p_azimuthForZeroDeegres;
    }

    return l_azimuth;
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


