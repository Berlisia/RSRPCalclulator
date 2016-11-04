#include "RsrpCalculation.h"
#include <cmath>
#include <algorithm>

RsrpCalculation::RsrpCalculation(RsrpInitialization &initialize) :
    init(initialize)
{
}

float RsrpCalculation::calculateRsrp(Sector const& sector)
{
    float rsrp = 0;
    rsrp = std::log10(sector.getPower()/numberOfSubcarrer(sector.getBandwith())) * 10;
    rsrp = rsrp + 30; //dB na dBm
    return rsrp;
}

int RsrpCalculation::numberOfSubcarrer(double bandwidth)
{
    int subcarriers = 0;
    int resourceBlocks = init.getNumberOfResourceBlocks(bandwidth);

    subcarriers = resourceBlocks * init.getNumberOfSubcarriersInBlock();
    return subcarriers;
}

float RsrpCalculation::findMaxRsrpFromSectors(std::vector<float> & vectorRsrp)
{
    auto biggest = std::max_element(std::begin(vectorRsrp), std::end(vectorRsrp));
    return *biggest;
}
