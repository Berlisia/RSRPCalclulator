#ifndef ANTENNALOSSHORIZONTALCALCULATOR_H
#define ANTENNALOSSHORIZONTALCALCULATOR_H
#include "AnetnnaLossCalculator.h"


class AntennaLossHorizontalCalculator : public AntenaLossCalculator
{
public:
    AntennaLossHorizontalCalculator(IMapDataProvider & p_mapProvider, IAntennaLossFileProvider & p_AntennafileProvider);

    float calculateAntennaLoss() override;
    int calculateAzimuth();

private:
    int valueOfX();
    int valueOfY();

};

#endif // ANTENNALOSSHORIZONTALCALCULATOR_H
