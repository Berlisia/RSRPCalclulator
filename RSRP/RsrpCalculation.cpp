#include "RsrpCalculation.h"
#include <cmath>
#include <algorithm>

RsrpCalculation::RsrpCalculation(RsrpInitialization &initialize) :
    init(initialize), numberOfPrb(0)
{
}

std::pair<int,double> RsrpCalculation::calculateRsrp(Sector const& sector)// signal
{
    double rsrp = 0;
    double power = sector.getPower() / mimo(sector);
    rsrp = power - std::log10(numberOfSubcarrer(sector.getBandwith())) * 10; //dBm - dB
    return std::pair<int, double>(numberOfPrb, rsrp);
}

int RsrpCalculation::numberOfSubcarrer(double bandwidth)
{
    int subcarriers = 0;
    numberOfPrb = init.getNumberOfResourceBlocks(bandwidth);
    subcarriers = numberOfPrb * init.getNumberOfSubcarriersInBlock();
    return subcarriers;
}

double RsrpCalculation::mimo(Sector const& sector)
{
    switch (sector.getMimo())
    {
    case Mimo::FourAntenna:
        return 4;
    case Mimo::TwoAntenna:
        return 2;
    case Mimo::Nan:
    default:
        return 1;
    }
}
