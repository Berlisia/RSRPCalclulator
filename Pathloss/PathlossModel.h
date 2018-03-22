#ifndef PATHLOSSMODEL_H
#define PATHLOSSMODEL_H
#include "Parameter.h"
#include "Pathloss.h"
#include "Core/modeltypes.h"

#include <string>
#include <vector>

class PathlossModel
{
public:
    PathlossModel(Parameter p_carrierFrequency,
                  Parameter p_effectiveBSAntennaHeight,
                  Parameter p_effectiveMSAntennaHeight,
                  Parameter p_distance,
                  Environment p_currentEnvironment);
    virtual Pathloss pathloss() = 0;

    virtual void changeDistance(float newValue) = 0;
    virtual void changeCurrentEnvironment(Environment env) = 0;
    virtual void changeEffectiveBSAntennaHeight(float newValue) = 0;
    virtual void changeCarrierFrequency(int newValue) = 0;
    virtual void changeEffectiveMSAntennaHeight(float newValue) = 0;

protected:
    Parameter carrierFrequency;
    Parameter effectiveBSAntennaHeight;
    Parameter effectiveMSAntennaHeight;
    Parameter distance;

    Environment currentEnvironment;
};

#endif // PATHLOSSMODEL_H
