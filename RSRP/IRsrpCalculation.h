#ifndef IRSRPCALCULATION_H
#define IRSRPCALCULATION_H
#include <map>
#include "Core/Pixel.h"


class IRsrpCalculation
{
public:
    virtual float calculateRsrp(Pixel & pixel) = 0;
};

#endif // IRSRPCALCULATION_H
