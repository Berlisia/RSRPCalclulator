#include "AntennaLossHorizontalCalculator.h"
#include <cmath>
#include <functional>
#include <iostream>

AntennaLossHorizontalCalculator::AntennaLossHorizontalCalculator(std::shared_ptr<IMapDataProvider> p_mapProvider,
                                                                 std::shared_ptr<IAntennaLossFileProvider> p_AntennafileProvider) :
    AntenaLossCalculator(p_mapProvider, p_AntennafileProvider)
{
}

float AntennaLossHorizontalCalculator::calculateAntennaLoss()
{
    int azimuthForZeroDeegres = calcAzimuth(); //calculateAzimuth();
    int l_azimuth = relativeAzimuth(azimuthForZeroDeegres);

    float loss = antennafileProvider->getLossFromFile(l_azimuth, Charakteristic::horizontal);
    return loss;
}

void AntennaLossHorizontalCalculator::setAzimuth(int p_azimuth)
{
    azimuth = p_azimuth;
}

int AntennaLossHorizontalCalculator::getAzimuth()
{
    return azimuth;
}

int AntennaLossHorizontalCalculator::relativeAzimuth(int p_azimuthForZeroDeegres)
{
    int l_azimuth = 0;
    if(p_azimuthForZeroDeegres < azimuth)
    {
        l_azimuth = azimuth - p_azimuthForZeroDeegres;
    }
    else if(p_azimuthForZeroDeegres > azimuth)
    {
        l_azimuth = p_azimuthForZeroDeegres - azimuth;
    }
    return l_azimuth;
}

int AntennaLossHorizontalCalculator::calcAzimuth()
{
    float x = antenna.first - receiver.first;
    float y = antenna.second - receiver.second;
    int azimuth = 0;
    if(x == 0)
    {
        if(y < 0) return 180;
        else return 0;
    }
    if(y != 0 )
    {
        azimuth = arcTangens(x/y);
    }
    else
    {
        if(x > 0) return azimuth = 270;
        else return azimuth = 90;
    }

    if(x > 0)
    {
        if (y > 0) azimuth = 360 - azimuth;
        else  azimuth = - azimuth + 180;
    }
    else if(x < 0)
    {
        if(y < 0) azimuth = 180 - azimuth;
        else azimuth = - azimuth;
    }
    return azimuth;
}
