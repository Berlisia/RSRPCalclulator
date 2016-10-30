#ifndef RSRPCALCULATION_H
#define RSRPCALCULATION_H
#include "IRsrpCalculation.h"
#include "RsrpInitialization.h"

class RsrpCalculation : public IRsrpCalculation
{
public:
    RsrpCalculation(RsrpInitialization & initialize);
    float calculateRsrp(Sector const& sector);
    float findMaxRsrpFromSectors(std::vector<float> & vectorRsrp);

private:
    int numberOfSubcarrer(double bandwidth);
    RsrpInitialization & init;
};

#endif // RSRPCALCULATION_H
