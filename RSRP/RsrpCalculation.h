#ifndef RSRPCALCULATION_H
#define RSRPCALCULATION_H
#include "IRsrpCalculation.h"
#include "RsrpInitialization.h"

class RsrpCalculation : public IRsrpCalculation
{
public:
    RsrpCalculation(RsrpInitialization & initialize);
    double calculateRsrp(Sector const& sector);
    double findMaxRsrpFromSectors(std::vector<double> & vectorRsrp);

private:
    int numberOfSubcarrer(double bandwidth);
    double mimo(Sector const& sector);
    RsrpInitialization & init;
};

#endif // RSRPCALCULATION_H
