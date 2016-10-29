#ifndef IRSRPCALCULATION_H
#define IRSRPCALCULATION_H
#include <map>
#include "Core/SectorsControler.h"

class IRsrpCalculation
{
public:
    virtual float calculateRsrp(SectorsControler & sectors) = 0;
    std::vector<float> m_rsrpFromSectors;
};

#endif // IRSRPCALCULATION_H
