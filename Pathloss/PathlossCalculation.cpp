#include "PathlossCalculation.h"

Pathloss PathlossCalculation::calculatePathloss(PathlossModel &model)
{
    Pathloss pathloss = model.pathloss();
    return pathloss;
}
