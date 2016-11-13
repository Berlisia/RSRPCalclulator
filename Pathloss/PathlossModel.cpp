#include "PathlossModel.h"

PathlossModel::PathlossModel(Parameter p_carrierFrequency,
                             Parameter p_effectiveBSAntennaHeight,
                             Parameter p_effectiveMSAntennaHeight,
                             Parameter p_distance,
                             Environment p_currentEnvironment) :
    carrierFrequency(p_carrierFrequency),
    effectiveBSAntennaHeight(p_effectiveBSAntennaHeight),
    effectiveMSAntennaHeight(p_effectiveMSAntennaHeight),
    distance(p_distance),
    currentEnvironment(p_currentEnvironment)
{
}
