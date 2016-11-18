#include "Cost231HataModel.h"
#include <math.h>

using namespace std;

Cost231HataModel::Cost231HataModel() :
    PathlossModel(Parameter(2000, 1500), //MHz
                  Parameter(200,30), //m
                  Parameter(10,1), //m
                  Parameter(20,1),
                  Environment::Idle) //km
{

}

Pathloss Cost231HataModel::pathloss()
{
    Pathloss pathloss = 0;
    float C = executeC();
    pathloss = factorA() + (factorB() * log10(distance.getValue())) + C;
    return pathloss;
}

void Cost231HataModel::changeDistance(float newValue)
{
    distance.setValue(newValue);
}

void Cost231HataModel::changeCurrentEnvironment(Environment newEnvironment)
{
    currentEnvironment = newEnvironment;
}

void Cost231HataModel::changeEffectiveBSAntennaHeight(float newValue)
{
    effectiveBSAntennaHeight.setValue(newValue);
}

void Cost231HataModel::changeCarrierFrequency(int newValue)
{
    carrierFrequency.setValue(newValue);
}

void Cost231HataModel::changeEffectiveMSAntennaHeight(float newValue)
{
    effectiveMSAntennaHeight.setValue(newValue);
}

float Cost231HataModel::factorA()
{
    float factorA = 0;
    factorA = 46.3 + (33.9 * log10(carrierFrequency.getValue())) -
              (13.82 * log10(effectiveBSAntennaHeight.getValue())) -
              factorAh();
    return factorA;
}

float Cost231HataModel::factorB()
{
    float factorB = 0;
    factorB = 44.9 - (6.55 * log10(effectiveBSAntennaHeight.getValue()));
    return factorB;
}

float Cost231HataModel::factorAh()
{
    float factorAh = 0;
    factorAh = (((1.1 * log10(carrierFrequency.getValue())) - 0.7) * effectiveMSAntennaHeight.getValue()) -
               ((1.56 * log10(carrierFrequency.getValue())) - 0.8);
    return factorAh;
}

float Cost231HataModel::executeC()
{
    float C = 0;
    switch(currentEnvironment)
    {
    case Environment::MetropolitanAreas:
        C = 3;
        break;
    case Environment::SuburbanEvironments:
    case Environment::SmallAndMediumSizeCities:
    case Environment::RuralAera:
    case Environment::Idle:
    default:
        C = 0;
        break;
    }
    return C;
}

