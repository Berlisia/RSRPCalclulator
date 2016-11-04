#ifndef ANTENNALOSSVERTICALCALCULATOR_H
#define ANTENNALOSSVERTICALCALCULATOR_H
#include "AnetnnaLossCalculator.h"

class AntennaLossVerticalCalculator : public AntenaLossCalculator
{
public:
    AntennaLossVerticalCalculator(std::shared_ptr<IMapDataProvider> p_mapProvider,
                                  std::shared_ptr<IAntennaLossFileProvider> p_AntennafileProvider);

    float calculateAntennaLoss();

    void setAntennaHeight(float p_antennaHeight); //względem UE!!!!
    void setTilt(int p_tilt);

    float getAntennaHeight();
    int getTilt();

private:
    int calculateAngle();
    void calculateAntennaHeight();
    void calculateAngleWithTilt(int & angle);
    int atangens(const float distance);


    float antennaHeight;
    int tilt;
};

#endif // ANTENNALOSSCALCULATOR_H
