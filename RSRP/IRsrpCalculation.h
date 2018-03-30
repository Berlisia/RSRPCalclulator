#ifndef IRSRPCALCULATION_H
#define IRSRPCALCULATION_H
#include <map>
#include "Core/SectorsControler.h"

class IRsrpCalculation
{
public:
    virtual double calculateRsrp(const Sector & sectors) = 0;
    virtual double findMaxRsrpFromSectors(std::vector<double> & vectorRsrp) = 0;
};

#endif // IRSRPCALCULATION_H
