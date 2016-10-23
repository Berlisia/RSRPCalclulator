#ifndef ANETNNALOSSCALCULATOR_H
#define ANETNNALOSSCALCULATOR_H
#include "Core/PixelPoint.h"
#include "MapProvider/IMapDataProvider.h"
#include "Core/Antenna.h"
#include "IAntennaLossFileProvider.h"

class AntenaLossCalculator
{
public:
    AntenaLossCalculator(IMapDataProvider & p_mapProvider, IAntennaLossFileProvider & p_AntennafileProvider);

    virtual float calculateAntennaLoss() = 0;
    void setReceiver(std::pair<int,int> p_receiver);
    void setAntenna(std::pair<int,int> p_antenna);

protected:
    int arcTangens(const float distance);

    IMapDataProvider & mapProvider;
    IAntennaLossFileProvider & antennafileProvider;

    std::pair<int,int> receiver;
    std::pair<int,int> antenna;

    static const int stopnie;
    static const float PI;
};

#endif // ANETNNALOSSCALCULATOR_H