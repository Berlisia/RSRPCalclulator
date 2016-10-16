#ifndef IRSRPCALCULATION_H
#define IRSRPCALCULATION_H
#include <map>
#include "Core/PixelPoint.h"

class IRsrpCalculation
{
public:
    virtual float calculateRsrp(PixelPoint & pixel) = 0;
};

#endif // IRSRPCALCULATION_H
