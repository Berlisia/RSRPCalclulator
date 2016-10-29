#include "RsrpCalculation.h"
#include <cmath>
#include <algorithm>

RsrpCalculation::RsrpCalculation(RsrpInitialization &initialize) :
    init(initialize)
{
}

float RsrpCalculation::calculateRsrp(SectorsControler & sectors)
{
    float rsrp = 0;
    float buffRsrp = 0;
    float powerOfSector = 0;
    double bandwithOfSector = 0;
    std::vector<float> rsrpFromSectors;

    for (auto sector : sectors.getVectorOfSectors())
    {
        powerOfSector = sector.getPower();
        bandwithOfSector = sector.getBandwith();

        buffRsrp = std::log10(powerOfSector/numberOfSubcarrer(bandwithOfSector)) * 10;
        rsrpFromSectors.push_back(buffRsrp);
        m_rsrpFromSectors.push_back(buffRsrp); //!!!!!!!!!!!!!!
        buffRsrp = 0;
    }
    rsrp = findMaxRsrpFromSectors(rsrpFromSectors);
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
