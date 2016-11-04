#ifndef ANTENNALOSSHORIZONTALCALCULATOR_H
#define ANTENNALOSSHORIZONTALCALCULATOR_H
#include "AnetnnaLossCalculator.h"


class AntennaLossHorizontalCalculator : public AntenaLossCalculator
{
public:
    AntennaLossHorizontalCalculator(std::shared_ptr<IMapDataProvider> p_mapProvider,
                                    std::shared_ptr<IAntennaLossFileProvider> p_AntennafileProvider);

    float calculateAntennaLoss();
    int calculateAzimuth();
    void setAzimuth(int p_azimuth);

    int getAzimuth();

private:
    int relativeAzimuth(int p_azimuthForZeroDeegres);
    int azimuth;
    int valueOfX();
    int valueOfY();

};

#endif // ANTENNALOSSHORIZONTALCALCULATOR_H
