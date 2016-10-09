#ifndef OKUMURAPARAMETERFORSECTOR_H
#define OKUMURAPARAMETERFORSECTOR_H
#include "Parameter.h"
#include <memory>

class OkumuraParameterForSector
{
public:
    void setCarrierFrequency(float newValue);
    void setEffectiveMSAntennaHeight(float newValue);
    float calculate();

private:
    std::unique_ptr<Parameter> carrierFrequency;
    std::unique_ptr<Parameter> effectiveMSAntennaHeight;

    float calculateFactorPerSector();
};

#endif // OKUMURAPARAMETERFORSECTOR_H
