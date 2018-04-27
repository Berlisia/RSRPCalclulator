#ifndef COST231HATAMODEL_H
#define COST231HATAMODEL_H
#include "PathlossModel.h"


class Cost231HataModel : public PathlossModel
{
public:
    Cost231HataModel();

    Pathloss pathloss();

    void changeDistance(double newValue);
    void changeCurrentEnvironment(Environment newEnvironment);
    void changeEffectiveBSAntennaHeight(double newValue);
    void changeCarrierFrequency(int newValue);
    void changeEffectiveMSAntennaHeight(double newValue);

private:
    double factorA();
    double factorB();
    double factorAh();
    double executeC();
};

#endif // COST231HATAMODEL_H
