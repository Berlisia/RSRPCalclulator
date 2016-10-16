#ifndef ANTENNALOSSVERTICALCALCULATOR_H
#define ANTENNALOSSVERTICALCALCULATOR_H
#include "Core/PixelPoint.h"
#include "MapProvider/IMapDataProvider.h"
#include "Core/Antenna.h"
#include "IAntennaLossFileProvider.h"

class AntennaLossVerticalCalculator
{
public:
    AntennaLossVerticalCalculator(IMapDataProvider & p_mapProvider, IAntennaLossFileProvider & p_AntennafileProvider);
    float calculateAntennaLoss();
    void setReceiver(std::pair<int,int> p_receiver);
    void setAntenna(std::pair<int,int> p_antenna);
    void setAntennaHeight(float p_antennaHeight); //względem UE!!!!
    void setTilt(int p_tilt);

private:
    int calculateAngle();

    std::pair<int,int> receiver;
    std::pair<int,int> antenna;
    float antennaHeight;
    int tilt;
    IMapDataProvider & mapProvider;
    IAntennaLossFileProvider & antennafileProvider;
};

#endif // ANTENNALOSSCALCULATOR_H
