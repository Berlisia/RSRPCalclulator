#ifndef PATHLOSSCALCULATION_H
#define PATHLOSSCALCULATION_H
#include "IPathlossCalculation.h"

class PathlossCalculation : public IPathlossCalculation
{
public:
    Pathloss calculatePathloss(PathlossModel & model);
};

#endif // PATHLOSSCALCULATION_H
