#ifndef RSRPCALCULATION_H
#define RSRPCALCULATION_H
#include "IRsrpCalculation.h"
#include "RsrpInitialization.h"

class RsrpCalculation : public IRsrpCalculation
{
public:
    RsrpCalculation(RsrpInitialization & initialize);
    std::pair<int,double> calculateRsrp(Sector const& sector);

private:
    int numberOfSubcarrer(double bandwidth);
    double mimo(Sector const& sector);
    RsrpInitialization & init;
    int numberOfPrb;
};

#endif // RSRPCALCULATION_H
