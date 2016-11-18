#include "OkumuraHataPathlossModel.h"

#include <cmath>
using namespace std;

OkumuraHataPathlossModel::OkumuraHataPathlossModel() :
    PathlossModel(Parameter(1500, 150), //MHz
                  Parameter(200,30), //m
                  Parameter(10,1), //m
                  Parameter(20,1),
                  Environment::Idle) //km
{
}

Pathloss OkumuraHataPathlossModel::pathloss()
{
    Pathloss pathloss = 0;
    float factorC = executeFactorC(currentEnvironment);
    pathloss = factorA()+ (factorB() * std::log10(distance.getValue())) + factorC;
    return pathloss;
}

void OkumuraHataPathlossModel::changeDistance(float newValue)
{
    distance.setValue(newValue);
}

void OkumuraHataPathlossModel::changeCurrentEnvironment(Environment newEnvironment)
{
    currentEnvironment = newEnvironment;
}

void OkumuraHataPathlossModel::changeEffectiveBSAntennaHeight(float newValue)
{
    effectiveBSAntennaHeight.setValue(newValue);
}

void OkumuraHataPathlossModel::changeCarrierFrequency(int newValue)
{
    carrierFrequency.setValue(newValue);
}

void OkumuraHataPathlossModel::changeEffectiveMSAntennaHeight(float newValue)
{
    effectiveMSAntennaHeight.setValue(newValue);
}

float OkumuraHataPathlossModel::factorA()
{
    float factorA = executeFactorA(currentEnvironment);
    float result = 69.55 + (26.16 * std::log10(carrierFrequency.getValue())) + factorA;
    return result;
}

float OkumuraHataPathlossModel::factorB()
{
    float factorB = 0;
    factorB = 44.90 - (6.55 * std::log10(effectiveBSAntennaHeight.getValue()));
    return factorB;
}

float OkumuraHataPathlossModel::factorCforCities()
{
    float factorC = 0;
    return factorC;
}

float OkumuraHataPathlossModel::factorCforSuburbanEnvironments()
{
    float factorC = 0;
    float logFc = std::log10(carrierFrequency.getValue() / 28);
    factorC = ((-2) * logFc * logFc) - 5.4;
    return factorC;
}

float OkumuraHataPathlossModel::factorCforRuralArea()
{
    float factorC = 0;
    float logFc = std::log10(carrierFrequency.getValue());
    factorC = ((-4.78) * logFc * logFc) + (18.33 * logFc) - 40.98;
    return factorC;
}

float OkumuraHataPathlossModel::functionAForMediumCities()
{
    float functionA = 0;
    float logFc = std::log10(carrierFrequency.getValue());
    functionA = (((1.1 * logFc) - 0.7) * effectiveMSAntennaHeight.getValue()) - ((1.56 * logFc) - 0.8);
    return functionA;
}

float OkumuraHataPathlossModel::functionAForMetriopolitan() //zobacz z książką!!!
{
    float functionA = 0;
    float logHm = 0;
    if(carrierFrequency.getValue() <= 200)
    {
        logHm = std::log10(1.54 * effectiveMSAntennaHeight.getValue());
        functionA = (8.29 * logHm * logHm) - 1.1;
    }
    else if(carrierFrequency.getValue() >= 400)
    {
        logHm = std::log10(11.75 * effectiveMSAntennaHeight.getValue());
        functionA = (3.2 * logHm * logHm) - 4.97;
    }
    else
    {
        functionA = functionAForMediumCities();
    }
    return functionA;
}

float OkumuraHataPathlossModel::executeFactorA(Environment env)
{
    float A = 0;
    switch(env)
    {
    case Environment::MetropolitanAreas:
        A = functionAForMetriopolitan();
        break;
    case Environment::SuburbanEvironments:
    case Environment::SmallAndMediumSizeCities:
    case Environment::RuralAera:
        A = functionAForMediumCities();
        break;
    case Environment::Idle:
    default:
        break;
    }
    return A;
}

float OkumuraHataPathlossModel::executeFactorC(Environment env)
{
    float C = 0;
    switch (env)
    {
    case Environment::SmallAndMediumSizeCities:
    case Environment::MetropolitanAreas:
        C = factorCforCities();
        break;
    case Environment::SuburbanEvironments:
        C = factorCforSuburbanEnvironments();
        break;
    case Environment::RuralAera:
        C = factorCforRuralArea();
        break;
    case Environment::Idle:
    default:
        break;
    }
    return C;
}
