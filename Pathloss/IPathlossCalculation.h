#ifndef IPATHLOSSCALCULATION_H
#define IPATHLOSSCALCULATION_H
#include "Pathloss.h"
#include "PathlossModel.h"


class IPathlossCalculation
{
public:
    virtual std::vector<float> calculatePathloss() = 0;
};

#endif // IPATHLOSSCALCULATION_H
