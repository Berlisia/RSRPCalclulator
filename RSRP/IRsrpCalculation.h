#ifndef IRSRPCALCULATION_H
#define IRSRPCALCULATION_H
#include <map>
#include "Core/SectorsControler.h"

class IRsrpCalculation
{
public:
    virtual std::pair<int,double> calculateRsrp(const Sector & sectors) = 0;
};

#endif // IRSRPCALCULATION_H
