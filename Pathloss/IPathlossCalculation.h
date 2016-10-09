#ifndef IPATHLOSSCALCULATION_H
#define IPATHLOSSCALCULATION_H
#include "Pathloss.h"
#include "PathlossModel.h"


class IPathlossCalculation
{
public:
    virtual Pathloss calculatePathloss(PathlossModel & model) = 0;
};

#endif // IPATHLOSSCALCULATION_H
