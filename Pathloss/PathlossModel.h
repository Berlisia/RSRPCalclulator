#ifndef PATHLOSSMODEL_H
#define PATHLOSSMODEL_H
#include "Parameter.h"
#include "Pathloss.h"

#include <string>
#include <vector>

enum class environment
{
    Idle,
    SmallAndMediumSizeCities,
    MetropolitanAreas,
    SuburbanEvironments,
    RuralAera
};

class PathlossModel
{
public:
    virtual Pathloss pathloss() = 0;
};

#endif // PATHLOSSMODEL_H
