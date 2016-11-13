#ifndef COST231HATAMODEL_H
#define COST231HATAMODEL_H
#include "PathlossModel.h"


class Cost231HataModel : public PathlossModel
{
public:
    Cost231HataModel();

    Pathloss pathloss();

    void changeDistance(float newValue);
    void changeCurrentEnvironment(Environment env);
    void changeEffectiveBSAntennaHeight(float newValue);
    void changeCarrierFrequency(int newValue);
    void changeEffectiveMSAntennaHeight(float newValue);

private:
    float factorA();
    float factorB();
    float factorAh();
};

#endif // COST231HATAMODEL_H
