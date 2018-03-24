#include "RsrpCalculation.h"
#include <cmath>
#include <algorithm>

RsrpCalculation::RsrpCalculation(RsrpInitialization &initialize) :
    init(initialize)
{
}

float RsrpCalculation::calculateRsrp(Sector const& sector)// signal
{
    float rsrp = 0;
    float power = sector.getPower() / mimo(sector);
    //power = std::pow(10, (power/10)) / 1000; //[W]
    //rsrp = std::log10(power/numberOfSubcarrer(sector.getBandwith())) * 10;
    //rsrp = rsrp + 30; //dB na dBm
    //return rsrp;
    return power;
}

int RsrpCalculation::numberOfSubcarrer(double bandwidth)
{
    int subcarriers = 0;
    int resourceBlocks = init.getNumberOfResourceBlocks(bandwidth);

    subcarriers = resourceBlocks * init.getNumberOfSubcarriersInBlock();
    return subcarriers;
}

float RsrpCalculation::mimo(Sector const& sector)
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

float RsrpCalculation::findMaxRsrpFromSectors(std::vector<float> & vectorRsrp)
{
    auto biggest = std::max_element(std::begin(vectorRsrp), std::end(vectorRsrp));
    return *biggest;
}
