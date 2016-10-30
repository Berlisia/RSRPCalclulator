#ifndef ANTENNALOSSHORIZONTALCALCULATOR_H
#define ANTENNALOSSHORIZONTALCALCULATOR_H
#include "AnetnnaLossCalculator.h"


class AntennaLossHorizontalCalculator : public AntenaLossCalculator
{
public:
    AntennaLossHorizontalCalculator(IMapDataProvider & p_mapProvider, IAntennaLossFileProvider & p_AntennafileProvider);

    float calculateAntennaLoss() override;
    int calculateAzimuth();
    void setAzimuth(int p_azimuth);

private:
    int relativeAzimuth(int p_azimuthForZeroDeegres);
    int azimuth;
    int valueOfX();
    int valueOfY();

};

#endif // ANTENNALOSSHORIZONTALCALCULATOR_H
