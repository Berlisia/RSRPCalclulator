#include "ThroughputCalculator.h"
#include "Common/ModulationSchemes.h"
#include <cmath>

const double threeDBChannelWidth = 0.85;
extern const std::vector<ModulationSchemeAndSnrMapping> modulationAndSnrMappingTable;

ThroughputCalculator::ThroughputCalculator(Throughput& thrData):
    thrData(thrData)
{
}

void ThroughputCalculator::calculate()
{
    for(auto& thrSectorData: thrData) //sector
    {
        double result = threeDBChannelWidth * thrSectorData.getSectorBandwith();
        double oldCoveragePercentage = 0;
        double sumOfModulation = 0;
        for(int modIdx = modulationAndSnrMappingTable.size() - 1; modIdx > 0; modIdx--) //modulacje
        {
            double coveragePercentage = thrSectorData.calculateAreaCoveragePercentage(modulationAndSnrMappingTable[modIdx].minSnr);
            coveragePercentage = coveragePercentage - oldCoveragePercentage;
            double sum = coveragePercentage * modulationAndSnrMappingTable[modIdx].codingRate * std::log2(modulationAndSnrMappingTable[modIdx].valencOfMod);

            sumOfModulation = sumOfModulation + sum;
            oldCoveragePercentage = coveragePercentage;
        }
        thrSectorData.storeThroughputForSector(result * sumOfModulation);
    }
}
