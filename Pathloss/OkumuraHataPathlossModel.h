#ifndef OKUMURAHATAPATHLOSSMODEL_H
#define OKUMURAHATAPATHLOSSMODEL_H
#include "PathlossModel.h"
#include "myunorderedmap.h"

#include <functional>
#include <map>
#include <memory>

class OkumuraHataPathlossModel : public PathlossModel
{
public:
    OkumuraHataPathlossModel();

    Pathloss pathloss();

    void changeDistance(float newValue);
    void changeCurrentEnvironment(std::string newEnvironment);
    void calculateEffectiveBSAntennaHeight();
    void changeCarrierFrequency(float newValue);
    void changeEffectiveMSAntennaHeight(float newValue);

private:
    float factorA();
    float factorB();

    float factorCforCities();
    float factorCforSuburbanEnvironments();
    float factorCforRuralArea();

    float functionAForMediumCities();
    float functionAForMetriopolitan();

    std::unique_ptr<Parameter> carrierFrequency;
    std::unique_ptr<Parameter> effectiveBSAntennaHeight;
    std::unique_ptr<Parameter> effectiveMSAntennaHeight;
    std::unique_ptr<Parameter> distance;

    const std::string idle = "Idle";
    const std::string SmallAndMediumSizeCities = "SmallAndMediumSizeCities";
    const std::string MetropolitanAreas = "MetropolitanAreas";
    const std::string SuburbanEvironments = "SuburbanEvironments";
    const std::string RuralAera = "RuralAera";

    typedef std::function<float(void)> parametersCalculationfunction;
    std::map<std::string, parametersCalculationfunction> factorCMap;
    std::map<std::string, parametersCalculationfunction> functionAMap;

    std::string currentEnvironment;
};

#endif // OKUMURAHATAPATHLOSSMODEL_H
