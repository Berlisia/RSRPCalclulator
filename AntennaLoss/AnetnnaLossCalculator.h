#ifndef ANETNNALOSSCALCULATOR_H
#define ANETNNALOSSCALCULATOR_H
#include "Core/PixelXY.h"
#include "MapProvider/IMapDataProvider.h"
#include "Core/Antenna.h"
#include "IAntennaLossFileProvider.h"
#include <memory>

class AntenaLossCalculator
{
public:
    AntenaLossCalculator(std::shared_ptr<IMapDataProvider> p_mapProvider,
                         std::shared_ptr<IAntennaLossFileProvider> p_AntennafileProvider);

    //double calculateAntennaLoss();
    void setReceiver(std::pair<int,int> p_receiver);
    void setAntenna(std::pair<int,int> p_antenna);

    std::pair<int,int> getAntennaPossiton();

protected:
    int arcTangens(const double distance);

    std::shared_ptr<IMapDataProvider> mapProvider;
    std::shared_ptr<IAntennaLossFileProvider> antennafileProvider;

    std::pair<int,int> receiver;
    std::pair<int,int> antenna;

    static const int stopnie;
    static const double PI;
    static const int circle;
};

#endif // ANETNNALOSSCALCULATOR_H
