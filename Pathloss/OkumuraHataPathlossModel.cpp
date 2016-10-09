#include "OkumuraHataPathlossModel.h"

#include <cmath>

OkumuraHataPathlossModel::OkumuraHataPathlossModel() :
    factorCMap
    {
        {SmallAndMediumSizeCities, std::bind(&OkumuraHataPathlossModel::factorCforCities, this)},
        {MetropolitanAreas,        std::bind(&OkumuraHataPathlossModel::factorCforCities, this)},
        {SuburbanEvironments,      std::bind(&OkumuraHataPathlossModel::factorCforSuburbanEnvironments, this)},
        {RuralAera,                std::bind(&OkumuraHataPathlossModel::factorCforRuralArea, this)},
    },

    functionAMap
    {
        {SmallAndMediumSizeCities, std::bind(&OkumuraHataPathlossModel::functionAForMediumCities, this)},
        {MetropolitanAreas,        std::bind(&OkumuraHataPathlossModel::functionAForMetriopolitan, this)},
        {SuburbanEvironments,      std::bind(&OkumuraHataPathlossModel::functionAForMediumCities, this)},
        {RuralAera,                std::bind(&OkumuraHataPathlossModel::functionAForMediumCities, this)},
    },
    currentEnvironment{idle}
{
    carrierFrequency = std::unique_ptr<Parameter> (new Parameter(150,1500)); //MHz
    effectiveBSAntennaHeight = std::unique_ptr<Parameter> (new Parameter(30,200)); //m
    effectiveMSAntennaHeight = std::unique_ptr<Parameter> (new Parameter(1,10)); //m
    distance = std::unique_ptr<Parameter> (new Parameter(1,20)); //km
}

Pathloss OkumuraHataPathlossModel::pathloss()
{
    Pathloss pathloss = 0;
    const auto & factorFunctionC = factorCMap.find(currentEnvironment);
    float factorC = 0;
    if(factorFunctionC != factorCMap.end())
    {
        factorC = factorFunctionC->second();
    }
    pathloss = factorA()+ (factorB() * std::log10(distance->getValue())) + factorC;
    return pathloss;
}

void OkumuraHataPathlossModel::changeDistance(float newValue)
{
    distance->setValue(newValue);
}

void OkumuraHataPathlossModel::changeCurrentEnvironment(std::string newEnvironment)
{
    currentEnvironment = newEnvironment;
}

void OkumuraHataPathlossModel::calculateEffectiveBSAntennaHeight()
{
    //Na podstawie mapy
}

void OkumuraHataPathlossModel::changeCarrierFrequency(float newValue)
{
    carrierFrequency->setValue(newValue);
}

void OkumuraHataPathlossModel::changeEffectiveMSAntennaHeight(float newValue)
{
    effectiveMSAntennaHeight->setValue(newValue);
}

float OkumuraHataPathlossModel::factorA()
{
    float factorA = 0;
    const auto & functionAFunc = functionAMap.find(currentEnvironment);
    float functionA = 0;
    if(functionAFunc != functionAMap.end())
    {
        functionA = functionAFunc->second();
    }
    factorA = 69.55 + (26.16 * std::log10(effectiveBSAntennaHeight->getValue())) + functionA;
    return factorA;
}

float OkumuraHataPathlossModel::factorB()
{
    float factorB = 0;
    factorB = 44.90 - (6.55 * std::log10(effectiveBSAntennaHeight->getValue()));
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
    float logFc = std::log10(carrierFrequency->getValue() / 28);
    factorC = ((-2) * logFc * logFc) - 5.4;
    return factorC;
}

float OkumuraHataPathlossModel::factorCforRuralArea()
{
    float factorC = 0;
    float logFc = std::log10(carrierFrequency->getValue());
    factorC = ((-4.78) * logFc * logFc) + (18.33 * logFc) - 40.98;
    return factorC;
}

float OkumuraHataPathlossModel::functionAForMediumCities()
{
    float functionA = 0;
    float logFc = std::log10(carrierFrequency->getValue());
    functionA = (((1.1 * logFc) - 0.7) * effectiveMSAntennaHeight->getValue()) - ((1.56 * logFc) - 0.8);
    return functionA;
}

float OkumuraHataPathlossModel::functionAForMetriopolitan()
{
    float functionA = 0;
    float logHm = 0;
    if(carrierFrequency->getValue() <= 200)
    {
        logHm = std::log10(1.54 * effectiveMSAntennaHeight->getValue());
        functionA = (8.29 * logHm * logHm) - 1.1;
    }
    else if(carrierFrequency->getValue() >= 400)
    {
        logHm = std::log10(11.75 * effectiveMSAntennaHeight->getValue());
        functionA = (3.2 * logHm * logHm) - 4.97;
    }
    else
    {
        functionA = functionAForMediumCities();
    }
    return functionA;
}
