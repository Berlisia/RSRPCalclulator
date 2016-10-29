#ifndef RSRPCALCULATION_H
#define RSRPCALCULATION_H
#include "IRsrpCalculation.h"
#include "RsrpInitialization.h"

class RsrpCalculation : public IRsrpCalculation
{
public:
    RsrpCalculation(RsrpInitialization & initialize);
    float calculateRsrp(SectorsControler & sectors);

private:
    int numberOfSubcarrer(double bandwidth);
    float findMaxRsrpFromSectors(std::vector<float> & vectorRsrp);
    RsrpInitialization & init;
};

#endif // RSRPCALCULATION_H
