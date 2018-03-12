#ifndef OKUMURAHATAPATHLOSSMODEL_H
#define OKUMURAHATAPATHLOSSMODEL_H
#include "PathlossModel.h"
#include <functional>
#include <map>

class OkumuraHataPathlossModel : public PathlossModel
{
public:
    OkumuraHataPathlossModel();

    Pathloss pathloss();

    void changeDistance(float newValue);
    void changeCurrentEnvironment(Environment env);
    void changeEffectiveBSAntennaHeight(float newValue);
    void changeCarrierFrequency(int newValue);
    void changeEffectiveMSAntennaHeight(float newValue);

private:
    float factorA();
    float factorB();

    float factorCforCities();
    float factorCforSuburbanEnvironments();
    float factorCforRuralArea();

    float functionAForMediumCities();
    float functionAForMetriopolitan();

    float executeFactorA(Environment env);
    float executeFactorC(Environment env);
};

#endif // OKUMURAHATAPATHLOSSMODEL_H
