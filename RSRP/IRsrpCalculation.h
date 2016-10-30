#ifndef IRSRPCALCULATION_H
#define IRSRPCALCULATION_H
#include <map>
#include "Core/SectorsControler.h"

class IRsrpCalculation
{
public:
    virtual float calculateRsrp(const Sector & sectors) = 0;
    virtual float findMaxRsrpFromSectors(std::vector<float> & vectorRsrp) = 0;
};

#endif // IRSRPCALCULATION_H
