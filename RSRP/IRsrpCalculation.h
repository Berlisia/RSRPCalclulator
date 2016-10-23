#ifndef IRSRPCALCULATION_H
#define IRSRPCALCULATION_H
#include <map>
#include "Core/PixelFinder.h"

class IRsrpCalculation
{
public:
    virtual float calculateRsrp(PixelFinder & pixel) = 0;
};

#endif // IRSRPCALCULATION_H
