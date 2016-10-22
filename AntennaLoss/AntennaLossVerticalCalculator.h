#ifndef ANTENNALOSSVERTICALCALCULATOR_H
#define ANTENNALOSSVERTICALCALCULATOR_H
#include "AnetnnaLossCalculator.h"

class AntennaLossVerticalCalculator : public AntenaLossCalculator
{
public:
    AntennaLossVerticalCalculator(IMapDataProvider & p_mapProvider, IAntennaLossFileProvider & p_AntennafileProvider);

    float calculateAntennaLoss() override;

    void setAntennaHeight(float p_antennaHeight); //względem UE!!!!
    void setTilt(int p_tilt);

private:
    int calculateAngle();
    void calculateAntennaHeight();
    void calculateAngleWithTilt(int & angle);
    int atangens(const float distance);


    float antennaHeight;
    int tilt;
};

#endif // ANTENNALOSSCALCULATOR_H
