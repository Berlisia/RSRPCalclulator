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

    void changeDistance(double newValue);
    void changeCurrentEnvironment(Environment newEnvironment);
    void changeEffectiveBSAntennaHeight(double newValue);
    void changeCarrierFrequency(int newValue);
    void changeEffectiveMSAntennaHeight(double newValue);

private:
    double factorA();
    double factorB();

    double factorCforCities();
    double factorCforSuburbanEnvironments();
    double factorCforRuralArea();

    double functionAForMediumCities();
    double functionAForMetriopolitan();

    double executeFactorA(Environment env);
    double executeFactorC(Environment env);
};

#endif // OKUMURAHATAPATHLOSSMODEL_H
