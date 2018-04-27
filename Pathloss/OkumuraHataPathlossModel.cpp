#include "OkumuraHataPathlossModel.h"
#include <cmath>

OkumuraHataPathlossModel::OkumuraHataPathlossModel()
    : PathlossModel(Parameter(1500, 150), // MHz
                    Parameter(200, 30),   // m
                    Parameter(10, 1),     // m
                    Parameter(20, 1),
                    Environment::Idle) // km
{
}

Pathloss OkumuraHataPathlossModel::pathloss()
{
    Pathloss pathloss = 0;
    double factorC = executeFactorC(currentEnvironment);
    pathloss = factorA() + (factorB() * std::log10(distance.getValue())) + factorC;
    return pathloss;
}

void OkumuraHataPathlossModel::changeDistance(double newValue)
{
    distance.setValue(newValue);
}

void OkumuraHataPathlossModel::changeCurrentEnvironment(Environment newEnvironment)
{
    currentEnvironment = newEnvironment;
}

void OkumuraHataPathlossModel::changeEffectiveBSAntennaHeight(double newValue)
{
    effectiveBSAntennaHeight.setValue(newValue);
}

void OkumuraHataPathlossModel::changeCarrierFrequency(int newValue)
{
    carrierFrequency.setValue(newValue);
}

void OkumuraHataPathlossModel::changeEffectiveMSAntennaHeight(double newValue)
{
    effectiveMSAntennaHeight.setValue(newValue);
}

double OkumuraHataPathlossModel::factorA()
{
    double factorA = executeFactorA(currentEnvironment);
    double result = 69.55 + (26.16 * std::log10(carrierFrequency.getValue())) + factorA;
    return result;
}

double OkumuraHataPathlossModel::factorB()
{
    double factorB = 0;
    factorB = 44.90 - (6.55 * std::log10(effectiveBSAntennaHeight.getValue()));
    return factorB;
}

double OkumuraHataPathlossModel::factorCforCities()
{
    double factorC = 0;
    return factorC;
}

double OkumuraHataPathlossModel::factorCforSuburbanEnvironments()
{
    double factorC = 0;
    double logFc = std::log10(carrierFrequency.getValue() / 28);
    factorC = ((-2) * logFc * logFc) - 5.4;
    return factorC;
}

double OkumuraHataPathlossModel::factorCforRuralArea()
{
    double factorC = 0;
    double logFc = std::log10(carrierFrequency.getValue());
    factorC = ((-4.78) * logFc * logFc) + (18.33 * logFc) - 40.98;
    return factorC;
}

double OkumuraHataPathlossModel::functionAForMediumCities()
{
    double functionA = 0;
    double logFc = std::log10(carrierFrequency.getValue());
    functionA = (((1.1 * logFc) - 0.7) * effectiveMSAntennaHeight.getValue()) - ((1.56 * logFc) - 0.8);
    return functionA;
}

double OkumuraHataPathlossModel::functionAForMetriopolitan() // zobacz z książką!!!
{
    double functionA = 0;
    double logHm = 0;
    if (carrierFrequency.getValue() <= 200)
    {
        logHm = std::log10(1.54 * effectiveMSAntennaHeight.getValue());
        functionA = (8.29 * logHm * logHm) - 1.1;
    }
    else if (carrierFrequency.getValue() >= 400)
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

double OkumuraHataPathlossModel::executeFactorA(Environment env)
{
    double A = 0;
    switch (env)
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

double OkumuraHataPathlossModel::executeFactorC(Environment env)
{
    double C = 0;
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
